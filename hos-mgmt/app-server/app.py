# This Python file uses the following encoding: utf-8
from flask import Flask, request, jsonify
import os
import json
import re
from datetime import datetime
from threading import Lock

# WebSocket
# pip install flask-sock simple-websocket
from flask_sock import Sock

# SQLite 初始化与服务导入
from infra.sqlite_store import get_db, init_db
init_db()  # 确保 health / conversations / messages 等表存在

from services.auth_service import AuthService
from services.chat_service import ChatService

# doctor.db（独立库）初始化与查询
from infra.doctor_store import list_doctors, ensure_schema as ensure_doctor_schema
ensure_doctor_schema()  # 确保 doctor.db 的 users 表存在

# 智谱AI SDK（可选）
try:
    from zai import ZhipuAiClient
except Exception:
    ZhipuAiClient = None

app = Flask(__name__)
sock = Sock(app)  # 一定要在使用 @sock.route 之前创建

auth_svc = AuthService()
chat_svc = ChatService()

# 智谱AI客户端初始化
ZHIPUAI_API_KEY = "bf1b48412dd44f499e47b5ba3f85da8f.HiG3WMp9h64Bho8v"
glm_client = ZhipuAiClient(api_key=ZHIPUAI_API_KEY) if (ZhipuAiClient and ZHIPUAI_API_KEY) else None

# --------------------
# 认证与健康接口（按你现有逻辑保留）
# --------------------
@app.route("/api/auth/login", methods=["POST"])
def api_auth_login():
    data = request.get_json(silent=True) or {}
    profession = str(data.get("userType", "")).strip()
    username = str(data.get("username", "")).strip()
    password = str(data.get("password", "")).strip()
    if not username or not password or not profession:
        return jsonify(success=False, reason="用户名或密码或职业为空"), 400

    user, err = auth_svc.login(profession, username, password)
    if err:
        return jsonify(success=False, reason=err, remainingAttempts=4), 401

    return jsonify(success=True, userId=user["id"], userType=profession)

@app.route("/api/auth/register", methods=["POST"])
def register_user():
    data = request.json or {}
    profession = data.get("userType")
    username = data.get("username")
    password = data.get("password")
    patient_info = {
        "gender": data.get("gender"),
        "phone": data.get("phone"),
        "address": data.get("address"),
        "age": data.get("age"),
    }
    if not (profession and username and password):
        return jsonify({"error": "必填项缺失"}), 400
    uid, err = auth_svc.register_user(profession, username, password, patient_info)
    if err:
        return jsonify({"error": err}), 400
    return jsonify({"id": uid}), 200

@app.route("/api/patient/info", methods=["GET"])
def api_patient_info():
    user_id = request.args.get("userId", type=int)
    profession = request.args.get("profession", type=str)
    info = auth_svc.get_patient_info(profession, user_id)
    if not info:
        return jsonify(success=False, reason="用户不存在"), 404
    return jsonify(success=True, info=info)

@app.route("/api/patient/update", methods=["POST"])
def api_patient_update():
    data = request.json or {}
    user_id = data.get("userId")
    profession = data.get("profession")
    username = data.get("username")
    phone = data.get("phone")
    address = data.get("address")
    age = data.get("age")
    gender = data.get("gender")
    ok = auth_svc.update_patient_info(profession, user_id, username, phone, address, age, gender)
    return jsonify(success=ok)

# --------------------
# 医生列表（来自独立 doctor.db）
# --------------------
@app.route("/api/doctors", methods=["GET"])
def api_list_doctors():
    """
    医生列表
    优先从职业库 db/doctor.sqlite 的 users 表读取（与注册一致），
    若无数据再回退到独立的 doctor.db（infra.doctor_store）。

    统一返回字段（若无则置空）：
    id, username, department, title, hospital, phone, address, age, gender, description, fee
    支持 ?q= 关键字搜索（匹配 username/phone/address）
    """
    q = (request.args.get("q") or "").strip()
    like = f"%{q}%" if q else None

    # 1) 优先：职业库（与注册一致）
    try:
        conn = get_db("doctor")
        cur = conn.cursor()
        if like:
            cur.execute(
                """
                SELECT id, username, phone, address, age, gender
                FROM users
                WHERE username LIKE ? OR phone LIKE ? OR address LIKE ?
                ORDER BY id DESC
                LIMIT 100
                """,
                (like, like, like),
            )
        else:
            cur.execute(
                """
                SELECT id, username, phone, address, age, gender
                FROM users
                ORDER BY id DESC
                LIMIT 100
                """
            )
        rows = cur.fetchall()
        conn.close()

        doctors = []
        for r in rows:
            # 映射到统一字段，职业库没有的字段置空/默认
            d = dict(r)
            doctors.append({
                "id": int(d.get("id", 0)),
                "username": d.get("username") or "",
                "department": "",
                "title": "",
                "hospital": "",
                "phone": d.get("phone") or "",
                "address": d.get("address") or "",
                "age": d.get("age") if d.get("age") is not None else "",
                "gender": d.get("gender") or "",
                "description": "",
                "fee": 0
            })

        # 若职业库已有数据，直接返回
        if len(doctors) > 0:
            return jsonify(success=True, doctors=doctors)
    except Exception as e:
        # 打印日志但不影响后续回退
        print("api/doctors read from profession db failed:", e)

    # 2) 回退：独立 doctor.db（老数据或预置数据）
    try:
        data = list_doctors(q=q, limit=100)
        return jsonify(success=True, doctors=data)
    except Exception as e:
        return jsonify(success=False, reason=f"doctor.db 查询失败: {e}"), 500

# --------------------
# 健康评估
# --------------------
@app.route("/api/health/submit", methods=["POST"])
def submit_health():
    data = request.get_json(silent=True) or {}
    try:
        user_id = int(data.get("userId", 0))
        height = float(data.get("height", 0))
        weight = float(data.get("weight", 0))
        lung = int(data.get("lung", 0))
        bp = str(data.get("bp", "")).strip()
    except Exception:
        return jsonify(success=False, reason="参数解析错误"), 400

    if user_id <= 0:
        return jsonify(success=False, reason="userId 非法"), 400
    if height < 50 or height > 250 or weight < 10 or weight > 500 or lung < 100 or lung > 20000:
        return jsonify(success=False, reason="参数范围错误"), 400
    if not re.match(r'^\s*\d{2,3}\s*/\s*\d{2,3}\s*$', bp):
        return jsonify(success=False, reason="血压格式错误，示例 120/80"), 400

    def assess_bmi(height_cm, weight_kg):
        h = height_cm / 100.0
        bmi = weight_kg / (h*h) if h > 0 else 0
        if bmi < 18.5:
            cat = "偏瘦"
        elif bmi < 25:
            cat = "正常"
        elif bmi < 30:
            cat = "超重"
        else:
            cat = "肥胖"
        return bmi, cat

    def assess_bp(bp_str):
        m = re.match(r'^\s*(\d{2,3})\s*/\s*(\d{2,3})\s*$', bp_str)
        if not m:
            return "无效"
        sys = int(m.group(1))
        dia = int(m.group(2))
        if sys < 120 and dia < 80:
            return "理想"
        elif 120 <= sys < 130 and dia < 80:
            return "偏高"
        elif (130 <= sys < 140) or (80 <= dia < 90):
            return "高血压一期"
        elif sys >= 140 or dia >= 90:
            return "高血压二期"
        else:
            return "未分类"

    def assess_lung(lung_ml):
        if lung_ml < 2500:
            return "偏低"
        elif lung_ml <= 3500:
            return "正常"
        else:
            return "良好"

    bmi, bmi_cat = assess_bmi(height, weight)
    bp_level = assess_bp(bp)
    lung_level = assess_lung(lung)

    flags = []
    if bmi_cat in ("偏瘦", "超重", "肥胖"):
        flags.append("体重")
    if bp_level in ("偏高", "高血压一期", "高血压二期"):
        flags.append("血压")
    if lung_level == "偏低":
        flags.append("肺活量")
    overall = "健康" if not flags else "需关注：" + "、".join(flags)

    conn = get_db()
    c = conn.cursor()
    c.execute("""
        INSERT INTO health (user_id, height, weight, lung, bp, bmi, bmiLevel, bpLevel, lungLevel, overall, time)
        VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)""",
        (user_id, height, weight, lung, bp, round(bmi, 1), bmi_cat, bp_level, lung_level, overall, datetime.utcnow().isoformat())
    )
    conn.commit()
    conn.close()

    return jsonify(success=True,
                   bmi=round(bmi, 1),
                   lungLevel=lung_level,
                   bpLevel=bp_level,
                   overall=overall)

# 智谱GLM大语言模型（可选）
@app.route("/glm_chat", methods=["POST"])
def glm_chat():
    data = request.get_json(silent=True) or {}
    question = data.get("question", "")
    if not question:
        return jsonify({"reply": "问题内容为空"}), 400
    if not glm_client:
        return jsonify({"reply": "未配置ZHIPUAI_API_KEY或未安装zai SDK"}), 500
    try:
        response = glm_client.chat.completions.create(
            model="glm-4-air-250414",
            messages=[
                {"role": "system", "content": "你是智能医疗助手，请将回答控制在70字以内。"},
                {"role": "user", "content": question}
            ],
            temperature=0.6
        )
        reply = response.choices[0].message.content
        return jsonify({"reply": reply})
    except Exception as e:
        return jsonify({"reply": "调用大模型失败: {}".format(str(e))}), 500

# --------------------
# 聊天 REST 接口
# --------------------
@app.route("/api/chat/conversation", methods=["POST"])
def api_chat_conversation():
    data = request.get_json(silent=True) or {}
    try:
        patient_id = int(data.get("patientId"))
        doctor_id = int(data.get("doctorId"))
    except Exception:
        return jsonify(success=False, reason="参数错误"), 400

    conv_id = chat_svc.create_or_get_conversation(patient_id, doctor_id)
    return jsonify(success=True, conversationId=conv_id)

@app.route("/api/chat/messages", methods=["GET"])
def api_chat_messages():
    conversation_id = request.args.get("conversationId", type=int)
    if not conversation_id:
        return jsonify(success=False, reason="缺少 conversationId"), 400
    after = request.args.get("after", default=None, type=str)
    limit = request.args.get("limit", default=100, type=int)
    msgs = chat_svc.list_messages(conversation_id, after_iso=after, limit=limit)
    return jsonify(success=True, messages=msgs)

@app.route("/api/chat/send", methods=["POST"])
def api_chat_send():
    data = request.get_json(silent=True) or {}
    try:
        conversation_id = int(data.get("conversationId"))
        sender_id = int(data.get("senderId"))
        sender_role = str(data.get("senderRole"))
        content = str(data.get("content")).strip()
    except Exception:
        return jsonify(success=False, reason="参数错误"), 400
    if not content:
        return jsonify(success=False, reason="内容为空"), 400

    msg = chat_svc.add_message(conversation_id, sender_id, sender_role, content)
    _broadcast_message(conversation_id, msg)

    pair = chat_svc.get_conversation_pair(conversation_id)
    if pair and pair[1] == -1 and sender_role == "patient":
        _ai_reply_async(conversation_id, content)

    return jsonify(success=True, message=msg)

# 新增：医生端会话列表接口（用于医生会话列表页）
@app.get("/api/chat/doctor/conversations")
def api_doctor_conversations():
    """
    列出某医生的会话列表（按最后一条消息时间倒序）
    返回：
      { success:true, conversations:[{ id, patient_id, doctor_id, patient_name, last_message, last_at }] }
    数据来源：
      - conversations/messages 表位于默认库（get_db(None)）
      - 患者姓名位于 patient 库（get_db('patient')）
    """
    doctor_id = request.args.get("doctorId", type=int)
    limit = request.args.get("limit", default=100, type=int)
    offset = request.args.get("offset", default=0, type=int)
    if not doctor_id:
        return jsonify(success=False, reason="缺少 doctorId"), 400

    def _get_patient_name(pid: int) -> str:
        try:
            conn_p = get_db("patient")
            cur_p = conn_p.cursor()
            cur_p.execute("SELECT username FROM users WHERE id = ? LIMIT 1", (pid,))
            row = cur_p.fetchone()
            conn_p.close()
            return row["username"] if row else ""
        except Exception:
            return ""

    try:
        conn = get_db()
        cur = conn.cursor()
        cur.execute(
            """
            WITH last_msg AS (
              SELECT conversation_id, MAX(id) AS max_id
              FROM messages
              GROUP BY conversation_id
            )
            SELECT c.id,
                   c.patient_id,
                   c.doctor_id,
                   m.content AS last_message,
                   COALESCE(m.created_at, c.created_at) AS last_at
            FROM conversations c
            LEFT JOIN last_msg lm ON lm.conversation_id = c.id
            LEFT JOIN messages m ON m.id = lm.max_id
            WHERE c.doctor_id = ?
            ORDER BY last_at DESC
            LIMIT ? OFFSET ?
            """,
            (doctor_id, limit, offset),
        )
        rows = cur.fetchall()
        conn.close()

        data = []
        for r in rows:
            d = dict(r)
            d["id"] = int(d["id"])
            d["patient_id"] = int(d["patient_id"])
            d["doctor_id"] = int(d["doctor_id"])
            d["patient_name"] = _get_patient_name(d["patient_id"])
            d["last_message"] = d.get("last_message") or ""
            d["last_at"] = d.get("last_at") or ""
            data.append(d)
        return jsonify(success=True, conversations=data)
    except Exception as e:
        return jsonify(success=False, reason=str(e)), 500

# --------------------
# WebSocket 实时聊天
# --------------------
_rooms = {}
_rooms_lock = Lock()

def _join_room(conversation_id: int, ws):
    with _rooms_lock:
        _rooms.setdefault(conversation_id, set()).add(ws)

def _leave_room(conversation_id: int, ws):
    with _rooms_lock:
        if conversation_id in _rooms and ws in _rooms[conversation_id]:
            _rooms[conversation_id].remove(ws)
            if not _rooms[conversation_id]:
                _rooms.pop(conversation_id, None)

def _broadcast_message(conversation_id: int, msg: dict):
    payload = json.dumps({"type": "message", "conversationId": conversation_id, "message": msg}, ensure_ascii=False)
    with _rooms_lock:
        conns = list(_rooms.get(conversation_id, set()))
    for ws in conns:
        try:
            ws.send(payload)
        except Exception:
            _leave_room(conversation_id, ws)

@sock.route("/ws/chat")
def ws_chat(ws):
    """
    客户端协议：
    - 发送: {"type":"join","conversationId":1}
    - 发送: {"type":"send","senderId":123,"senderRole":"patient|doctor","content":"你好"}
    - 接收: {"type":"message","conversationId":1,"message":{...}}
    """
    joined_conv = None
    try:
        while True:
            raw = ws.receive()
            if raw is None:
                break
            try:
                data = json.loads(raw)
            except Exception:
                ws.send(json.dumps({"type":"error","reason":"invalid json"}))
                continue

            t = data.get("type")
            if t == "join":
                conv_id = int(data.get("conversationId", 0))
                if conv_id <= 0:
                    ws.send(json.dumps({"type":"error","reason":"invalid conversationId"}))
                    continue
                if joined_conv is not None and joined_conv != conv_id:
                    _leave_room(joined_conv, ws)
                joined_conv = conv_id
                _join_room(conv_id, ws)
                ws.send(json.dumps({"type":"joined","conversationId":conv_id}))
            elif t == "send":
                if joined_conv is None:
                    ws.send(json.dumps({"type":"error","reason":"not joined"}))
                    continue
                try:
                    sender_id = int(data.get("senderId"))
                    sender_role = str(data.get("senderRole"))
                    content = str(data.get("content")).strip()
                except Exception:
                    ws.send(json.dumps({"type":"error","reason":"bad payload"}))
                    continue
                if not content:
                    continue
                msg = chat_svc.add_message(joined_conv, sender_id, sender_role, content)
                _broadcast_message(joined_conv, msg)

                pair = chat_svc.get_conversation_pair(joined_conv)
                if pair and pair[1] == -1 and sender_role == "patient":
                    _ai_reply_async(joined_conv, content)
            else:
                ws.send(json.dumps({"type":"error","reason":"unknown type"}))
    finally:
        if joined_conv is not None:
            _leave_room(joined_conv, ws)

# --------------------
# AI 自动回复（可选）
# --------------------
def _ai_reply_async(conversation_id: int, user_content: str):
    if not glm_client:
        return
    try:
        resp = glm_client.chat.completions.create(
            model="glm-4-air-250414",
            messages=[
                {"role": "system", "content": "你是智能医疗助手，请用不超过70字回复，不能提供诊断，仅给一般性建议。"},
                {"role": "user", "content": user_content}
            ],
            temperature=0.6
        )
        reply = resp.choices[0].message.content.strip()
        if not reply:
            reply = "已收到，请补充更多症状信息。"
    except Exception:
        reply = "当前无法自动回复，请稍后再试。"

    msg = chat_svc.add_message(conversation_id, sender_id=0, sender_role="ai", content=reply)
    _broadcast_message(conversation_id, msg)

if __name__ == "__main__":
    # 开发模式：内置服务器即可；部署建议用 hypercorn 或 gunicorn + gevent/ws
    # pip install hypercorn
    # 运行: hypercorn app:app --bind 127.0.0.1:8080
    app.run(host="127.0.0.1", port=8080, debug=True)

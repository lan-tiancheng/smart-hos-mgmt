# This Python file uses the following encoding: utf-8
from flask import Flask, request, jsonify
import os
from datetime import datetime

# SQLite 初始化与服务导入
from infra.sqlite_store import get_db, init_db
init_db()

from services.auth_service import AuthService

# 智谱AI SDK导入
from zai import ZhipuAiClient

app = Flask(__name__)

auth_svc = AuthService()

# 智谱AI客户端初始化（请替换为你的API KEY）
ZHIPUAI_API_KEY = os.environ.get("ZHIPUAI_API_KEY", "bf1b48412dd44f499e47b5ba3f85da8f.HiG3WMp9h64Bho8v")
glm_client = ZhipuAiClient(api_key=ZHIPUAI_API_KEY)

# 登录接口
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
# 获取医生信息
@app.route("/api/doctor/info", methods=["GET"])
def api_doctor_info():
    doctor_id = request.args.get("doctorId", type=str)
    if not doctor_id:
        return jsonify(success=False, reason="doctorId为空"), 400

    conn = get_db("doctor")
    c = conn.cursor()
    c.execute("SELECT id, name, hospital, department, profile, work_time, fee, max_patients, photo FROM doctor WHERE id=?", (doctor_id,))
    row = c.fetchone()
    conn.close()

    if not row:
        return jsonify(success=False, reason="医生不存在"), 404

    info = {
        "id": row[0],
        "name": row[1],
        "hospital": row[2],
        "department": row[3],
        "profile": row[4],
        "work_time": row[5],
        "fee": row[6],
        "max_patients": row[7],
        "photo": row[8]
    }
    return jsonify(success=True, info=info)


# 更新医生信息
@app.route("/api/doctor/update", methods=["POST"])
def api_doctor_update():
    data = request.get_json(silent=True) or {}
    doctor_id = data.get("id")
    if not doctor_id:
        return jsonify(success=False, reason="医生ID为空"), 400

    conn = get_db("doctor")
    c = conn.cursor()
    # 如果医生不存在，则插入新记录，否则更新
    c.execute("SELECT 1 FROM doctor WHERE id=?", (doctor_id,))
    if c.fetchone():
        c.execute("""
            UPDATE doctor SET
                name=?, hospital=?, department=?, profile=?, work_time=?, fee=?, max_patients=?, photo=?
            WHERE id=?
        """, (
            data.get("name"),
            data.get("hospital"),
            data.get("department"),
            data.get("profile"),
            data.get("work_time"),
            data.get("fee"),
            data.get("max_patients"),
            data.get("photo"),
            doctor_id
        ))
    else:
        c.execute("""
            INSERT INTO doctor (id, name, hospital, department, profile, work_time, fee, max_patients, photo)
            VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?)
        """, (
            doctor_id,
            data.get("name"),
            data.get("hospital"),
            data.get("department"),
            data.get("profile"),
            data.get("work_time"),
            data.get("fee"),
            data.get("max_patients"),
            data.get("photo")
        ))
    conn.commit()
    conn.close()
    return jsonify(success=True)

# 注册接口
@app.route("/api/auth/register", methods=["POST"])
def register_user():
    data = request.json
    print("Received register request:", data)
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

# 获取患者信息
@app.route("/api/patient/info", methods=["GET"])
def api_patient_info():
    user_id = request.args.get("userId", type=int)
    profession = request.args.get("profession", type=str)
    info = auth_svc.get_patient_info(profession, user_id)
    if not info:
        return jsonify(success=False, reason="用户不存在"), 404
    return jsonify(success=True, info=info)

# 修改患者信息
@app.route("/api/patient/update", methods=["POST"])
def api_patient_update():
    try:
        data = request.json
        user_id = data.get("userId")
        profession = data.get("profession")
        username = data.get("username")
        phone = data.get("phone")
        address = data.get("address")
        age = data.get("age")
        gender = data.get("gender")
        dob = data.get("dob")
        id_card = data.get("idCard")
        email = data.get("email")

        ok, reason = auth_svc.update_patient_info(
            profession, user_id, username, phone, address, age, gender,
            dob, id_card, email
        )
        return jsonify(success=ok, reason=reason)
    except Exception as e:
        # 捕获 Flask 全局异常，确保返回 JSON
        print("接口异常:", e)
        return jsonify(success=False, reason=str(e)), 500

# 健康体检提交接口
@app.route("/api/health/submit", methods=["POST"])
def submit_health():
    import re
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

    # 保存到 SQLite 健康表
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

# 智谱GLM大语言模型接口
@app.route("/glm_chat", methods=["POST"])
def glm_chat():
    data = request.get_json(silent=True) or {}
    question = data.get("question", "")
    if not question:
        return jsonify({"reply": "问题内容为空"}), 400
    try:
        response = glm_client.chat.completions.create(
            model="glm-4-air-250414",
            messages=[
                {"role": "system", "content": "你是一个县浩田开发的，李融超（其男友）合作的智能医疗助手，清保证你的回答在70字以内。"},
                {"role": "user", "content": question}
            ],
            temperature=0.6
        )
        reply = response.choices[0].message.content
        return jsonify({"reply": reply})
    except Exception as e:
        return jsonify({"reply": "调用大模型失败: {}".format(str(e))}), 500

if __name__ == "__main__":
    app.run(host="127.0.0.1", port=8080, debug=True)

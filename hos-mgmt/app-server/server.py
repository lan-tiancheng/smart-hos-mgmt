# This Python file uses the following encoding: utf-8

# if __name__ == "__main__":
#     pass
# server.py （替换 DB 相关实现为 Redis）
from flask import Flask, request, jsonify
import redis, re
from werkzeug.security import generate_password_hash, check_password_hash
from datetime import datetime

app = Flask(__name__)
# 连接 Redis（默认本机）
r = redis.Redis(host='127.0.0.1', port=6379, db=0, decode_responses=True)

# helper: create user atomically (prevent duplicate username)
def create_user_atomic(username, password_hash, user_type, phone, address, age, gender):
    username_key = f"username:{username}"
    with r.pipeline() as pipe:
        while True:
            try:
                # WATCH username key to detect concurrent writes
                pipe.watch(username_key)
                if r.exists(username_key):
                    pipe.unwatch()
                    return None  # 已存在
                # 执行事务：INCR next_user_id + HSET user + SET username:{name} = id
                pipe.multi()
                pipe.incr("next_user_id")
                res = pipe.execute()
                # res[0] 是新 id
                new_id = res[0]
                user_key = f"user:{new_id}"
                pipe = r.pipeline()
                pipe.hset(user_key, mapping={
                    "username": username,
                    "password_hash": password_hash,
                    "user_type": user_type,
                    "phone": phone,
                    "address": address,
                    "age": age,
                    "gender": gender,
                    "created_at": datetime.utcnow().isoformat()
                })
                pipe.set(username_key, new_id)
                pipe.execute()
                return new_id
            except redis.WatchError:
                # 竞争失败，重试
                continue

@app.route("/api/auth/register", methods=["POST"])
def register():
    data = request.get_json(silent=True) or {}
    username = data.get("username","").strip()
    pwd = data.get("password","")
    user_type = data.get("userType","patient")
    phone = data.get("phone","")
    address = data.get("address","")
    age = int(data.get("age",0) or 0)
    gender = data.get("gender","")
    if not username or not pwd:
        return jsonify(success=False, reason="用户名/密码不能为空"), 400

    pwd_hash = generate_password_hash(pwd)
    new_id = create_user_atomic(username, pwd_hash, user_type, phone, address, age, gender)
    if new_id is None:
        return jsonify(success=False, reason="用户名已存在"), 400
    return jsonify(success=True, userId=int(new_id))

@app.route("/api/auth/login", methods=["POST"])
def login():
    data = request.get_json(silent=True) or {}
    username = data.get("username","").strip()
    pwd = data.get("password","")
    if not username or not pwd:
        return jsonify(success=False, reason="用户名/密码不能为空"), 400

    username_key = f"username:{username}"
    uid = r.get(username_key)
    if not uid:
        return jsonify(success=False, reason="用户不存在"), 400
    user_key = f"user:{uid}"
    pwd_hash = r.hget(user_key, "password_hash")
    user_type = r.hget(user_key, "user_type") or "patient"
    if not pwd_hash or not check_password_hash(pwd_hash, pwd):
        return jsonify(success=False, reason="用户名或密码错误"), 400
    return jsonify(success=True, userId=int(uid), userType=user_type)

def assess_bmi(height_cm, weight_kg):
    h = height_cm / 100.0
    bmi = weight_kg / (h*h) if h > 0 else 0
    if bmi < 18.5: cat = "偏瘦"
    elif bmi < 25: cat = "正常"
    elif bmi < 30: cat = "超重"
    else: cat = "肥胖"
    return bmi, cat

def assess_bp(bp_str):
    m = re.match(r'^\s*(\d{2,3})\s*/\s*(\d{2,3})\s*$', bp_str)
    if not m:
        return "无效"
    sys = int(m.group(1)); dia = int(m.group(2))
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

@app.route("/api/health/submit", methods=["POST"])
def submit_health():
    data = request.get_json(silent=True) or {}
    try:
        user_id = int(data.get("userId", 0))
        height = float(data.get("height", 0))
        weight = float(data.get("weight", 0))
        lung = int(data.get("lung", 0))
        bp = str(data.get("bp","")).strip()
    except Exception:
        return jsonify(success=False, reason="参数解析错误"), 400

    if user_id <= 0:
        return jsonify(success=False, reason="userId 非法"), 400
    if height < 50 or height > 250 or weight < 10 or weight > 500 or lung < 100 or lung > 20000:
        return jsonify(success=False, reason="参数范围错误"), 400
    if not re.match(r'^\s*\d{2,3}\s*/\s*\d{2,3}\s*$', bp):
        return jsonify(success=False, reason="血压格式错误，示例 120/80"), 400

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

    # 生成 record id 并写入 hash，同时把 record id 加入用户记录列表
    record_id = r.incr("next_record_id")
    rec_key = f"record:{record_id}"
    r.hset(rec_key, mapping={
        "user_id": user_id,
        "height": height,
        "weight": weight,
        "bmi": bmi,
        "lung": lung,
        "bp": bp,
        "lung_level": lung_level,
        "bp_level": bp_level,
        "overall": overall,
        "created_at": datetime.utcnow().isoformat()
    })
    # 将记录 id 加入用户的历史列表（最近记录放左侧）
    r.lpush(f"user:{user_id}:records", record_id)

    return jsonify(success=True, bmi=bmi, lungLevel=lung_level, bpLevel=bp_level, overall=overall)
if __name__ == "__main__":
    # 确保 8080 没有被其它进程占用（比如上面的 QTcpServer）
    app.run(host="127.0.0.1", port=8080, debug=True)

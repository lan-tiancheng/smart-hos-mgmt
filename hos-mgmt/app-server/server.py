# This Python file uses the following encoding: utf-8
from flask import Flask, request, jsonify
import os, re
from datetime import datetime

from services import AuthService, AppointmentService, MedicalService, AttendanceService, ChatService
from infra.redis_store import get_redis
from asr_service import load_model, recognize_wav

app = Flask(__name__)

# 可通过环境变量 VOSK_MODEL_DIR 指定中文模型目录（例如 models/vosk-model-small-cn-0.22）
VOSK_MODEL_DIR = os.environ.get("VOSK_MODEL_DIR", os.path.join(os.path.dirname(__file__), "models", "vosk-model-small-cn-0.22"))
try:
    load_model(VOSK_MODEL_DIR)
except Exception as e:
    # 不终止服务；仅在首次访问 /api/asr 时再报错
    app.logger.warning("ASR 模型加载失败：%s", e)

auth_svc = AuthService()
appt_svc = AppointmentService()
med_svc = MedicalService()
att_svc = AttendanceService()
chat_svc = ChatService()

@app.route("/api/asr", methods=["POST"])
def api_asr():
    # multipart/form-data: field name "audio"
    if 'audio' not in request.files:
        return jsonify(success=False, reason="缺少音频文件字段 audio"), 400
    f = request.files['audio']
    if f.filename == '':
        return jsonify(success=False, reason="音频文件名为空"), 400

    # 临时保存并识别
    tmp_dir = os.path.join(os.path.dirname(__file__), "tmp")
    os.makedirs(tmp_dir, exist_ok=True)
    tmp_path = os.path.join(tmp_dir, "asr.wav")
    f.save(tmp_path)

    try:
        # 确保已加载模型
        load_model(VOSK_MODEL_DIR)
        text = recognize_wav(tmp_path)
        return jsonify(success=True, text=text)
    except Exception as e:
        return jsonify(success=False, reason=str(e)), 500

# 其余已有路由（登录/注册/体检提交）保持不变...
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

    r = get_redis()
    r.hset(f"user:{user_id}:last_health", mapping={
        "height": height, "weight": weight, "lung": lung, "bp": bp,
        "bmi": round(bmi, 1),
        "bmiLevel": bmi_cat, "bpLevel": bp_level, "lungLevel": lung_level,
        "overall": overall, "time": datetime.utcnow().isoformat()
    })

    return jsonify(success=True,
                   bmi=round(bmi, 1),
                   lungLevel=lung_level,
                   bpLevel=bp_level,
                   overall=overall)

if __name__ == "__main__":
    app.run(host="127.0.0.1", port=8080, debug=True)

# This Python file uses the following encoding: utf-8
from flask import request, jsonify
from services.chat_service import ChatService
from infra.sqlite_store import get_db

def register_doctor_chat_routes(app, chat_svc: ChatService):
    @app.get("/api/chat/doctor/conversations")
    def api_doctor_conversations():
        """
        列出某医生的会话列表（按最后一条消息时间倒序）
        返回：
        {
          success: true,
          conversations: [
            { id, patient_id, doctor_id, patient_name, last_message, last_at }
          ]
        }
        """
        doctor_id = request.args.get("doctorId", type=int)
        limit = request.args.get("limit", default=100, type=int)
        offset = request.args.get("offset", default=0, type=int)
        if not doctor_id:
            return jsonify(success=False, reason="缺少 doctorId"), 400

        try:
            # 查会话 + 最后一条消息
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
                       COALESCE(p.username, '') AS patient_name,
                       m.content AS last_message,
                       COALESCE(m.created_at, c.created_at) AS last_at
                FROM conversations c
                LEFT JOIN last_msg lm ON lm.conversation_id = c.id
                LEFT JOIN messages m ON m.id = lm.max_id
                LEFT JOIN users p ON p.id = c.patient_id
                WHERE c.doctor_id = ?
                ORDER BY last_at DESC
                LIMIT ? OFFSET ?
                """,
                (doctor_id, limit, offset),
            )
            rows = cur.fetchall()
            data = []
            for r in rows:
                d = dict(r)
                d["id"] = int(d["id"])
                d["patient_id"] = int(d["patient_id"])
                d["doctor_id"] = int(d["doctor_id"])
                data.append(d)
            conn.close()
            return jsonify(success=True, conversations=data)
        except Exception as e:
            return jsonify(success=False, reason=str(e)), 500

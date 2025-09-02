# This Python file uses the following encoding: utf-8
from typing import Optional, Tuple, List, Dict
from infra.sqlite_store import get_db

class ChatService:
    def create_or_get_conversation(self, patient_id: int, doctor_id: int) -> int:
        """
        不存在则创建，存在则返回已有 id。依赖 conversations 上的唯一约束或唯一索引。
        """
        conn = get_db()
        try:
            cur = conn.cursor()
            # 先尝试查找
            cur.execute(
                "SELECT id FROM conversations WHERE patient_id = ? AND doctor_id = ? LIMIT 1",
                (patient_id, doctor_id),
            )
            row = cur.fetchone()
            if row:
                return int(row["id"])

            # 不存在则插入；若并发导致唯一冲突，改为读取
            try:
                cur.execute(
                    "INSERT INTO conversations (patient_id, doctor_id) VALUES (?, ?)",
                    (patient_id, doctor_id),
                )
                conn.commit()
                return int(cur.lastrowid)
            except Exception:
                conn.rollback()
                cur.execute(
                    "SELECT id FROM conversations WHERE patient_id = ? AND doctor_id = ? LIMIT 1",
                    (patient_id, doctor_id),
                )
                row = cur.fetchone()
                if not row:
                    raise
                return int(row["id"])
        finally:
            conn.close()

    def get_conversation_pair(self, conversation_id: int) -> Optional[Tuple[int, int]]:
        conn = get_db()
        try:
            cur = conn.cursor()
            cur.execute(
                "SELECT patient_id, doctor_id FROM conversations WHERE id = ? LIMIT 1",
                (conversation_id,),
            )
            row = cur.fetchone()
            if not row:
                return None
            return int(row["patient_id"]), int(row["doctor_id"])
        finally:
            conn.close()

    def add_message(self, conversation_id: int, sender_id: int, sender_role: str, content: str) -> Dict:
        conn = get_db()
        try:
            cur = conn.cursor()
            cur.execute(
                "INSERT INTO messages (conversation_id, sender_id, sender_role, content) VALUES (?, ?, ?, ?)",
                (conversation_id, sender_id, sender_role, content),
            )
            conn.commit()
            cur.execute(
                "SELECT id, conversation_id, sender_id, sender_role, content, created_at FROM messages WHERE id = ?",
                (cur.lastrowid,),
            )
            row = cur.fetchone()
            return {
                "id": int(row["id"]),
                "conversation_id": int(row["conversation_id"]),
                "sender_id": int(row["sender_id"]),
                "sender_role": row["sender_role"],
                "content": row["content"],
                "created_at": row["created_at"],
            }
        finally:
            conn.close()

    def list_messages(self, conversation_id: int, after_iso: Optional[str] = None, limit: int = 100) -> List[Dict]:
        conn = get_db()
        try:
            cur = conn.cursor()
            if after_iso:
                cur.execute(
                    """
                    SELECT id, conversation_id, sender_id, sender_role, content, created_at
                    FROM messages
                    WHERE conversation_id = ? AND created_at > ?
                    ORDER BY id ASC
                    LIMIT ?
                    """,
                    (conversation_id, after_iso, limit),
                )
            else:
                cur.execute(
                    """
                    SELECT id, conversation_id, sender_id, sender_role, content, created_at
                    FROM messages
                    WHERE conversation_id = ?
                    ORDER BY id ASC
                    LIMIT ?
                    """,
                    (conversation_id, limit),
                )
            rows = cur.fetchall()
            return [
                {
                    "id": int(r["id"]),
                    "conversation_id": int(r["conversation_id"]),
                    "sender_id": int(r["sender_id"]),
                    "sender_role": r["sender_role"],
                    "content": r["content"],
                    "created_at": r["created_at"],
                }
                for r in rows
            ]
        finally:
            conn.close()

from infra.sqlite_store import get_db, init_db

class AuthService:
    def login(self, profession, username, password):
        conn = get_db(profession)
        c = conn.cursor()
        c.execute("SELECT id FROM users WHERE username=? AND password=?", (username, password))
        row = c.fetchone()
        conn.close()
        if row:
            return {"id": row[0]}, None
        else:
            return None, "用户名或密码错误"

    def register_user(self, profession, username, password, patient_info):
        init_db(profession)
        conn = get_db(profession)
        c = conn.cursor()
        try:
            for key in ["gender", "phone", "address", "age"]:
                if key not in patient_info:
                    raise ValueError(f"缺少字段: {key}")
            c.execute(
                "INSERT INTO users (username, password, gender, phone, address, age) VALUES (?, ?, ?, ?, ?, ?)",
                (username, password, patient_info["gender"], patient_info["phone"], patient_info["address"], patient_info["age"])
            )
            uid = c.lastrowid
            conn.commit()
            return uid, None
        except Exception as e:
            print("注册失败:", repr(e))
            return None, str(e)
        finally:
            conn.close()

    def get_patient_info(self, profession, user_id):
        conn = get_db(profession)
        c = conn.cursor()
        c.execute("SELECT username, phone, address, age, gender FROM users WHERE id=?", (user_id,))
        row = c.fetchone()
        conn.close()
        if row:
            return {
                "username": row[0], "phone": row[1], "address": row[2],
                "age": row[3], "gender": row[4]
            }
        else:
            return None

    def update_patient_info(self, profession, user_id, username, phone, address, age, gender):
        conn = get_db(profession)
        c = conn.cursor()
        c.execute("""UPDATE users SET username=?, phone=?, address=?, age=?, gender=? WHERE id=?""",
                    (username, phone, address, age, gender, user_id))
        conn.commit()
        conn.close()
        return True

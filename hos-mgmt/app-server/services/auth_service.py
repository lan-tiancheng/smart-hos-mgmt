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
            for key in ["gender", "phone", "address", "age", "dob", "idCard", "email"]:
                if key not in patient_info:
                    patient_info[key] = ""  # 缺失字段默认空
            c.execute(
                "INSERT INTO users (username, password, gender, phone, address, age, dob, idCard, email) "
                "VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?)",
                (
                    username, password,
                    patient_info["gender"],
                    patient_info["phone"],
                    patient_info["address"],
                    patient_info["age"],
                    patient_info["dob"],
                    patient_info["idCard"],
                    patient_info["email"]
                )
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
        c.execute(
            "SELECT username, phone, address, age, gender, dob, idCard, email "
            "FROM users WHERE id=?", (user_id,)
        )
        row = c.fetchone()
        conn.close()
        if row:
            return {
                "username": row[0],
                "phone": row[1],
                "address": row[2],
                "age": row[3],
                "gender": row[4],
                "dob": row[5] or "",
                "idCard": row[6] or "",
                "email": row[7] or ""
            }
        else:
            return None

    def update_patient_info(self, profession, user_id, username, phone, address, age, gender, dob="", idCard="", email=""):
        conn = get_db(profession)
        c = conn.cursor()
        c.execute(
            "UPDATE users SET username=?, phone=?, address=?, age=?, gender=?, dob=?, idCard=?, email=? WHERE id=?",
            (username, phone, address, age, gender, dob, idCard, email, user_id)
        )
        conn.commit()
        conn.close()
        return True

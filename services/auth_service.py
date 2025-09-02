from infra.sqlite_store import get_db, init_db

class AuthService:
    def update_doctor_info(self, profession, doctor_id, name, hospital, department, profile, work_time, fee, max_patients, photo=""):
            """
            profession: 'doctor'
            doctor_id: 医生编号（可作为用户名或id）
            其他字段对应 doctorData
            """
            try:
                conn = get_db(profession)
                c = conn.cursor()

                # 类型和空值处理
                fee = float(fee) if fee else 0
                max_patients = int(max_patients) if max_patients else 0
                name = name or ""
                hospital = hospital or ""
                department = department or ""
                profile = profile or ""
                work_time = work_time or ""
                photo = photo or ""

                # UPDATE 操作，如果医生已存在则更新，否则插入新记录
                # 假设 username 用 doctor_id 存储唯一标识
                c.execute("SELECT id FROM users WHERE username=?", (doctor_id,))
                row = c.fetchone()
                if row:
                    c.execute("""
                        UPDATE users
                        SET username=?, address=?, gender=?, age=?, dob=?, phone=?, email=?, hospital=?, department=?, profile=?, work_time=?, fee=?, max_patients=?, photo=?
                        WHERE id=?
                    """, (doctor_id, "", "", 0, "", "", "", hospital, department, profile, work_time, fee, max_patients, photo, row[0]))
                else:
                    c.execute("""
                        INSERT INTO users (username, hospital, department, profile, work_time, fee, max_patients, photo)
                        VALUES (?, ?, ?, ?, ?, ?, ?, ?)
                    """, (doctor_id, hospital, department, profile, work_time, fee, max_patients, photo))
                conn.commit()
                return True, None
            except Exception as e:
                print("保存医生信息失败:", e)
                return False, str(e)
            finally:
                conn.close()
    def update_patient_info(self, profession, user_id, username, phone, address, age, gender, dob="", idCard="", email=""):
            try:
                conn = get_db(profession)
                c = conn.cursor()
                age = int(age) if age else 0
                gender = gender or ""
                dob = dob or ""
                idCard = idCard or ""
                email = email or ""

                c.execute(
                    "UPDATE users SET username=?, phone=?, address=?, age=?, gender=?, dob=?, idCard=?, email=? WHERE id=?",
                    (username, phone, address, age, gender, dob, idCard, email, user_id)
                )
                conn.commit()
                return True, None
            except sqlite3.IntegrityError as e:
                return False, "用户名已存在或唯一约束冲突"
            except Exception as e:
                print("更新患者信息失败:", e)
                return False, str(e)
            finally:
                conn.close()
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
            # 默认值处理
            for key in ["gender", "phone", "address", "age", "dob", "idCard", "email"]:
                if key not in patient_info:
                    patient_info[key] = ""
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
            try:
                conn = get_db(profession)
                c = conn.cursor()
                # 类型和空值处理
                age = int(age) if age else 0
                gender = gender or ""
                dob = dob or ""
                idCard = idCard or ""
                email = email or ""

                c.execute(
                    "UPDATE users SET username=?, phone=?, address=?, age=?, gender=?, dob=?, idCard=?, email=? WHERE id=?",
                    (username, phone, address, age, gender, dob, idCard, email, user_id)
                )
                conn.commit()
                return True, None
            except sqlite3.IntegrityError as e:
                return False, "用户名已存在或唯一约束冲突"
            except Exception as e:
                print("更新患者信息失败:", e)
                return False, str(e)
            finally:
                conn.close()



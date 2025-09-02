import sqlite3
import threading
import os

_db_path = "hos_app.db"
_lock = threading.Lock()

def get_db(profession=None):
    """
    根据职业获取数据库连接
    """
    if profession is None:
        db_path = "db/default.sqlite"
    else:
        db_path = f"db/{profession}.sqlite"

    # 确保 db 文件夹存在
    os.makedirs(os.path.dirname(db_path), exist_ok=True)
    conn = sqlite3.connect(db_path)

    # 自动建表
    c = conn.cursor()
    if profession == "patient":
        c.execute("""
            CREATE TABLE IF NOT EXISTS users (
                id INTEGER PRIMARY KEY AUTOINCREMENT,
                username TEXT UNIQUE,
                password TEXT,
                gender TEXT,
                phone TEXT,
                address TEXT,
                age INTEGER,
                dob TEXT,
                idCard TEXT,
                email TEXT
            )
        """)
        c.execute("""
            CREATE TABLE IF NOT EXISTS health (
                id INTEGER PRIMARY KEY AUTOINCREMENT,
                user_id INTEGER,
                height REAL,
                weight REAL,
                lung INTEGER,
                bp TEXT,
                bmi REAL,
                bmiLevel TEXT,
                bpLevel TEXT,
                lungLevel TEXT,
                overall TEXT,
                time TEXT
            )
        """)
    elif profession == "doctors":
        c.execute("""
            CREATE TABLE IF NOT EXISTS doctor (
                id INTEGER PRIMARY KEY AUTOINCREMENT,
                doctor_id TEXT UNIQUE,
                name TEXT,
                hospital TEXT,
                department TEXT,
                profile TEXT,
                work_time TEXT,
                fee REAL,
                max_patients INTEGER,
                photo TEXT
            )
        """)


    conn.commit()
    return conn


def init_db(professions=("patient", "doctor")):
    """
    初始化所有职业的数据库和表结构。
    professions: 可自定义职业列表
    """
    with _lock:
        for profession in professions:
            conn = get_db(profession)
            conn.close()

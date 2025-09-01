import sqlite3
import threading

_db_path = "hos_app.db"
_lock = threading.Lock()

def get_db(profession=None):
    if profession is None:
        # 用默认数据库
        db_path = "db/default.sqlite"
    else:
        # 用分职业数据库
        db_path = f"db/{profession}.sqlite"
    db_name = f"{profession.lower()}.db"
    conn = sqlite3.connect(db_name)
    # 自动建表
    c = conn.cursor()
    c.execute("""
        CREATE TABLE IF NOT EXISTS users (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            username TEXT UNIQUE,
            password TEXT,
            gender TEXT,
            phone TEXT,
            address TEXT,
            age INTEGER
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

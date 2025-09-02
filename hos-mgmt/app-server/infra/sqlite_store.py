# This Python file uses the following encoding: utf-8
import os
import sqlite3
import threading
from typing import Optional, Iterable

# 可通过环境变量覆盖数据库目录（默认使用项目根下的 db/ 目录）
BASE_DIR = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
DB_DIR = os.environ.get("DB_DIR", os.path.join(BASE_DIR, "db"))

_lock = threading.Lock()

def _normalize_profession(profession: Optional[str]) -> Optional[str]:
    if profession is None:
        return None
    p = str(profession).strip()
    return p.lower() if p else None

def _db_path_for(profession: Optional[str]) -> str:
    """
    None -> db/default.sqlite
    'patient' -> db/patient.sqlite
    'doctor' -> db/doctor.sqlite
    其他 -> db/<profession>.sqlite
    """
    p = _normalize_profession(profession)
    fname = "default.sqlite" if p is None else f"{p}.sqlite"
    os.makedirs(DB_DIR, exist_ok=True)
    return os.path.join(DB_DIR, fname)

def _ensure_pragmas(conn: sqlite3.Connection) -> None:
    c = conn.cursor()
    # 提升并发与数据一致性
    c.execute("PRAGMA journal_mode=WAL;")
    c.execute("PRAGMA synchronous=NORMAL;")
    c.execute("PRAGMA foreign_keys=ON;")

def _ensure_schema(conn: sqlite3.Connection) -> None:
    """
    统一初始化需要的表：
    - users     （用户信息）
    - health    （健康评估）
    - conversations/messages（聊天会话与消息，避免会话创建 500）
    """
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
    c.execute("""
        CREATE TABLE IF NOT EXISTS conversations (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            patient_id INTEGER NOT NULL,
            doctor_id INTEGER NOT NULL,
            created_at TEXT DEFAULT CURRENT_TIMESTAMP
        )
    """)
    # 会话唯一约束（若已存在不会报错）
    c.execute("CREATE UNIQUE INDEX IF NOT EXISTS idx_conversation_unique ON conversations(patient_id, doctor_id)")
    c.execute("""
        CREATE TABLE IF NOT EXISTS messages (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            conversation_id INTEGER NOT NULL,
            sender_id INTEGER NOT NULL,
            sender_role TEXT NOT NULL,  -- 'patient' | 'doctor' | 'ai'
            content TEXT NOT NULL,
            created_at TEXT DEFAULT CURRENT_TIMESTAMP
        )
    """)
    conn.commit()

def get_db(profession: Optional[str] = None) -> sqlite3.Connection:
    """
    获取指定职业库连接（或默认库）：
    - 默认库：db/default.sqlite
    - 指定库：db/<profession>.sqlite（小写）
    连接配置：
    - check_same_thread=False 方便在多线程（WS/异步）场景中使用
    - row_factory=sqlite3.Row 返回 dict 风格记录
    - 应用 WAL、foreign_keys 等 PRAGMA
    每次获取都会确保表结构存在。
    """
    path = _db_path_for(profession)
    conn = sqlite3.connect(path, check_same_thread=False)
    conn.row_factory = sqlite3.Row
    _ensure_pragmas(conn)
    _ensure_schema(conn)
    return conn

def init_db(professions: Iterable[str] = ("patient", "doctor")) -> None:
    """
    初始化默认库与各职业库的表结构。
    - 默认库：用于通用数据或未区分职业的数据
    - professions：可自定义职业列表（例如: ["patient", "doctor", "nurse"]）
    """
    with _lock:
        # 先初始化默认库
        conn = get_db(None)
        conn.close()
        # 再初始化各职业库
        for profession in professions:
            conn = get_db(profession)
            conn.close()

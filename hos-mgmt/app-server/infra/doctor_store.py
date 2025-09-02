# -*- coding: utf-8 -*-
import os
import sqlite3
from typing import List, Dict, Any, Optional

# doctor.db 默认放在项目根目录（与 app.py 同级）
# 可通过环境变量 DOCTOR_DB_PATH 覆盖
PROJECT_ROOT = os.path.abspath(os.path.join(os.path.dirname(__file__), ".."))
DEFAULT_DB_PATH = os.path.join(PROJECT_ROOT, "doctor.db")
DOCTOR_DB_PATH = os.environ.get("DOCTOR_DB_PATH", DEFAULT_DB_PATH)

def _connect() -> sqlite3.Connection:
    conn = sqlite3.connect(DOCTOR_DB_PATH)
    conn.row_factory = sqlite3.Row
    return conn

def _table_columns(conn: sqlite3.Connection, table: str) -> set:
    cols = set()
    try:
        for r in conn.execute(f"PRAGMA table_info({table})").fetchall():
            # name 在不同驱动返回位置可能不同，这里两种都兼容
            cols.add(r["name"] if "name" in r.keys() else r[1])
    except Exception:
        pass
    return cols

def ensure_schema():
    """
    可选：若数据库不存在 users 表，则创建一个最小结构，便于联调。
    生产环境可移除此函数。
    """
    conn = _connect()
    try:
        conn.execute("""
            CREATE TABLE IF NOT EXISTS users (
                id INTEGER PRIMARY KEY AUTOINCREMENT,
                username TEXT NOT NULL UNIQUE
            )
        """)
        conn.commit()
    finally:
        conn.close()

def list_doctors(q: Optional[str] = "", limit: int = 100) -> List[Dict[str, Any]]:
    """
    从 doctor.db 的 users 表读取医生列表（该库仅存医生）。
    为了兼容不同表结构，最少返回：
      - id, name（从 username 映射），并回传 username
      - department, title（若列不存在则返回空字符串）
    支持关键字搜索 q（匹配 username 或 name 列，如果存在）。
    """
    conn = _connect()
    try:
        cols = _table_columns(conn, "users")
        if "id" not in cols or ("username" not in cols and "name" not in cols):
            # 基本列都不存在，返回空列表
            return []

        select_cols = ["id"]
        if "username" in cols:
            select_cols.append("username")
        if "name" in cols:
            select_cols.append("name")
        if "department" in cols:
            select_cols.append("department")
        if "title" in cols:
            select_cols.append("title")

        sql = f"SELECT {', '.join(select_cols)} FROM users"
        params: list = []
        where = []
        if q:
            if "name" in cols and "username" in cols:
                where.append("(name LIKE ? OR username LIKE ?)")
                params.extend([f"%{q}%", f"%{q}%"])
            elif "name" in cols:
                where.append("name LIKE ?")
                params.append(f"%{q}%")
            elif "username" in cols:
                where.append("username LIKE ?")
                params.append(f"%{q}%")

        if where:
            sql += " WHERE " + " AND ".join(where)
        sql += " ORDER BY id ASC LIMIT ?"
        params.append(limit)

        rows = conn.execute(sql, params).fetchall()
        data: List[Dict[str, Any]] = []
        for r in rows:
            d = dict(r)
            username = d.get("username") or d.get("name") or f"doctor_{d['id']}"
            name = d.get("name") or username
            department = d.get("department", "")
            title = d.get("title", "")
            data.append({
                "id": d["id"],
                "name": name,          # 前端 QML 使用 model.name
                "username": username,  # 备用
                "department": department,
                "title": title,
            })
        return data
    finally:
        conn.close()

# -*- coding: utf-8 -*-
import os
import sqlite3
from typing import List, Dict, Any

BASE_DIR = os.path.abspath(os.path.join(os.path.dirname(__file__), ".."))
DEFAULT_DB_PATH = os.path.join(BASE_DIR, "doctor.db")
DOCTOR_DB_PATH = os.environ.get("DOCTOR_DB_PATH", DEFAULT_DB_PATH)

def _connect() -> sqlite3.Connection:
    conn = sqlite3.connect(DOCTOR_DB_PATH)
    conn.row_factory = sqlite3.Row
    return conn

def _table_columns(conn: sqlite3.Connection, table: str) -> set:
    cur = conn.execute(f"PRAGMA table_info({table})")
    return {row["name"] for row in cur.fetchall()}

def _map_doctor_row(row: sqlite3.Row, columns: set) -> Dict[str, Any]:
    def pick(keys, default=""):
        for k in keys:
            if k in columns and row[k] is not None:
                return row[k]
        return default

    doc_id = pick(["id", "user_id", "uid"], 0)
    username = pick(["username", "name", "real_name", "full_name"], f"doctor_{doc_id}")
    department = pick(["department", "dept", "department_name", "dept_name"], "")
    title = pick(["title", "job_title", "position", "professional_title"], "")

    try:
        doc_id = int(doc_id)
    except Exception:
        pass

    return {
        "id": doc_id,
        "username": str(username),
        "department": str(department),
        "title": str(title),
    }

def list_doctors(q: str = "", limit: int = 100) -> List[Dict[str, Any]]:
    """
    从 doctor.db 的 user 表读取医生列表。
    统一返回：id, username, department, title
    支持关键字搜索 q（匹配 username/name）
    """
    conn = _connect()
    try:
        cols = _table_columns(conn, "user")
        where = []
        params: list = []
        if q:
            like_cols = []
            if "username" in cols:
                like_cols.append("username")
            if "name" in cols:
                like_cols.append("name")
            if like_cols:
                where.append("(" + " OR ".join(f"{c} LIKE ?" for c in like_cols) + ")")
                params.extend([f"%{q}%"] * len(like_cols))
        where_sql = " WHERE " + " AND ".join(where) if where else ""
        if "username" in cols:
            order_sql = " ORDER BY username"
        elif "name" in cols:
            order_sql = " ORDER BY name"
        else:
            order_sql = " ORDER BY id"

        sql = f"SELECT * FROM user{where_sql}{order_sql} LIMIT ?"
        params.append(limit)
        rows = conn.execute(sql, params).fetchall()
        return [_map_doctor_row(r, cols) for r in rows]
    finally:
        conn.close()

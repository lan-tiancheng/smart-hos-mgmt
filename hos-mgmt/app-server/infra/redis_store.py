# This Python file uses the following encoding: utf-8

# if __name__ == "__main__":
#     pass
import redis
from typing import Callable, Optional, Dict, Any, Tuple

# 单例 Redis 连接（decode_responses=True 直接返回 str）
_redis_instance: Optional[redis.Redis] = None

def get_redis() -> redis.Redis:
    global _redis_instance
    if _redis_instance is None:
        _redis_instance = redis.Redis(host='127.0.0.1', port=6379, db=0, decode_responses=True)
    return _redis_instance

class TxnError(Exception):
    pass

def atomic_create_with_uniques(
    r: redis.Redis,
    id_counter_key: str,
    unique_checks: Tuple[Tuple[str, str], ...],  # (index_key, index_value) -> ensure not exists
    write_hash_key_fn: Callable[[int], str],
    write_hash_mapping: Dict[str, Any],
    set_unique_index_fns: Tuple[Callable[[int], Tuple[str, str]], ...] = (),
) -> int:
    """
    - 先 WATCH 所有唯一索引键，确保不存在
    - INCR id 生成新 ID
    - 写入主体 hash
    - 建立唯一索引（如 username:{name} -> user_id）
    """
    watch_keys = [k for (k, _) in unique_checks]
    with r.pipeline() as pipe:
        while True:
            try:
                if watch_keys:
                    pipe.watch(*watch_keys)
                # 唯一性检查
                for key, _ in unique_checks:
                    if r.exists(key):
                        pipe.unwatch()
                        raise TxnError(f"Unique key already exists: {key}")

                pipe.multi()
                new_id = pipe.incr(id_counter_key)
                pipe.execute()
                new_id = int(r.get(id_counter_key))

                # 写主体 hash
                hk = write_hash_key_fn(new_id)
                r.hset(hk, mapping=write_hash_mapping)

                # 建唯一索引
                for fn in set_unique_index_fns:
                    idx_key, idx_val = fn(new_id)
                    # 通常 value=新ID
                    r.set(idx_key, idx_val)

                return new_id
            except redis.WatchError:
                continue

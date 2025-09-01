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
    unique_checks: Tuple[Tuple[str, str], ...],
    write_hash_key_fn: Callable[[int], str],
    write_hash_mapping: Dict[str, Any],
    set_unique_index_fns: Tuple[Callable[[int], Tuple[str, str]], ...] = (),
    max_retries: int = 5,   # 防止无限卡死
) -> int:
    watch_keys = [k for (k, _) in unique_checks]
    for attempt in range(max_retries):
        with r.pipeline() as pipe:
            try:
                if watch_keys:
                    pipe.watch(*watch_keys)

                # 唯一性检查
                for key, _ in unique_checks:
                    if r.exists(key):
                        pipe.unwatch()
                        raise TxnError(f"Unique key already exists: {key}")

                # 生成新 ID
                pipe.multi()
                pipe.incr(id_counter_key)
                pipe.execute()
                new_id = int(r.get(id_counter_key))

                # 写主体 hash
                hk = write_hash_key_fn(new_id)
                r.hset(hk, mapping=write_hash_mapping)

                # 写唯一索引
                for fn in set_unique_index_fns:
                    idx_key, idx_val = fn(new_id)
                    r.set(idx_key, idx_val)

                return new_id

            except redis.WatchError:
                continue

    raise TxnError("Transaction failed after max retries")

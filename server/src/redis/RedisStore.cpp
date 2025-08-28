#include "RedisStore.h"
#include <sw/redis++/redis++.h>
#include <QDebug>
#include <unordered_map>

using sw::redis::Redis;
using sw::redis::ConnectionOptions;
using sw::redis::ConnectionPoolOptions;

RedisStore& RedisStore::instance() {
    static RedisStore inst;
    return inst;
}

bool RedisStore::init(const ServerConfig& cfg) {
    try {
        ConnectionOptions opts;
        opts.host = cfg.redisHost.toStdString();
        opts.port = cfg.redisPort;
        if (!cfg.redisPassword.isEmpty()) opts.password = cfg.redisPassword.toStdString();
        opts.db = cfg.redisDb;
        opts.socket_timeout = std::chrono::milliseconds(2000);

        ConnectionPoolOptions pool;
        pool.size = cfg.redisPoolSize > 0 ? cfg.redisPoolSize : 4;
        pool.wait_timeout = std::chrono::milliseconds(1000);
        pool.connection_lifetime = std::chrono::minutes(10);

        redis_ = std::make_shared<Redis>(opts, pool);
        auto pong = redis_->ping();
        qInfo() << "Redis ping:" << QString::fromStdString(pong);
        return true;
    } catch (const std::exception& e) {
        qCritical() << "Redis init error:" << e.what();
        return false;
    }
}

std::optional<User> RedisStore::findUserByEmail(const QString& email) {
    if (!redis_) return std::nullopt;
    try {
        auto key = "u:email:" + email.toStdString();
        auto idOpt = redis_->get(key);
        if (!idOpt) return std::nullopt;
        qint64 id = std::stoll(*idOpt);
        return findUserById(id);
    } catch (const std::exception& e) {
        qWarning() << "findUserByEmail error:" << e.what();
        return std::nullopt;
    }
}

std::optional<User> RedisStore::findUserById(qint64 id) {
    if (!redis_) return std::nullopt;
    try {
        auto key = "user:" + std::to_string(id);
        std::unordered_map<std::string, std::string> h;
        redis_->hgetall(key, std::inserter(h, h.begin()));
        if (h.empty()) return std::nullopt;

        User u;
        u.id = id;
        u.email = QString::fromStdString(h["email"]);
        u.role = QString::fromStdString(h["role"]);
        u.name = QString::fromStdString(h["name"]);
        u.passwordHash = QString::fromStdString(h["pass_hash"]);
        u.salt = QString::fromStdString(h["salt"]);
        u.createdAt = QString::fromStdString(h["created_at"]);
        return u;
    } catch (const std::exception& e) {
        qWarning() << "findUserById error:" << e.what();
        return std::nullopt;
    }
}

qint64 RedisStore::createUser(const User& user) {
    if (!redis_) return -1;
    try {
        // 生成新 ID
        auto newId = redis_->incr("counters:user:id");
        std::string idStr = std::to_string(newId);

        // 邮箱唯一索引
        auto idxKey = "u:email:" + user.email.toStdString();
        bool setnx_ok = redis_->setnx(idxKey, idStr);
        if (!setnx_ok) {
            return -1; // email 冲突
        }
        // 写入 Hash
        std::string userKey = "user:" + idStr;
        auto pipe = redis_->pipeline();
        pipe.hset(userKey, "email", user.email.toStdString());
        pipe.hset(userKey, "role", user.role.toStdString());
        pipe.hset(userKey, "name", user.name.toStdString());
        pipe.hset(userKey, "pass_hash", user.passwordHash.toStdString());
        pipe.hset(userKey, "salt", user.salt.toStdString());
        pipe.hset(userKey, "created_at", user.createdAt.toStdString());
        pipe.exec();

        return std::stoll(idStr);
    } catch (const std::exception& e) {
        qWarning() << "createUser error:" << e.what();
        return -1;
    }
}
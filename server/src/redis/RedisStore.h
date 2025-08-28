#pragma once
#include <optional>
#include <memory>
#include <QString>
#include "../ServerConfig.h"
#include "../models/User.h"

namespace sw { namespace redis { class Redis; } }

class RedisStore {
public:
    static RedisStore& instance();
    bool init(const ServerConfig& cfg);

    std::optional<User> findUserByEmail(const QString& email);
    std::optional<User> findUserById(qint64 id);
    qint64 createUser(const User& user);

private:
    RedisStore() = default;
    std::shared_ptr<sw::redis::Redis> redis_;
};

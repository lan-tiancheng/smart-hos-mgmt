#include "AuthHandler.h"
#include "../redis/RedisStore.h"
#include "../models/User.h"
#include "common/Utils.h"
#include <QDateTime>

AuthResult AuthHandler::registerUser(const QString& email, const QString& password, const QString& role, const QString& name) {
    AuthResult res;
    auto& store = RedisStore::instance();
    if (store.findUserByEmail(email).has_value()) {
        res.code = 409; res.message = "email already exists"; return res;
    }
    QString salt = Utils::randomSalt();
    QString hash = Utils::hashPassword(password, salt);

    User u;
    u.email = email;
    u.role = role.isEmpty() ? "patient" : role;
    u.name = name;
    u.salt = salt;
    u.passwordHash = hash;
    u.createdAt = QDateTime::currentDateTimeUtc().toString(Qt::ISODate);

    auto id = store.createUser(u);
    if (id <= 0) { res.code = 500; res.message = "failed to create user"; return res; }
    res.ok = true; res.userId = id; res.role = u.role; res.name = u.name;
    return res;
}

AuthResult AuthHandler::login(const QString& email, const QString& password) {
    AuthResult res;
    auto& store = RedisStore::instance();
    auto uopt = store.findUserByEmail(email);
    if (!uopt.has_value()) { res.code = 404; res.message = "user not found"; return res; }
    auto u = uopt.value();
    QString hash = Utils::hashPassword(password, u.salt);
    if (hash != u.passwordHash) { res.code = 401; res.message = "invalid credentials"; return res; }
    res.ok = true; res.userId = u.id; res.role = u.role; res.name = u.name;
    return res;
}
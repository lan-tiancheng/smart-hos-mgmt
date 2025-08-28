#include "Router.h"
#include "handlers/AuthHandler.h"
#include "common/Protocol.h"

Router::Router() {}

QJsonObject Router::route(const QJsonObject& req) {
    const QString action = req.value("action").toString();
    if (action == "auth.register") return handleAuthRegister(req);
    if (action == "auth.login")    return handleAuthLogin(req);
    return notFound(action);
}

QJsonObject Router::notFound(const QString& action) {
    return Protocol::error(action, 404, "action not found");
}

QJsonObject Router::badRequest(const QString& action, const QString& msg) {
    return Protocol::error(action, 400, msg);
}

QJsonObject Router::handleAuthRegister(const QJsonObject& req) {
    auto data = req.value("data").toObject();
    QString email = data.value("email").toString();
    QString password = data.value("password").toString();
    QString role = data.value("role").toString("patient");
    QString name = data.value("name").toString();
    if (email.isEmpty() || password.isEmpty()) {
        return badRequest("auth.register", "email/password required");
    }
    AuthHandler h;
    auto r = h.registerUser(email, password, role, name);
    if (!r.ok) return Protocol::error("auth.register", r.code, r.message);
    QJsonObject out; out["user_id"] = r.userId; out["role"] = role;
    return Protocol::ok("auth.register", out);
}

QJsonObject Router::handleAuthLogin(const QJsonObject& req) {
    auto data = req.value("data").toObject();
    QString email = data.value("email").toString();
    QString password = data.value("password").toString();
    if (email.isEmpty() || password.isEmpty()) {
        return badRequest("auth.login", "email/password required");
    }
    AuthHandler h;
    auto r = h.login(email, password);
    if (!r.ok) return Protocol::error("auth.login", r.code, r.message);
    QJsonObject out; out["user_id"] = r.userId; out["role"] = r.role; out["name"] = r.name;
    return Protocol::ok("auth.login", out);
}
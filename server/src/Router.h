#pragma once
#include <QJsonObject>

class Router {
public:
    Router();
    QJsonObject route(const QJsonObject& req);

private:
    QJsonObject notFound(const QString& action);
    QJsonObject badRequest(const QString& action, const QString& msg);

    QJsonObject handleAuthRegister(const QJsonObject& req);
    QJsonObject handleAuthLogin(const QJsonObject& req);
};

#pragma once
#include <QString>

struct AuthResult {
    bool ok = false;
    int code = 0;
    QString message;
    qint64 userId = 0;
    QString role;
    QString name;
};

class AuthHandler {
public:
    AuthResult registerUser(const QString& email, const QString& password, const QString& role, const QString& name);
    AuthResult login(const QString& email, const QString& password);
};

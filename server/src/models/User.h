#pragma once
#include <QString>

struct User {
    qint64 id = 0;
    QString email;
    QString role;   // patient / doctor / admin
    QString name;
    QString passwordHash;
    QString salt;
    QString createdAt;
};

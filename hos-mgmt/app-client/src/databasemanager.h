#pragma once

#include <QSqlError>
#include <QDebug>
#include <QString>
#include <QSqlDatabase>

class DatabaseManager
{
public:
    DatabaseManager(const QString& dbPath = "smart_hos_mgmt.db");
    ~DatabaseManager();

    QSqlDatabase database() const;

private:
    QSqlDatabase db;
};

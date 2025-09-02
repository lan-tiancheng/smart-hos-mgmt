#include "databasemanager.h"

DatabaseManager::DatabaseManager(const QString& dbPath)
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(dbPath);
    if (!db.open()) {
        qWarning() << "无法打开数据库:" << db.lastError().text();
    } else {
        qDebug() << "SQLite数据库连接成功:" << dbPath;
    }
}

DatabaseManager::~DatabaseManager()
{
    db.close();
}

QSqlDatabase DatabaseManager::database() const
{
    return db;
}

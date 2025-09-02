#pragma once

#include <QSqlDatabase>
#include <QSqlError>
#include <QDebug>
#include <QString>

class DatabaseManager
{
public:
    // 构造函数保持原语义：传入路径时立即打开数据库
    // 可选传入连接名，避免与其他地方的默认连接冲突
    explicit DatabaseManager(const QString& dbPath = "smart_hos_mgmt.db",
                             const QString& connectionName = QString());
    ~DatabaseManager();

    // 重新打开/切换数据库（可更换路径与连接名）
    bool open(const QString& dbPath, const QString& connectionName = QString());

    // 关闭并移除该连接
    void close();

    // 访问底层 QSqlDatabase
    QSqlDatabase database() const;

    // 状态与信息
    bool isOpen() const;
    QString databasePath() const { return m_dbPath; }
    QString connectionName() const { return m_connName; }

    // 环境检查
    static bool hasSqliteDriver();

    // 可选：确保 users 表存在（使用你给出的表结构）
    bool ensureUsersTable();

private:
    // 内部辅助：生成一个稳定的连接名
    static QString makeConnectionName(const QString& suggested, const QString& dbPath);

private:
    QSqlDatabase m_db;
    QString m_dbPath;
    QString m_connName;
};

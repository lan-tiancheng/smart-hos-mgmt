#include "databasemanager.h"

#include <QSqlQuery>
#include <QCoreApplication>
#include <QFileInfo>

static const char* kDefaultDriver = "QSQLITE";

DatabaseManager::DatabaseManager(const QString& dbPath, const QString& connectionName)
{
    if (!dbPath.isEmpty()) {
        open(dbPath, connectionName);
    }
}

DatabaseManager::~DatabaseManager()
{
    close();
}

bool DatabaseManager::hasSqliteDriver()
{
    return QSqlDatabase::isDriverAvailable(kDefaultDriver);
}

QString DatabaseManager::makeConnectionName(const QString& suggested, const QString& dbPath)
{
    // 优先使用调用者给的连接名；否则用文件名派生一个连接名，避免默认连接冲突
    if (!suggested.trimmed().isEmpty())
        return suggested.trimmed();

    const QString base = QFileInfo(dbPath).completeBaseName();
    QString conn = QString("%1_conn").arg(base.isEmpty() ? "sqlite" : base);

    // 若重名则追加序号
    int idx = 1;
    QString tryName = conn;
    while (QSqlDatabase::contains(tryName)) {
        tryName = QString("%1_%2").arg(conn).arg(idx++);
    }
    return tryName;
}

bool DatabaseManager::open(const QString& dbPath, const QString& connectionName)
{
    // 若已打开且同一路径，直接返回
    if (m_db.isValid() && m_db.isOpen() && dbPath == m_dbPath)
        return true;

    // 先关闭旧连接
    close();

    if (!hasSqliteDriver()) {
        qWarning() << "[DB] QSQLITE driver not available";
        return false;
    }

    m_dbPath = dbPath;
    m_connName = makeConnectionName(connectionName, dbPath);

    // 若连接名已存在，直接复用；否则新建
    if (QSqlDatabase::contains(m_connName)) {
        m_db = QSqlDatabase::database(m_connName);
    } else {
        m_db = QSqlDatabase::addDatabase(kDefaultDriver, m_connName);
        m_db.setDatabaseName(m_dbPath);
    }

    if (!m_db.isOpen() && !m_db.open()) {
        qWarning() << "[DB] 打开数据库失败:" << m_db.lastError().text() << " path=" << m_dbPath;
        // 打开失败时清理连接名，避免脏状态
        QString badConn = m_connName;
        m_db = QSqlDatabase(); // 先置空句柄
        QSqlDatabase::removeDatabase(badConn);
        m_connName.clear();
        return false;
    }

    qDebug() << "[DB] SQLite数据库连接成功:" << m_dbPath << " conn=" << m_connName;
    return true;
}

void DatabaseManager::close()
{
    if (!m_db.isValid())
        return;

    const QString connName = m_connName;
    if (m_db.isOpen())
        m_db.close();

    // 按 Qt 文档要求：先让所有 QSqlDatabase 实例离开作用域/置空，再 removeDatabase
    m_db = QSqlDatabase();
    if (!connName.isEmpty() && QSqlDatabase::contains(connName)) {
        QSqlDatabase::removeDatabase(connName);
    }

    m_connName.clear();
    m_dbPath.clear();
}

QSqlDatabase DatabaseManager::database() const
{
    return m_db;
}

bool DatabaseManager::isOpen() const
{
    return m_db.isValid() && m_db.isOpen();
}

bool DatabaseManager::ensureUsersTable()
{
    if (!isOpen())
        return false;

    QSqlQuery q(m_db);
    const char* createUsers =
        "CREATE TABLE IF NOT EXISTS users ("
        " id INTEGER PRIMARY KEY AUTOINCREMENT,"
        " username TEXT UNIQUE,"
        " password TEXT,"
        " gender TEXT,"
        " phone TEXT,"
        " address TEXT,"
        " age INTEGER"
        ")";
    if (!q.exec(createUsers)) {
        qWarning() << "[DB] 创建/确认 users 表失败:" << q.lastError().text();
        return false;
    }
    return true;
}

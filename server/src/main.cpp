#include <QCoreApplication>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QDebug>
#include "ServerConfig.h"
#include "TcpServer.h"
#include "redis/RedisStore.h"

static QJsonObject loadJsonFile(const QString& path) {
    QFile f(path);
    if (!f.open(QIODevice::ReadOnly)) return {};
    auto doc = QJsonDocument::fromJson(f.readAll());
    return doc.isObject() ? doc.object() : QJsonObject{};
}

int main(int argc, char* argv[]) {
    QCoreApplication app(argc, argv);
    app.setApplicationName("smart_hos_server");

    // 读取配置
    QJsonObject js = loadJsonFile("config/server_config.json");
    ServerConfig cfg;
    cfg.port = js.value("port").toInt(5555);
    cfg.redisHost = js.value("redis_host").toString("127.0.0.1");
    cfg.redisPort = static_cast<uint16_t>(js.value("redis_port").toInt(6379));
    cfg.redisDb = js.value("redis_db").toInt(0);
    cfg.redisPassword = js.value("redis_password").toString();
    cfg.redisPoolSize = js.value("redis_pool_size").toInt(4);

    // 初始化 Redis
    if (!RedisStore::instance().init(cfg)) {
        qCritical() << "Failed to init Redis";
        return 1;
    }

    // 启动 TCP 服务
    TcpServer server;
    if (!server.start(cfg.port)) {
        qCritical() << "Failed to start server on port" << cfg.port;
        return 1;
    }
    qInfo() << "Server started on port" << cfg.port;

    return app.exec();
}
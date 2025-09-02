#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "src/authmanager.h"
#include "src/asruploader.h"
#include "chat/QMLChatClient.h"
// #include "src/databasemanager.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    // DatabaseManager dbManager("smart_hos_mgmt.db");
    AuthManager authManager;
    // 确保端口与 Flask server 一致（server.py 默认 8080）
    authManager.setApiBase("http://127.0.0.1:8080");
    // authManager.setDatabase(&dbManager);

    AsrUploader asrUploader;
    asrUploader.setApiBase("http://127.0.0.1:8080");

    QMLChatClient chatClient;

    QQmlApplicationEngine engine;
    qmlRegisterType<AuthManager>("com.mycompany.app", 1, 0, "AuthManager");

    engine.rootContext()->setContextProperty("authManager", &authManager);
    engine.rootContext()->setContextProperty("asrUploader", &asrUploader);

    engine.load(QUrl(QStringLiteral("qrc:/client/qml/qml/Main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}

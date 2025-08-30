#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "src/authmanager.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    // 创建 AuthManager 后端实例
    AuthManager authManager;
    authManager.setApiBase("http://127.0.0.1:8080"); // 修改为你的服务器地址

    QQmlApplicationEngine engine;
    qmlRegisterType<AuthManager>("com.mycompany.app", 1, 0, "AuthManager");

    // 将已有实例暴露给 QML
    engine.rootContext()->setContextProperty("authManager", &authManager);

    // 加载 QML
    engine.load(QUrl(QStringLiteral("qrc:/client/qml/qml/Main.qml"))); // 修改为资源路径

    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}

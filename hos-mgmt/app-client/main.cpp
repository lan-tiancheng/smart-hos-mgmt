#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "src/authmanager.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    // 注册 QML 类型（供 QML 创建 AuthManager 对象或访问枚举）
    qmlRegisterType<AuthManager>("com.mycompany.app", 1, 0, "AuthManager");
    qmlRegisterUncreatableType<AuthManager>("com.mycompany.app", 1, 0, "AuthManagerEnums", "Enums only");

    QQmlApplicationEngine engine;

    // 创建 AuthManager 实例，并暴露给 QML
    AuthManager authManager;
    engine.rootContext()->setContextProperty("authManager", &authManager);

    // 加载主 QML
    const QUrl url(QStringLiteral("qrc:/client/qml/qml/Main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
                         if (!obj && url == objUrl)
                             QCoreApplication::exit(-1);
                     }, Qt::QueuedConnection);

    engine.load(url);

    return app.exec();
}

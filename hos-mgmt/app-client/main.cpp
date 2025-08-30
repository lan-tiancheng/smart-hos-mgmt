#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "src/authmanager.h"
#include "src/asruploader.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    AuthManager authManager;
    authManager.setApiBase("http://127.0.0.1:8080");

    AsrUploader asrUploader;
    asrUploader.setApiBase("http://127.0.0.1:8080");

    QQmlApplicationEngine engine;
    qmlRegisterType<AuthManager>("com.mycompany.app", 1, 0, "AuthManager");

    engine.rootContext()->setContextProperty("authManager", &authManager);
    engine.rootContext()->setContextProperty("asrUploader", &asrUploader);

    engine.load(QUrl(QStringLiteral("qrc:/client/qml/qml/Main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}

#include "src/authmanager.h"
#include <QDebug>
#include <QHostAddress>

AuthManager::AuthManager(QObject *parent)
    : QObject(parent)
{
    connect(&m_socket, &QTcpSocket::readyRead, this, &AuthManager::onReadyRead);
    connect(&m_socket, &QTcpSocket::connected, this, &AuthManager::onConnected);
    connect(&m_socket, &QTcpSocket::errorOccurred, this, &AuthManager::onErrorOccurred);

    // 测试用，可以连接到本地服务端
    m_socket.connectToHost(QHostAddress("127.0.0.1"), 8080);// 端口需要修改 网络编程
}

// 登录请求
void AuthManager::requestLogin(UserType userType, const QString &username, const QString &password)
{
    QJsonObject request;
    request["type"] = "login";
    request["userType"] = (userType == Patient) ? "patient" : "doctor";
    request["username"] = username;
    request["password"] = password;

    QJsonDocument doc(request);
    m_socket.write(doc.toJson());
    m_socket.flush(); // 确保发送
}

// 注册请求
void AuthManager::requestRegister(UserType userType, const QString &username, const QString &password,
                                  const QString &phone, const QString &address, int age, const QString &gender)
{
    QJsonObject request;
    request["type"] = "register";
    request["userType"] = (userType == Patient) ? "patient" : "doctor";
    request["username"] = username;
    request["password"] = password;
    request["phone"] = phone;
    request["address"] = address;
    request["age"] = age;
    request["gender"] = gender;

    QJsonDocument doc(request);
    m_socket.write(doc.toJson());
    m_socket.flush();
}

// Socket 已连接
void AuthManager::onConnected()
{
    qDebug() << "Connected to server.";
}

// Socket 错误处理
void AuthManager::onErrorOccurred(QTcpSocket::SocketError socketError)
{
    Q_UNUSED(socketError);
    qDebug() << "Socket error:" << m_socket.errorString();
    emit loginFailed("无法连接到服务器");
}

// 接收服务器响应
void AuthManager::onReadyRead()
{
    QByteArray data = m_socket.readAll();
    handleResponse(data);
}

// 处理服务端返回
void AuthManager::handleResponse(const QByteArray &data)
{
    QJsonDocument doc = QJsonDocument::fromJson(data);
    if (doc.isNull() || !doc.isObject()) {
        emit loginFailed("服务器响应格式错误");
        return;
    }

    QJsonObject resp = doc.object();
    QString type = resp["type"].toString();
    bool success = resp["success"].toBool();
    QString reason = resp["reason"].toString();

    if (type == "login") {
        if (success) {
            m_isAuthenticated = true;
            emit isAuthenticatedChanged();
            bool isPatient = (resp["userType"].toString() == "patient");
            emit loginSuccess(isPatient ? Patient : Doctor);
        } else {
            setRemainingAttempts(resp["remainingAttempts"].toInt());
            emit loginFailed(reason);
        }
    } else if (type == "register") {
        if (success) {
            emit registerSuccess();
        } else {
            emit registerFailed(reason);
        }
    }
}

void AuthManager::setRemainingAttempts(int attempts)
{
    if (m_remainingAttempts != attempts) {
        m_remainingAttempts = attempts;
        emit remainingAttemptsChanged();
    }
}

// 将军 \O/\O/\O/\O/\O/

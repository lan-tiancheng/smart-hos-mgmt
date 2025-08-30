#ifndef AUTHMANAGER_H
#define AUTHMANAGER_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QTcpSocket>
#include <QJsonObject>

class AuthManager : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool isAuthenticated READ isAuthenticated NOTIFY isAuthenticatedChanged)
    Q_PROPERTY(int remainingAttempts READ remainingAttempts NOTIFY remainingAttemptsChanged)
    Q_PROPERTY(int currentUserId READ currentUserId NOTIFY currentUserIdChanged)

public:
    explicit AuthManager(QObject *parent = nullptr);

    enum UserType { Patient = 0, Doctor = 1 };
    Q_ENUM(UserType)

    Q_INVOKABLE void setApiBase(const QString &url);

    // 暴露给 QML 的 HTTP 版本
    Q_INVOKABLE void requestLogin(const QString &username, const QString &password);
    Q_INVOKABLE void requestRegister(const QString &userType, const QString &username, const QString &password,
                                     const QString &phone, const QString &address, int age, const QString &gender);
    Q_INVOKABLE void submitHealthData(double heightCm, double weightKg, int lungMl, const QString &bp);
    Q_INVOKABLE void setRemainingAttempts(int attempts);

    // getters
    bool isAuthenticated() const;
    int remainingAttempts() const;
    int currentUserId() const;

signals:
    void loginSuccess(int userId, AuthManager::UserType userType);
    void loginFailed(const QString &reason);

    void registerSuccess();
    void registerFailed(const QString &reason);

    void healthSubmitSuccess(double bmi, const QString &lungLevel, const QString &bpLevel, const QString &overall);
    void healthSubmitFailed(const QString &reason);

    void isAuthenticatedChanged();
    void remainingAttemptsChanged();
    void currentUserIdChanged();

private slots:
    // TCP
    void onConnected();
    void onErrorOccurred(QAbstractSocket::SocketError socketError);
    void onReadyRead();

    // HTTP
    void onHttpLoginFinished(QNetworkReply* reply);
    void onHttpRegisterFinished(QNetworkReply* reply);
    void onHttpHealthSubmitFinished(QNetworkReply* reply);

private:
    // TCP 版本保留为内部使用，避免与 QML 冲突
    void requestLogin(UserType userType, const QString &username, const QString &password);
    void requestRegister(UserType userType, const QString &username, const QString &password,
                         const QString &phone, const QString &address, int age, const QString &gender);

    // 公共工具（增加 timeoutMs，默认 15000ms）
    void sendTcpJson(const QJsonObject &obj);
    void postHttpJson(const QString &path,
                      const QJsonObject &obj,
                      std::function<void(QNetworkReply*)> callback,
                      int timeoutMs = 15000);
    void handleHttpReply(QNetworkReply* reply,
                         std::function<void(const QJsonObject&)> onSuccess,
                         std::function<void(const QString&)> onError);

    // 响应处理
    void processLoginResponse(const QJsonObject &resp);
    void processRegisterResponse(const QJsonObject &resp);
    void processHealthSubmitResponse(const QJsonObject &resp);

private:
    QNetworkAccessManager m_nam;
    QTcpSocket m_socket;
    QByteArray m_pendingBuffer;

    QString m_apiBase;
    bool m_isAuthenticated = false;
    int m_remainingAttempts = 5;
    int m_userId = -1;
};

#endif // AUTHMANAGER_H

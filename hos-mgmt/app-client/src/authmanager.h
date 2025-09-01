#ifndef AUTHMANAGER_H
#define AUTHMANAGER_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QTcpSocket>
#include <QJsonObject>
#include <QJSValue>
#include <QSqlDatabase>
#include "databasemanager.h"

class AuthManager : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool isAuthenticated READ isAuthenticated NOTIFY isAuthenticatedChanged)
    Q_PROPERTY(int remainingAttempts READ remainingAttempts NOTIFY remainingAttemptsChanged)
    Q_PROPERTY(int currentUserId READ currentUserId NOTIFY currentUserIdChanged)
    Q_PROPERTY(UserType currentUserType READ currentUserType NOTIFY currentUserTypeChanged)

public:
    explicit AuthManager(QObject *parent = nullptr);

    enum UserType { Patient = 0, Doctor = 1 };
    Q_ENUM(UserType)

    Q_INVOKABLE void setApiBase(const QString &url);

    // 暴露给 QML 的 HTTP 版本
    Q_INVOKABLE void requestLogin(const QString &profession,
                                  const QString &username,
                                  const QString &password);
    Q_INVOKABLE void requestRegister(const QString &profession,
                                     const QString &username,
                                     const QString &password,
                                     const QString &phone,
                                     const QString &address,
                                     int age,
                                     const QString &gender);

    Q_INVOKABLE void submitHealthData(double heightCm, double weightKg, int lungMl, const QString &bp);
    Q_INVOKABLE void setRemainingAttempts(int attempts);

    // 个人信息获取与修改
    Q_INVOKABLE void getPatientInfo(QJSValue callback); // 不要加 const
    Q_INVOKABLE void updatePatientInfo(const QString &username,
                                       const QString &phone,
                                       const QString &address,
                                       const QString &age,
                                       const QString &gender,
                                       QJSValue callback); // 不要加 const

    // getters
    bool isAuthenticated() const;
    int remainingAttempts() const;
    int currentUserId() const;
    UserType currentUserType() const { return m_userType; }

    void setDatabase(DatabaseManager* db) { dbManager = db; }

    static QSqlDatabase getProfessionDatabase(const QString& profession);

signals:
    void loginSuccess(int userId, AuthManager::UserType userType);
    void loginFailed(const QString &reason);

    void registerSuccess();
    void registerFailed(const QString &reason);

    void healthSubmitSuccess(double bmi, const QString &lungLevel, const QString &bpLevel, const QString &overall);
    void healthSubmitFailed(const QString &reason);

    // 个人信息修改结果信号
    void updatePatientInfoSuccess();
    void updatePatientInfoFailed(const QString &reason);

    void isAuthenticatedChanged();
    void remainingAttemptsChanged();
    void currentUserIdChanged();
    void currentUserTypeChanged();

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

    // 公共工具
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
    DatabaseManager* dbManager = nullptr;
    QNetworkAccessManager m_nam;
    QTcpSocket m_socket;
    QByteArray m_pendingBuffer;

    QString m_apiBase;
    bool m_isAuthenticated = false;
    int m_remainingAttempts = 5;
    int m_userId = -1;
    UserType m_userType = Patient;
};

#endif // AUTHMANAGER_H

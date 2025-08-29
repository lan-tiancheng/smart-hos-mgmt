#ifndef AUTHMANAGER_H
#define AUTHMANAGER_H

#include <QObject>
#include <QTcpSocket>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QJsonObject>
#include <QDateTime>

class AuthManager : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool isAuthenticated READ isAuthenticated NOTIFY isAuthenticatedChanged)
    Q_PROPERTY(int remainingAttempts READ remainingAttempts NOTIFY remainingAttemptsChanged)
    Q_PROPERTY(int currentUserId READ currentUserId NOTIFY currentUserIdChanged)


public:
    explicit AuthManager(QObject *parent = nullptr);

    enum UserType {
        Patient,
        Doctor
    };
    Q_ENUM(UserType)

    // 登录和注册方法
    Q_INVOKABLE void requestLogin(UserType userType, const QString &username, const QString &password);
    Q_INVOKABLE void requestLogin(const QString &username, const QString &password);
    Q_INVOKABLE void requestRegister(UserType userType, const QString &username, const QString &password,
                                     const QString &phone, const QString &address, int age, const QString &gender);
    Q_INVOKABLE void requestRegister(const QString &userType, const QString &username, const QString &password,
                                     const QString &phone, const QString &address, int age, const QString &gender);

    // 健康数据提交
    Q_INVOKABLE void submitHealthData(double heightCm, double weightKg, int lungMl, const QString &bp);

    // 消息通信功能
    Q_INVOKABLE void sendMessage(int toUserId, const QString &message);
    Q_INVOKABLE void requestConversations();
    Q_INVOKABLE void requestMessages(int otherUserId);

    // 视频通话功能
    Q_INVOKABLE void startVideoCall(int otherUserId);
    Q_INVOKABLE void acceptVideoCall(int callId);
    Q_INVOKABLE void rejectVideoCall(int callId);
    Q_INVOKABLE void endVideoCall(int callId);

    // 剩余尝试次数设置
    Q_INVOKABLE void setRemainingAttempts(int attempts);

    // 属性 getter
    bool isAuthenticated() const { return m_isAuthenticated; }
    int remainingAttempts() const { return m_remainingAttempts; }
    int currentUserId() const { return m_userId; }

    //登出
    Q_INVOKABLE void logout();

signals:
    // 登录信号
    void loginSuccess(int userId, const QString &userType);
    void loginSuccess(UserType userType);
    void loginFailed(const QString &reason);

    // 注册信号
    void registerSuccess();
    void registerFailed(const QString &reason);

    // 健康数据提交信号
    void healthSubmitSuccess(double bmi, const QString &lungLevel, const QString &bpLevel, const QString &overall);
    void healthSubmitFailed(const QString &reason);

    // 消息通信信号
    void messageReceived(int fromUserId, const QString &fromUsername, const QString &message);
    void messageSentSuccess(int messageId);
    void messageSentFailed(const QString &reason);
    void conversationListReceived(const QJsonArray &conversations);
    void messagesReceived(int conversationId, const QJsonArray &messages);

    // 视频通话信号
    void videoCallRequested(int callId, int fromUserId, const QString &fromUsername);
    void videoCallAccepted(int callId);
    void videoCallRejected(int callId);
    void videoCallStarted(int callId);
    void videoCallEnded(int callId);
    void videoCallError(const QString &reason);

    // 属性变化信号
    void isAuthenticatedChanged();
    void remainingAttemptsChanged();
    void currentUserIdChanged();

    void logoutSuccess();

private slots:
    void onReadyRead();
    void onConnected();
    void onErrorOccurred(QAbstractSocket::SocketError socketError);

private:
    void processResponseObject(const QJsonObject &resp);
    void processMessage(const QJsonObject &messageObj);
    void processVideoCallRequest(const QJsonObject &callObj);

    QTcpSocket m_socket;
    QNetworkAccessManager m_nam;
    QString m_apiBase;

    bool m_isAuthenticated;
    int m_userId;
    int m_remainingAttempts;
};

#endif // AUTHMANAGER_H

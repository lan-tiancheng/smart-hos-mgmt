#ifndef AUTHMANAGER_H
#define AUTHMANAGER_H

#include <QObject>
#include <QTcpSocket>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QJsonObject>

/**
 * AuthManager
 *
 * 说明：
 * - 同时支持两种通信方式：
 *   1) 旧的 TCP JSON（QTcpSocket）风格（requestLogin(UserType, ...) / requestRegister(UserType,...))
 *   2) 推荐的 HTTP REST（QNetworkAccessManager）风格（requestLogin(QString,...) / requestRegister(QString,...))
 * - 响应统一由 processResponseObject() 处理，最终通过信号通知 QML。
 */

class AuthManager : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool isAuthenticated READ isAuthenticated NOTIFY isAuthenticatedChanged)
    Q_PROPERTY(int remainingAttempts READ remainingAttempts NOTIFY remainingAttemptsChanged)
    Q_PROPERTY(int currentUserId READ currentUserId NOTIFY isAuthenticatedChanged)

public:
    explicit AuthManager(QObject *parent = nullptr);

    // 枚举：用于 QML 调用时的类型（可在 QML 用 AuthManager.Patient / AuthManager.Doctor）
    enum UserType {
        Patient,
        Doctor
    };
    Q_ENUM(UserType)

    // ----- TCP-style (legacy) - 使用 enum UserType 参数 -----
    Q_INVOKABLE void requestLogin(UserType userType, const QString &username, const QString &password);
    Q_INVOKABLE void requestRegister(UserType userType, const QString &username, const QString &password,
                                     const QString &phone, const QString &address, int age, const QString &gender);

    // ----- HTTP-style (preferred) - 使用字符串类型 -----
    Q_INVOKABLE void requestLogin(const QString &username, const QString &password);
    Q_INVOKABLE void requestRegister(const QString &userType, const QString &username, const QString &password,
                                     const QString &phone, const QString &address, int age, const QString &gender);

    // 健康数据提交（HTTP）
    Q_INVOKABLE void submitHealthData(double heightCm, double weightKg, int lungMl, const QString &bp);

    // 剩余尝试次数（可由 QML 调用重置）
    Q_INVOKABLE void setRemainingAttempts(int attempts);

    // 属性 getter
    bool isAuthenticated() const { return m_isAuthenticated; }
    int remainingAttempts() const { return m_remainingAttempts; }
    int currentUserId() const { return m_userId; }

signals:
    // 登录信号（两种形式，便于兼容 QML 老代码与新代码）
    void loginSuccess(int userId, const QString &userType); // HTTP 风格（返回 userId）
    void loginSuccess(UserType userType);                    // 旧风格（仅返回 enum）

    void loginFailed(const QString &reason);

    // 注册信号
    void registerSuccess();
    void registerFailed(const QString &reason);

    // 健康数据提交信号
    void healthSubmitSuccess(double bmi, const QString &lungLevel, const QString &bpLevel, const QString &overall);
    void healthSubmitFailed(const QString &reason);

    // 属性变化信号
    void isAuthenticatedChanged();
    void remainingAttemptsChanged();

private slots:
    // TCP socket 事件处理
    void onReadyRead();
    void onConnected();
    void onErrorOccurred(QAbstractSocket::SocketError socketError);

private:
    // 统一处理来自 TCP/HTTP 的响应 JSON 对象
    void processResponseObject(const QJsonObject &resp);

    // 成员
    QTcpSocket m_socket;
    QNetworkAccessManager m_nam;
    QString m_apiBase = QStringLiteral("http://127.0.0.1:8080"); // 可在构造或暴露 setter 修改

    bool m_isAuthenticated = false;
    int m_userId = 0;
    int m_remainingAttempts = 5;
};

#endif // AUTHMANAGER_H

#ifndef AUTHMANAGER_H
#define AUTHMANAGER_H

#include <QObject>
#include <QTcpSocket>
#include <QJsonObject>
#include <QJsonDocument>

class AuthManager : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool isAuthenticated READ isAuthenticated NOTIFY isAuthenticatedChanged)
    Q_PROPERTY(int remainingAttempts READ remainingAttempts NOTIFY remainingAttemptsChanged)

public:
    enum UserType {
        Patient,
        Doctor
    };
    Q_ENUM(UserType)

    explicit AuthManager(QObject *parent = nullptr);

    Q_INVOKABLE void requestLogin(UserType userType, const QString &username, const QString &password);
    Q_INVOKABLE void requestRegister(UserType userType, const QString &username, const QString &password,
                                     const QString &phone, const QString &address, int age, const QString &gender);
    Q_INVOKABLE void setRemainingAttempts(int attempts);

    bool isAuthenticated() const { return m_isAuthenticated; }
    int remainingAttempts() const { return m_remainingAttempts; }

signals:
    void loginSuccess(UserType userType);
    void loginFailed(const QString &reason);
    void registerSuccess();
    void registerFailed(const QString &reason);
    void isAuthenticatedChanged();
    void remainingAttemptsChanged();

private slots:
    void onReadyRead();
    void onConnected();
    void onErrorOccurred(QTcpSocket::SocketError socketError);

private:
    QTcpSocket m_socket;
    bool m_isAuthenticated = false;
    int m_remainingAttempts = 5;

    void handleResponse(const QByteArray &data);
};

#endif // AUTHMANAGER_H

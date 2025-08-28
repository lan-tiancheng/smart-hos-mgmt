#pragma once
#include <QObject>
#include <QTcpSocket>
#include <QJsonObject>
#include <functional>

class ClientSocket : public QObject {
    Q_OBJECT
public:
    explicit ClientSocket(QObject* parent = nullptr);
    void connectToServer(const QString& host, quint16 port);
    void send(const QJsonObject& obj);
    void setOnMessage(std::function<void(const QJsonObject&)> cb) { onMessage_ = std::move(cb); }

private slots:
    void onReadyRead();

private:
    QTcpSocket sock_;
    QByteArray buf_;
    std::function<void(const QJsonObject&)> onMessage_;
};

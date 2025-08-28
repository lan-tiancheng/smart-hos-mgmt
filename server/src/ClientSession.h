#pragma once
#include <QObject>
#include <QTcpSocket>
#include <QByteArray>
#include <QJsonObject>
#include "Router.h"

class ClientSession : public QObject {
    Q_OBJECT
public:
    explicit ClientSession(QObject* parent = nullptr);
    bool start(qintptr socketDescriptor);

private slots:
    void onReadyRead();
    void onDisconnected();

private:
    void processLine(const QByteArray& line);
    QTcpSocket* socket_ = nullptr;
    QByteArray buffer_;
    Router router_;
};

#include "LoginWindow.h"
#include "../net/ClientSocket.h"
#include "common/Protocol.h"
#include "PatientHomeWindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>

LoginWindow::LoginWindow(QWidget* parent) : QWidget(parent) {
    setWindowTitle("患者端 - 登录");
    email_ = new QLineEdit(this);
    email_->setPlaceholderText("邮箱");
    password_ = new QLineEdit(this);
    password_->setPlaceholderText("密码");
    password_->setEchoMode(QLineEdit::Password);

    btnLogin_ = new QPushButton("登录", this);
    btnRegister_ = new QPushButton("注册", this);
    status_ = new QLabel(this);

    auto* v = new QVBoxLayout(this);
    v->addWidget(email_);
    v->addWidget(password_);
    auto* h = new QHBoxLayout();
    h->addWidget(btnLogin_);
    h->addWidget(btnRegister_);
    v->addLayout(h);
    v->addWidget(status_);

    socket_ = std::make_unique<ClientSocket>(this);
    socket_->connectToServer("127.0.0.1", 5555);
    socket_->setOnMessage([this](const QJsonObject& o){ handleResponse(o); });

    connect(btnLogin_, &QPushButton::clicked, this, &LoginWindow::onLogin);
    connect(btnRegister_, &QPushButton::clicked, this, &LoginWindow::onRegister);
}

void LoginWindow::onLogin() {
    QJsonObject data;
    data["email"] = email_->text();
    data["password"] = password_->text();
    QJsonObject req; req["action"] = "auth.login"; req["data"] = data;
    socket_->send(req);
}

void LoginWindow::onRegister() {
    QJsonObject data;
    data["email"] = email_->text();
    data["password"] = password_->text();
    data["role"] = "patient";
    data["name"] = "";
    QJsonObject req; req["action"] = "auth.register"; req["data"] = data;
    socket_->send(req);
}

void LoginWindow::handleResponse(const QJsonObject& obj) {
    bool ok = obj.value("ok").toBool();
    QString action = obj.value("action").toString();
    if (!ok) {
        status_->setText(QString("失败(%1): %2")
                         .arg(obj.value("error_code").toInt())
                         .arg(obj.value("error_message").toString()));
        return;
    }
    if (action == "auth.register") {
        status_->setText("注册成功，请登录。");
    } else if (action == "auth.login") {
        status_->setText("登录成功。");
        auto* home = new PatientHomeWindow();
        home->show();
        this->close();
    }
}
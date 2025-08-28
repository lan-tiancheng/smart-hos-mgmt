#pragma once
#include <QWidget>
#include <memory>

class QLineEdit;
class QPushButton;
class QLabel;
class ClientSocket;

class LoginWindow : public QWidget {
    Q_OBJECT
public:
    explicit LoginWindow(QWidget* parent = nullptr);

private slots:
    void onLogin();
    void onRegister();

private:
    void handleResponse(const QJsonObject& obj);
    std::unique_ptr<ClientSocket> socket_;
    QLineEdit* email_;
    QLineEdit* password_;
    QPushButton* btnLogin_;
    QPushButton* btnRegister_;
    QLabel* status_;
};

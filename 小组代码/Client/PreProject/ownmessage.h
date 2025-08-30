#ifndef OWNMESSAGE_H
#define OWNMESSAGE_H

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QCloseEvent>
#include <QLabel>
#include <QVBoxLayout>
#include <QFormLayout>

class OwnMessage : public QWidget {
    Q_OBJECT

public:
    OwnMessage(QWidget *parent = nullptr);
    void setOriginData(QString name,QString birth,QString id,QString phone,QString email);

signals:
    void back();

private slots:
    void confirm();
    void goBack();
    void modify();
    void setDisplayMode(bool display);

private:
    QVBoxLayout *mainLayout;
    QFormLayout *formLayout;
    QLabel *nameLabel;
    QLabel *dobLabel;
    QLabel *idLabel;
    QLabel *phoneLabel;
    QLabel *emailLabel;
    QLineEdit *nameEdit;
    QLineEdit *dobEdit;
    QLineEdit *idEdit;
    QLineEdit *phoneEdit;
    QLineEdit *emailEdit;
    QWidget *nameContainer;
    QWidget *dobContainer;
    QWidget *idContainer;
    QWidget *phoneContainer;
    QWidget *emailContainer;
    QPushButton *confirmButton;
    QPushButton *backButton;
    QPushButton *modifyButton;
};

#endif // OWNMESSAGE_H

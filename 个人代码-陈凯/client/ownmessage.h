#ifndef OWNMESSAGE_H
#define OWNMESSAGE_H

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QFormLayout>
#include <QLabel>

class OwnMessage : public QWidget {
    Q_OBJECT

public:
    explicit OwnMessage(QWidget *parent = nullptr);

private slots:
    void confirm();
    void goBack();
    void edit();

private:
    void setEditMode(bool edit);

    QLineEdit *nameEdit;
    QLineEdit *dobEdit;
    QLineEdit *idEdit;
    QLineEdit *phoneEdit;
    QLineEdit *emailEdit;

    QLabel *nameLabel;
    QLabel *dobLabel;
    QLabel *idLabel;
    QLabel *phoneLabel;
    QLabel *emailLabel;

    QPushButton *confirmButton;
    QPushButton *backButton;
    QPushButton *editButton;

    QFormLayout *formLayout;

    bool isEditing;  // 用于标记是否处于编辑模式
};

#endif // OWNMESSAGE_H

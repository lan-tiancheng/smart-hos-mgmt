#include "ownmessage.h"
#include <QVBoxLayout>
#include <QMessageBox>

OwnMessage::OwnMessage(QWidget *parent) : QWidget(parent), isEditing(false) {
    resize(400, 300);

    QVBoxLayout *mainLayout = new QVBoxLayout;

    // 创建表单布局
    formLayout = new QFormLayout;

    nameLabel = new QLabel("姓名:");
    dobLabel = new QLabel("出生年月日:");
    idLabel = new QLabel("身份证号:");
    phoneLabel = new QLabel("手机号:");
    emailLabel = new QLabel("邮箱:");

    nameEdit = new QLineEdit;
    dobEdit = new QLineEdit;
    idEdit = new QLineEdit;
    phoneEdit = new QLineEdit;
    emailEdit = new QLineEdit;

    // 初始状态：显示标签
    formLayout->addRow(nameLabel, new QLabel(nameEdit->text()));
    formLayout->addRow(dobLabel, new QLabel(dobEdit->text()));
    formLayout->addRow(idLabel, new QLabel(idEdit->text()));
    formLayout->addRow(phoneLabel, new QLabel(phoneEdit->text()));
    formLayout->addRow(emailLabel, new QLabel(emailEdit->text()));

    mainLayout->addLayout(formLayout);

    // 创建按钮
    confirmButton = new QPushButton("确认");
    backButton = new QPushButton("返回");
    editButton = new QPushButton("修改");

    connect(confirmButton, &QPushButton::clicked, this, &OwnMessage::confirm);
    connect(backButton, &QPushButton::clicked, this, &OwnMessage::goBack);
    connect(editButton, &QPushButton::clicked, this, &OwnMessage::edit);

    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(confirmButton);
    buttonLayout->addWidget(backButton);
    buttonLayout->addWidget(editButton);

    mainLayout->addLayout(buttonLayout);

    setLayout(mainLayout);

    // 设置初始状态
    setEditMode(false);
}

void OwnMessage::confirm() {
    if (isEditing) {
        // 保存文本框的内容到标签
        nameLabel->setText(nameEdit->text());
        dobLabel->setText(dobEdit->text());
        idLabel->setText(idEdit->text());
        phoneLabel->setText(phoneEdit->text());
        emailLabel->setText(emailEdit->text());

        // 隐藏文本框
        nameEdit->hide();
        dobEdit->hide();
        idEdit->hide();
        phoneEdit->hide();
        emailEdit->hide();

        // 显示标签
        formLayout->removeWidget(nameEdit);
        formLayout->removeWidget(dobEdit);
        formLayout->removeWidget(idEdit);
        formLayout->removeWidget(phoneEdit);
        formLayout->removeWidget(emailEdit);

        formLayout->addRow(nameLabel, nameLabel);
        formLayout->addRow(dobLabel, dobLabel);
        formLayout->addRow(idLabel, idLabel);
        formLayout->addRow(phoneLabel, phoneLabel);
        formLayout->addRow(emailLabel, emailLabel);

        // 切换状态
        isEditing = false;
    } else {
        // 切换到编辑模式
        nameEdit->setText(nameLabel->text());
        dobEdit->setText(dobLabel->text());
        idEdit->setText(idLabel->text());
        phoneEdit->setText(phoneLabel->text());
        emailEdit->setText(emailLabel->text());

        // 隐藏标签
        nameLabel->hide();
        dobLabel->hide();
        idLabel->hide();
        phoneLabel->hide();
        emailLabel->hide();

        // 添加文本框到布局中
        formLayout->addRow(nameLabel, nameEdit);
        formLayout->addRow(dobLabel, dobEdit);
        formLayout->addRow(idLabel, idEdit);
        formLayout->addRow(phoneLabel, phoneEdit);
        formLayout->addRow(emailLabel, emailEdit);

        // 显示文本框
        nameEdit->show();
        dobEdit->show();
        idEdit->show();
        phoneEdit->show();
        emailEdit->show();

        // 切换状态
        isEditing = true;
    }
}

void OwnMessage::goBack() {
    close();  // 关闭当前窗口
}

void OwnMessage::edit() {
    setEditMode(!isEditing);  // 切换编辑模式
}

void OwnMessage::setEditMode(bool edit) {
    isEditing = edit;

    if (edit) {
        // 切换到编辑模式
        nameLabel->hide();
        dobLabel->hide();
        idLabel->hide();
        phoneLabel->hide();
        emailLabel->hide();

        // 添加文本框到布局中
        formLayout->addRow(nameLabel, nameEdit);
        formLayout->addRow(dobLabel, dobEdit);
        formLayout->addRow(idLabel, idEdit);
        formLayout->addRow(phoneLabel, phoneEdit);
        formLayout->addRow(emailLabel, emailEdit);

        // 显示文本框
        nameEdit->show();
        dobEdit->show();
        idEdit->show();
        phoneEdit->show();
        emailEdit->show();
    } else {
        // 切换到显示模式
        nameLabel->setText(nameEdit->text());
        dobLabel->setText(dobEdit->text());
        idLabel->setText(idEdit->text());
        phoneLabel->setText(phoneEdit->text());
        emailLabel->setText(emailEdit->text());

        // 隐藏文本框
        nameEdit->hide();
        dobEdit->hide();
        idEdit->hide();
        phoneEdit->hide();
        emailEdit->hide();

        // 显示标签
        formLayout->addRow(nameLabel, nameLabel);
        formLayout->addRow(dobLabel, dobLabel);
        formLayout->addRow(idLabel, idLabel);
        formLayout->addRow(phoneLabel, phoneLabel);
        formLayout->addRow(emailLabel, emailLabel);
    }
}

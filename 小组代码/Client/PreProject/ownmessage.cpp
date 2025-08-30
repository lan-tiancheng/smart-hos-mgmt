#include "ownmessage.h"
#include "tcpmgr.h"
#include "usermgr.h"
#include <QVBoxLayout>
#include <QFormLayout>
#include <QMessageBox>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QWidget>
#include <qjsondocument.h>

OwnMessage::OwnMessage(QWidget *parent) : QWidget(parent) {
    // 设置窗口的初始大小
    resize(400, 300);

    // 创建主布局，使用垂直布局管理器
    mainLayout = new QVBoxLayout;

    // 创建表单布局，用于按行排列标签和输入框
    formLayout = new QFormLayout;

    // 初始化标签（用于显示信息）
    nameLabel = new QLabel;
    dobLabel = new QLabel;
    idLabel = new QLabel;
    phoneLabel = new QLabel;
    emailLabel = new QLabel;

    //——————————————————————————————————————注意！——————————————————————————————————
    //请在此处添加端口setOriginData(QString name,QString birth,QString id,QString phone,QString email)

    UserInfoNew userInfo = UserMgr::GetInstance()->getUserInfo();

        // 提取需要的数据
        QString name = userInfo.name;
        QString birth = userInfo.year + "-" + userInfo.month + "-" + userInfo.data;  // 假设 birth 需要完整的出生日期
        QString id = userInfo.IDcard;
        QString phone = userInfo.phone;
        QString email = userInfo.email;

        // 调用 setOriginData 函数传递数据
        setOriginData(name, birth, id, phone, email);

    // 初始化文本框（用于用户输入）
    nameEdit = new QLineEdit;
    dobEdit = new QLineEdit;
    idEdit = new QLineEdit;
    phoneEdit = new QLineEdit;
    emailEdit = new QLineEdit;

    // 创建容器，用于将标签和输入框组合在一起
    nameContainer = new QWidget;
    dobContainer = new QWidget;
    idContainer = new QWidget;
    phoneContainer = new QWidget;
    emailContainer = new QWidget;

    // 创建水平布局，用于在容器内排列标签和输入框
    QHBoxLayout *nameLayout = new QHBoxLayout;
    QHBoxLayout *dobLayout = new QHBoxLayout;
    QHBoxLayout *idLayout = new QHBoxLayout;
    QHBoxLayout *phoneLayout = new QHBoxLayout;
    QHBoxLayout *emailLayout = new QHBoxLayout;

    // 将标签和输入框添加到各自的水平布局中
    nameLayout->addWidget(nameEdit);  // 文本框在前
    nameLayout->addWidget(nameLabel); // 标签在后
    nameContainer->setLayout(nameLayout);

    dobLayout->addWidget(dobEdit);  // 文本框在前
    dobLayout->addWidget(dobLabel); // 标签在后
    dobContainer->setLayout(dobLayout);

    idLayout->addWidget(idEdit);  // 文本框在前
    idLayout->addWidget(idLabel); // 标签在后
    idContainer->setLayout(idLayout);

    phoneLayout->addWidget(phoneEdit);  // 文本框在前
    phoneLayout->addWidget(phoneLabel); // 标签在后
    phoneContainer->setLayout(phoneLayout);

    emailLayout->addWidget(emailEdit);  // 文本框在前
    emailLayout->addWidget(emailLabel); // 标签在后
    emailContainer->setLayout(emailLayout);

    // 将每个容器添加到表单布局中
    formLayout->addRow("姓名:", nameContainer);
    formLayout->addRow("出生年月日:", dobContainer);
    formLayout->addRow("身份证号:", idContainer);
    formLayout->addRow("手机号:", phoneContainer);
    formLayout->addRow("邮箱:", emailContainer);

    // 将表单布局添加到主布局中
    mainLayout->addLayout(formLayout);

    // 初始化按钮并连接到相应的槽函数
    confirmButton = new QPushButton("确认");
    backButton = new QPushButton("返回");
    modifyButton = new QPushButton("修改");

    connect(confirmButton, &QPushButton::clicked, this, &OwnMessage::confirm);
    connect(backButton, &QPushButton::clicked, this, &OwnMessage::goBack);
    connect(modifyButton, &QPushButton::clicked, this, &OwnMessage::modify);

    // 创建水平布局用于排列按钮
    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(confirmButton);
    buttonLayout->addWidget(backButton);
    buttonLayout->addWidget(modifyButton);

    // 将按钮布局添加到主布局中
    mainLayout->addLayout(buttonLayout);

    // 设置主布局
    setLayout(mainLayout);

    // 初始设置为显示模式（显示 QLabel，隐藏 QLineEdit）
    setDisplayMode(true);
}

void OwnMessage::setDisplayMode(bool display) {
    if (display) {
        UserInfoNew userInfo = UserMgr::GetInstance()->getUserInfo();

            // 提取需要的数据
            QString name = userInfo.name;
            QString birth = userInfo.year + "-" + userInfo.month + "-" + userInfo.data;  // 假设 birth 需要完整的出生日期
            QString id = userInfo.IDcard;
            QString phone = userInfo.phone;
            QString email = userInfo.email;

            // 调用 setOriginData 函数传递数据
            setOriginData(name, birth, id, phone, email);
        // 设置为显示模式，显示 QLabel，隐藏 QLineEdit
        nameLabel->show();
        dobLabel->show();
        idLabel->show();
        phoneLabel->show();
        emailLabel->show();

        nameEdit->hide();
        dobEdit->hide();
        idEdit->hide();
        phoneEdit->hide();
        emailEdit->hide();
    } else {
        // 设置为编辑模式，显示 QLineEdit，隐藏 QLabel
        nameEdit->show();
        dobEdit->show();
        idEdit->show();
        phoneEdit->show();
        emailEdit->show();

        nameLabel->hide();
        dobLabel->hide();
        idLabel->hide();
        phoneLabel->hide();
        emailLabel->hide();
    }
}

void OwnMessage::confirm() {
    // 从 QLineEdit 中获取文本并更新到 QLabel
    nameLabel->setText(nameEdit->text());//姓名
    dobLabel->setText(dobEdit->text());//出生年月
    idLabel->setText(idEdit->text());//身份证件号码
    phoneLabel->setText(phoneEdit->text());//电话
    emailLabel->setText(emailEdit->text());//邮箱

    QString name = nameLabel->text();
    QString dob = dobLabel->text();
    QString id = idLabel->text();
    QString phone = phoneLabel->text();
    QString email = emailLabel->text();
    int uid = UserMgr::GetInstance()->getUid();  // 从 UserMgr 获取 uid

    // 构建 JSON 对象
    QJsonObject jsonObj;
    jsonObj["uid"] = uid;
    jsonObj["name"] = name;
    jsonObj["IDcard"] = id;  // 将 idLabel 的值作为 IDcard 传递
    jsonObj["phone"] = phone;
    jsonObj["email"] = email;

    // 将 JSON 对象转换为字符串
    QJsonDocument doc(jsonObj);
    QString jsonString = doc.toJson(QJsonDocument::Indented);

    // 发送 TCP 请求给服务器
    emit TcpMgr::GetInstance()->sig_send_data(ReqId::ID_UPDATE_USER_INFO, jsonString);
    UserMgr::GetInstance()->setUid(uid);
    UserMgr::GetInstance()->setName(name);
    UserMgr::GetInstance()->setIDcard(id);
    UserMgr::GetInstance()->setPhone(phone);
    UserMgr::GetInstance()->setEmail(email);



    // 切换回显示模式
    setDisplayMode(true);

    // 弹出确认对话框
    QMessageBox::information(this, "确认", "信息已提交！");
}

void OwnMessage::goBack() {
    // 发出返回信号
    emit back();
}

void OwnMessage::modify() {
    // 切换到编辑模式
    setDisplayMode(false);
}
void OwnMessage::setOriginData(QString name,QString birth,QString id,QString phone,QString email){
    nameLabel->setText(name);
    dobLabel->setText(birth);
    idLabel->setText(id);
    phoneLabel->setText(phone);
    emailLabel->setText(email);

}


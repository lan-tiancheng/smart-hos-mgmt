#include "ownwindow.h"
#include "ownillness.h"
#include "owndeal.h"
#include "ownmessage.h"
#include <QLabel>
#include <QVBoxLayout>
#include <QPushButton>
#include <QHBoxLayout>

OwnWindow::OwnWindow() {
    resize(600, 400);

    QVBoxLayout *mainLayout = new QVBoxLayout;

    QLabel *titleLabel = new QLabel("个人");
    titleLabel->setStyleSheet("font-size: 40px; font-weight: bold;");
    mainLayout->addWidget(titleLabel);
    mainLayout->addStretch();  // 将顶部标签推至顶部

    QHBoxLayout *buttonLayout = new QHBoxLayout;
    for (int i = 0; i < 3; ++i) {
        QPushButton *button = new QPushButton;
        button->setIcon(QIcon(QString(":/images/button%1_icon.png").arg(i + 1)));
        button->setIconSize(QSize(64, 64));

        QLabel *label = new QLabel(QString("按钮%1描述").arg(i + 1));
        label->setAlignment(Qt::AlignCenter);

        QVBoxLayout *buttonAndLabelLayout = new QVBoxLayout;
        buttonAndLabelLayout->addWidget(button);
        buttonAndLabelLayout->addWidget(label);
        buttonAndLabelLayout->setAlignment(Qt::AlignCenter);

        buttonLayout->addLayout(buttonAndLabelLayout);
        buttonLayout->addSpacing(20);

        if (i == 0) {  // 按钮 1 的索引为 0
            connect(button, &QPushButton::clicked, this, &OwnWindow::showOwnIllness);
        } else if (i == 1) {  // 按钮 2 的索引为 1
            connect(button, &QPushButton::clicked, this, &OwnWindow::showOwnDeal);
        } else if (i == 2) {  // 按钮 3 的索引为 2
            connect(button, &QPushButton::clicked, this, &OwnWindow::showOwnMessage);
        }
    }

    mainLayout->addLayout(buttonLayout);
    setLayout(mainLayout);

    // 初始化 OwnIllness 和 OwnDeal 窗口
    illnessWindow = nullptr;
    dealWindow = nullptr;
    messageWindow = nullptr;
}

void OwnWindow::showOwnIllness() {
    if (!illnessWindow) {
        illnessWindow = new OwnIllness(this);
    }
    illnessWindow->show();
}

void OwnWindow::showOwnDeal() {
    if (!dealWindow) {
        dealWindow = new OwnDeal(this);
    }
    dealWindow->show();
}

void OwnWindow::showOwnMessage() {
    if (!messageWindow) {
        messageWindow = new OwnMessage(this);
    }
    messageWindow->show();
}

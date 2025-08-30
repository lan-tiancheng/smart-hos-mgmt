#include "quizwd.h"
#include "ui_quizwd.h"
#include <QLabel>
#include <QVBoxLayout>
#include <QString>
#include <QUrl>
#include <QDebug>
#include <QDesktopServices>
#include <QPainter>
#include <QPixmap>

quizWd::quizWd(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::quizWd)
{
    ui->setupUi(this);
    this->resize(500,500);
    this->setWindowTitle("问卷自测");

    // 创建并设置第一个 QLabel，调整字号和边框
      QLabel *linkLabel1 = new QLabel(this);
      linkLabel1->setOpenExternalLinks(true); // 允许点击链接在浏览器中打开
      linkLabel1->setText("<a style='color: red; text-decoration: none; font-size: 24px; border: 2px solid red; padding: 5px;' href='https://apesk.com/xinliceshi/?type=lately'>APESK经典心理测试题集</a>");
      linkLabel1->setAlignment(Qt::AlignHCenter); // 文本居中

      // 创建并设置第二个 QLabel，调整字号和边框
      QLabel *linkLabel2 = new QLabel(this);
      linkLabel2->setText("<a style='color: blue; text-decoration: none; font-size: 24px; border: 2px solid blue; padding: 5px;' href='https://testharo.com/cn'>Testharo心理测试</a>");
      linkLabel2->setAlignment(Qt::AlignHCenter); // 文本居中

      // 创建并设置第三个 QLabel，调整字号和边框
      QLabel *linkLabel3 = new QLabel(this);
      linkLabel3->setOpenExternalLinks(true); // 允许点击链接在浏览器中打开
      linkLabel3->setText("<a style='color: white; text-decoration: none; font-size: 24px; border: 2px solid white; padding: 5px;' href='https://a.051h.top/XlExam/detail_b/id/146.html'>抑郁与焦虑自评量表（SDS）专业版</a>");
      linkLabel3->setAlignment(Qt::AlignHCenter); // 文本居中

      // 创建并设置第四个 QLabel，调整字号和边框
      QLabel *linkLabel4 = new QLabel(this);
      linkLabel4->setOpenExternalLinks(true); // 允许点击链接在浏览器中打开
      linkLabel4->setText("<a style='color: yellow; text-decoration: none; font-size: 24px; border: 2px solid yellow; padding: 5px;' href='https://www.16personalities.com/ch'>MBTI16人格测试</a>");
      linkLabel4->setAlignment(Qt::AlignHCenter); // 文本居中

      // 连接信号槽，点击链接时打开浏览器
      connect(linkLabel2, &QLabel::linkActivated, [](const QString &url) {
          QDesktopServices::openUrl(QUrl(url));
      });

      // 使用垂直布局排列标签
      QVBoxLayout *layout = new QVBoxLayout(this);
      layout->addWidget(linkLabel1);
      layout->addWidget(linkLabel2);
      layout->addWidget(linkLabel3);
      layout->addWidget(linkLabel4);
      layout->setContentsMargins(20, 30, 20, 30); // 设置布局边距
      layout->setSpacing(10); // 设置组件间距

      setLayout(layout); // 设置布局

}
// 重写 paintEvent 方法来绘制背景图
void quizWd::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QPixmap backgroundPixmap(":/res/psychologyquiz.jpg"); // 使用资源文件中的背景图片
    painter.drawPixmap(0, 0, width(), height(), backgroundPixmap);
    QWidget::paintEvent(event); // 调用基类的 paintEvent 以确保正常绘制其他内容
}

quizWd::~quizWd()
{
    delete ui;
}

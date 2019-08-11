#include "mywidget.h"
#include "ui_mywidget.h"
#include <QDebug>
#include <QKeyEvent>
#include <QCloseEvent>
#include <QMessageBox>
#include <QEvent>

MyWidget::MyWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MyWidget)
{
    ui->setupUi(this);
    // 启动定时器
    timerId = this -> startTimer(1000);    // 以毫秒为单位
    timerId2 = this -> startTimer(500);

    connect(ui->pushButton, &MyButton::clicked,
            [=]()
            {
                qDebug() << "按钮被摁下！";
            });

    // 安装过滤器
    ui -> label_2 -> installEventFilter(this);
}

MyWidget::~MyWidget()
{
    delete ui;
}

void MyWidget::keyPressEvent(QKeyEvent *e)
{
    qDebug() << e -> key();

    if (e -> key() == Qt::Key_0)
    {
        qDebug() << "Qt::Key_0";
    }
}

void MyWidget::timerEvent(QTimerEvent *e)
{
    if(e -> timerId() == this -> timerId)
    {
        static int sec = 0;
        ui -> label -> setText(QString("<center><h1>Timer Out (%1)</h1></center>").arg(sec++));

        if(10 == sec)
        {
             killTimer(this -> timerId);
        }
    }
    else if(e -> timerId() == this -> timerId2)
    {
        static int sec = 0;
        ui -> label_2 -> setText(QString("<center><h1>Timer Out (%1)</h1></center>").arg(sec++));

        if(10 == sec)
        {
             killTimer(this -> timerId2);
        }
    }
}

// 主窗口事件，ignore()后调用
void MyWidget::mousePressEvent(QMouseEvent *e)
{
    qDebug() << "+++";
}

void MyWidget::closeEvent(QCloseEvent *e)
{
    int ret = QMessageBox::question(this,"qustion","您是否需要关闭？");
    if (ret == QMessageBox::Yes)
    {
        // 关闭窗口
        // 处理关闭窗口事件，接收事件，事件就不会往下传递
        e -> accept();
    }
    else
    {
        // 不关闭窗口
        // 忽略事件，事件就继续给父组件
        e -> ignore();
    }
}

/* bool MyWidget::event(QEvent *e)
{
    // 事件分发
    switch ( e -> type())
    {
        case QEvent::Close:
            closeEvent(e);
        break;
        case QEvent::MouseMove:
            mouseMoveEvent(e);
        break;

        ......
    }

    if (e -> type() == QEvent::Timer)
    {
        // 去掉定时器
        // 如果返回true，事件停止传播
        // QTimerEvent *e
        QtimerEvent *env = static_case<QtimerEvent *>(e);
        timeEvent(env);
        return true;
    }
    else if(e -> type() == QEvent::KeyPress)
    {
        QKeyEvent *env = static_cast<QKeyEvent *>(e);
        if (env -> key() == Qt::Key_B)
        {
            return QWidget::event(e);
        }
        else
        {
            return true;
        }
    }
    else
    {
        return QWidget::event(e);
    }
}*/

// 过滤事件
bool MyWidget::eventFilter(QObject *obj, QEvent *e)
{
    if (obj == ui -> label_2)
    {
        QMouseEvent *env = static_cast<QMouseEvent *>(e);
        // 判断事件
        if (e -> type() == QEvent::MouseMove)
        {
            ui -> label_2 -> setText(QString("MouseMove:(%1,%2)").arg(env -> x()).arg(env -> y()));
            return true;
        }
        else {
            return QWidget::eventFilter(obj,e);
        }
    }
    else
    {
        return QWidget::eventFilter(obj,e);
    }
}


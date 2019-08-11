#include "mywidget.h"
#include "ui_mywidget.h"
#include <QDebug>

MyWidget::MyWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MyWidget)
{
    ui->setupUi(this);

    // 动态分配空间，不能指定父对象
    myT = new MyThread;
    // 创建子进程
    thread = new QThread(this);
    // 把自定义的线程加入到子线程中
    myT -> moveToThread(thread);    // 进程关联

    // 处理线程信号
    connect(myT, &MyThread::mySignal, this, &MyWidget::dealSignal);

    qDebug() << "主线程号:" << QThread::currentThread();

    connect(this, &MyWidget::startThread, myT, &MyThread::myTimeout);
    connect(this, &MyWidget::destroyed, this, &MyWidget::dealClose);

    // 线程函数内部不允许操作图形界面
    // 对话框也不行

    // connect 第五个参数的作用
    // 只有在多线程时才有意义
    // 第五个参数为连接方式：默认、队列、直接使用

    // 如果是多线程，默认使用队列
    // 如果是单线程，默认为直接使用方式
    // 队列：槽函数所在的线程和接收者一致
    // 直接：槽函数所在线程和发送者一样
}

MyWidget::~MyWidget()
{
    delete ui;
}

void MyWidget::on_buttonStart_clicked()
{
    if (thread -> isRunning() == true)
    {
        return;
    }
    // 启动线程，但是没有启动线程处理函数
    thread -> start();
    myT -> setFlog(false);
    // 不能直接调用线程处理函数
    // 直接调用导致线程处理函数和主线程在同一个线程
    // myT -> myTimeout();

    // 只能通过 signal-slot 信号和槽方式调用
    emit startThread();
}

void MyWidget::dealSignal()
{
    static int i = 0;
    i ++;
    ui -> lcdNumber -> display(i);
}

void MyWidget::on_buttonStop_clicked()
{
    if (thread -> isRunning() == false)
    {
        return;
    }
    myT -> setFlog(true);
    thread -> quit();
    thread -> wait();
}

void MyWidget::dealClose()
{
    myT -> setFlog(true);
    delete myT;
}

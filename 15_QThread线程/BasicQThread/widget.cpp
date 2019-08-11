#include "widget.h"
#include "ui_widget.h"
#include <QThread>
#include <QDebug>
#define cout qDebug() << "[" << __FILE__ << ":" << __LINE__ << "]"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    myTimer = new QTimer(this);

    // 只要定时器启动，自动触发timeout信号
    connect(myTimer, &QTimer::timeout, this, &Widget::dealTimeout);

    // 分配空间
    thread = new MyThread(this);
    // 获取线程处理完成后信号
    connect(thread, &MyThread::isDone, this, &Widget::dealDone);
    // 在窗口处理结束（右上角X）后关闭线程
    connect(this, &Widget::destroy, this, &Widget::stopThread);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::dealTimeout()
{
    static int i = 0;
    // 设置Lcd的值
    ui -> lcdNumber -> display(i);
    i++;
}

void Widget::on_pushButton_clicked()
{
    if (myTimer -> isActive() == false)
    {
        myTimer -> start(100);
    }
    // 复杂数据处理，耗时较长
    // QThread::sleep(5);
    // 处理完成以后，关闭定时器
    //myTimer -> stop();
    //cout << "over!";

    // 启动线程，处理数据
    thread -> start();
}

void Widget::dealDone()
{
    cout << "It's over!";
    myTimer -> stop();    // 关闭定时器
}

void Widget::stopThread()
{
    // 两个关闭函数
    // 暴力，一般不要用此函数，有动态分配经常导致内存问题
    //thread -> terminate();

    // 等待线程处理完工作再关闭
    thread -> quit();    // 不一定马上关闭，也许会阻塞
    // 等待运行完成后结束
    thread -> wait();
}

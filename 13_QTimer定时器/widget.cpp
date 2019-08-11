#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    setWindowTitle("定时器");

    myTimer = new QTimer(this);
    connect(myTimer,&QTimer::timeout,
            [=]()
                {
                    static int i = 0;
                    ui -> lcdNumber -> display(i);
                    i ++;
                });
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_ButtonStart_clicked()
{
    // 启动定时器，时间间隔为100毫秒，每个100ms myTimer 自动触发timeout()
    // 如果定时器没有激活，才启动
    if (myTimer -> isActive() == false)
    {
        myTimer -> start(100);
    }
}

void Widget::on_ButtonStop_clicked()
{
    // 停止定时器
    if (myTimer -> isActive() == true)
    {
        myTimer -> stop();
    }
}

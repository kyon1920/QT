#include "widget.h"
#include "ui_widget.h"
#include <QPainter>
#include <QFlags>
#include <QMouseEvent>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    // 去窗口边框
    setWindowFlags(Qt::FramelessWindowHint | windowFlags());
    // 把窗口背景设置为透明
    setAttribute(Qt::WA_TranslucentBackground);
    // 变成对话框
    // setWindowFlag(Qt::Dialog);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    p.drawPixmap(0,0,width(),height(),QPixmap("../timg (17).jpg"));
}
void Widget::mouseMoveEvent(QMouseEvent *e)
{
    if (e -> button() == Qt::RightButton)
    {
        close();
    }
    else if (e -> button() == Qt::LeftButton)
    {
        // 求坐标差值
        // 当前点击坐标 - 窗口左上角坐标
        p = e -> globalPos() - this -> frameGeometry().topLeft();
    }
}
void Widget::mousePressEvent(QMouseEvent *e)
{
    if (e -> buttons() & Qt::LeftButton)
    {
        move(e->globalPos() - p);
    }
}

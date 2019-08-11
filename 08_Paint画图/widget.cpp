#include "widget.h"
#include "ui_widget.h"
#include <QPainter>    // 画家
#include <QPen>    //画笔
#include <QBrush>    // 画刷

// QBitmap -> QPixmap 继承关系

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    x = 0;
}

Widget::~Widget()
{
    delete ui;
}

void Widget::paintEvent(QPaintEvent *)
{
    // QPainter p(this);

    // 或者

    QPainter p;    // 创建画家对象
    p.begin(this);    // 指定当前窗口为绘图设备

    // 开始绘图
    // p.drawxxx();
    // 画背景图
    //p.drawPixmap(0,0,width(),height(),QPixmap("../timg (7).jpg"));
    // 获取窗口的整个矩形区域
    p.drawPixmap(rect(),QPixmap("../timg (7).jpg"));

    // 定义画笔
    QPen pen;
    pen.setWidth(5);    // 设置线宽
    pen.setColor(Qt::red);    // 设置颜色
    // pen.setColor(QColor(255,0,0));    // 利用RGB设置颜色
    pen.setStyle(Qt::DashLine);    // 设置风格
    // 把画笔交给画家
    p.setPen(pen);

    // 定义画刷
    QBrush brush;
    brush.setColor(Qt::red);
    brush.setStyle(Qt::Dense1Pattern);
    // 把画刷交给画家
    p.setBrush(brush);

    // 画线
    p.drawLine(50,50,500,50);
    p.drawLine(50,50,50,500);
    // 画矩形
    p.drawRect(10,10,100,100);
    // 画圆
    p.drawEllipse(QPoint(100,100),100,50);

    // 画个图像
    p.drawPixmap(x, 180, 80, 80,QPixmap("../timg (4).jpg"));


    p.end();

}

void Widget::on_pushButton_clicked()
{
    x += 20;
    if (x > width())
    {
        x = 0;
    }
    // 刷新窗口，让窗口重绘
    // update()不能放在上面的paintEvent()方法中，会进入死循环，使程序变得很卡
    update();    // 间接调用画图
}

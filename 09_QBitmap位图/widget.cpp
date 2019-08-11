#include "widget.h"
#include "ui_widget.h"
#include <QPainter>
#include <QBitmap>
#include <QBrush>
#include <QImage>
#include <QPicture>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    // 绘图设备400x300
    QPixmap pixmap(400,300);
    QPainter p(&pixmap);

    // 填充背景色
    p.fillRect(0,0,400,300,QBrush(Qt::white));
    //或者
    pixmap.fill(Qt::white);
    // 向设备进行绘图
    p.drawPixmap(0,0,300,250,QPixmap("../timg (7).jpg"));
    // 保存图片
    pixmap.save("../pixmap.jpg");

    // 创建一个绘图设备
    QImage image(400,300,QImage::Format_ARGB32);    // 背景透明
    QPainter q;
    q.begin(&image);
    // 绘图
    q.drawImage(0,0,QImage("../timg (7).jpg"));
    // 进行像素点操作，一个优点，但不常用
    for (int i = 0; i < 50; ++i)
    {
        for (int j = 0; j < 50; ++j)
        {
            // image.pixel(QPoint(i, j));    // 获取像素点
            image.setPixel(QPoint(i, j), qRgb(255,0,0));
        }
    }
    q.end();
    image.save("../image.png");

    // 创建一个绘图设备
    QPicture picture;
    QPainter qp;
    qp.begin(&picture);
    // 绘图
    qp.drawPixmap(0,0,300,250,QPixmap("../timg (7).jpg"));
    qp.drawLine(0,0,300,250);
    qp.end();
    // 保存的是二进制文件，在文件夹中打不开
    picture.save("../picture.jpg");
}

Widget::~Widget()
{
    delete ui;
}

void Widget::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    //p.drawPixmap(0,0,width(),height(),QPixmap("../timg (7).jpg"));

    // QBitmap 图片背景透明
    p.drawPixmap(0,0,width(),height(),QBitmap("../timg (15).jpg"));

    // 也可以通过下面方式加载图片
    //QPixmap pixmap;
    //pixmap.load("../timg (7).jpg");
    //p.drawPixmap(0,0,width(),height(),pixmap);

    //QBitmap bitmap;
    //bitmap.load("../timg (15).jpg");
    //p.drawPixmap(0,0,width(),height(),bixmap);

#if 0
    QPicture pic;
    pic.load("../picture.jpg");
    QPainter pa;
    pa.drawPicture(0,0,pic);
#endif

    // 各种绘图设备之间的转换
    QPixmap pixmap;
    pixmap.load("../pixmap.jpg");
    // QPixmap -> QImage
    QImage image = pixmap.toImage();
    p.drawImage(0,0,image);
    // QImage -> QPixmap
    QPixmap tempPixmap = QPixmap::fromImage(image);
    p.drawPixmap(100,0,tempPixmap);

}

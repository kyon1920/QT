#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

namespace Ui {
class Widget;
}

/*
 * 绘图设备
 * QPixmap：针对屏幕进行优化，和平台相关，不能对图片进行像素点进行修改
 * QImage：传输时用，和平台无关，可以对图片进行修改，可以在线程中绘图
 * QPicture：保存绘图得状态(二进制文件)
*/

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();

protected:
    // 重写绘图事件
    // 如果给窗口绘图，一定要在paintEvent实现
    void paintEvent(QPaintEvent *);

private:
    Ui::Widget *ui;
};

#endif // WIDGET_H

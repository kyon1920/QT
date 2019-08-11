#include "widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    /*
     * 对于父窗口(主窗口)，坐标系统相对于屏幕
     * 原点：相对于屏幕左上角
     * x：往右递增
     * y：往下递增
     */
    move(100,100);

    this -> setWindowTitle("CoordinateSystem");
    this -> setMinimumSize(500,500);
    this -> setMaximumSize(500,500);
    /*
     * 子窗口对于父窗口(主窗口)，坐标系统相对于父窗口
     * 原点：相对于父窗口左上角
     * x：往右递增
     * y：往下递增
     */
    b1 = new QPushButton;
    b1 -> move(100,100);
    b1 -> setText("^_^");
    b1 -> setParent(this);
    b1 -> setFixedSize(100,25);    // resize();也可以设置大小
    /*
     * 垃圾回收机制
     * 只要控件继承于QObject就会存在垃圾回收机制
     * 在最后会自动回收释放
     */
    /*
     * 垃圾回收机制条件：1)指定父对象后  2)间接或直接继承于QObject
     * 子对象如果是动态分配空间的，不需要手动释放
     * 系统会自动释放
     */
    // 验证自动回收机制，关闭程序时会打印 按钮被析构！
    b2 = new MyButton;
    b2 -> setParent(this);
    b2 -> resize(100,25);
    b2 -> move(50,50);
    b2 -> setText("回收机制触发");

}

Widget::~Widget()
{
}

#include "mywidget.h"
#include <QApplication>    //QApplication应用程序类
//Qt头文件没有.h
//头文件和类名一样都是前两个字母大写
#include <QPushButton>    //QPushButton按钮类

int main(int argc, char *argv[])
{
    // 有且只有一个QApplication应用程序类对象
    QApplication a(argc, argv);

    //MyWidget继承于QWidget，QWidget是一个窗口基类
    MyWidget w;
    w.setWindowTitle("主要看气质");    //设置窗口标题
    w.setMinimumSize(500,500);

    QPushButton b;
    /*如果按钮对象不指定父对象，对象和对象就没有任何关系，
     * 独立存在
     * a指定b为它的父对象 = a放在b的上面
     * 指定父对象，有两种方法：
     *      1)直接调用setParent()方法
     *      2)通过构造函数传参
     * 指定父对象，只需要父对象显示，子对象就将自动显示
     */
    b.setParent(&w);    //调用函数指定父对象
    b.setText("^_^");
    b.move(100,100);    //设定b所在位置

    QPushButton c(&w);    //通过构造传参指定父对象
    c.setText("~_~");

    w.show();

    return a.exec();
}

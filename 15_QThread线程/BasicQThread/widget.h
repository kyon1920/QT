#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTimer>
#include "mythread.h"    // 线程头文件

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();

    // 定时器槽函数
    void dealTimeout();    // 处理定时器信号
    void dealDone();    // 处理MyThread函数
    void stopThread();    // 关闭线程

private slots:
    void on_pushButton_clicked();

private:
    Ui::Widget *ui;

    QTimer *myTimer;
    MyThread *thread;    // 线程对象
};

#endif // WIDGET_H

#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QWidget>
#include <QThread>
#include "mythread.h"

namespace Ui {
class MyWidget;
}

class MyWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MyWidget(QWidget *parent = nullptr);
    ~MyWidget();

    void dealSignal();
    void dealClose();
private slots:
    void on_buttonStart_clicked();

    void on_buttonStop_clicked();

private:
    Ui::MyWidget *ui;

    MyThread *myT;
    // 子进程
    QThread *thread;

signals:
    void startThread();    // 启动子线程的信号
};

#endif // MYWIDGET_H

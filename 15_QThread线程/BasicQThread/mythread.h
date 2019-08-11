#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QThread>
#include <QWidget>

class MyThread : public QThread
{
    Q_OBJECT
public:
    explicit MyThread(QObject *parent = nullptr);

protected:
    // 重写QThread虚函数
    // 线程处理函数
    // 不能直接调用，通过start()调用
    void run();

signals:
    void isDone();

public slots:
};

#endif // MYTHREAD_H

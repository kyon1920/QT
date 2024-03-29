#include "mythread.h"
#include <QThread>
#include <QDebug>

MyThread::MyThread(QObject *parent) : QObject(parent)
{

    isStop = false;
}

void MyThread::myTimeout()
{
    while( isStop == false)
    {
        QThread::sleep(1);
        emit mySignal();
        qDebug() << "子线程号:" << QThread::currentThread();

        if (true == isStop)
        {
            break;
        }
    }
}

void MyThread::setFlog(bool flag)
{
    isStop = flag;
}

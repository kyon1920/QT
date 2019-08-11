#include "mythread.h"
#include <QDebug>

#define cout qDebug() << "[" << __FILE__ << ":" << __LINE__ << "]"

MyThread::MyThread(QObject *parent) : QThread(parent)
{

}

void MyThread::run()
{
    // 复杂数据处理，耗时较长
    sleep(5);
    cout << "over!";

    emit isDone();
}

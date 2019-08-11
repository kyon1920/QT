#include "mybutton.h"
#include <QMouseEvent>
#include <QDebug>

MyButton::MyButton(QWidget *parent) : QPushButton(parent)
{

}

// 重写要重视
void MyButton::mousePressEvent(QMouseEvent *e)
{
    if (e -> button() == Qt::LeftButton)
    {
        // 如果是左键按下打印
        // 事件接收后，就会往下传送
        qDebug() << "按下的是左键";
        QPushButton::mousePressEvent(e);
        // 上面事件的忽略，事件继续往下传递

        // accept()接收事件、ignore()事件忽略
        //e -> ignore();    忽略，事件继续往下传递。传递给谁？
        // 事件传递给了父组件，而不是（父类）基类
    }
    else
    {
        // 不做处理
        QPushButton::mousePressEvent(e);
    }
}

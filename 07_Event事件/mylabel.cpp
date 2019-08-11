#include "mylabel.h"
#include <QMouseEvent>
#include <QDebug>

MyLabel::MyLabel(QWidget *parent) : QLabel(parent)
{
    this -> setMouseTracking(true);
}


void MyLabel::mousePressEvent(QMouseEvent *ev)
{
    int i = ev -> x();
    int j = ev -> y();

    /*
     * 格式化
     * QString str = QString("abc %1 ^_^ %2").arg(123).arg("mike");
     * str = abc 123 ^_^ mike
     */

    if(ev -> button() == Qt::LeftButton)
    {
        qDebug() << "Left!";
    }
    else if(ev -> button() == Qt::RightButton)
    {
        qDebug() << "Right!";
    }
    else if(ev -> button() == Qt::MidButton)
    {
        qDebug() << "Mid!";
    }

    QString text = QString("<center><h1>Mouse Press: (%1, %2)</h1></center>").arg(i).arg(j);
    this -> setText(text);
}
void MyLabel::mouseReleaseEvent(QMouseEvent *ev)
{
    int i = ev -> x();
    int j = ev -> y();

    QString text = QString("<center><h1>Mouse Release: (%1, %2)</h1></center>").arg(i).arg(j);
    this -> setText(text);
}
void MyLabel::mouseMoveEvent(QMouseEvent *ev)
{
    int i = ev -> x();
    int j = ev -> y();

    QString text = QString("<center><h1>Mouse move: (%1, %2)</h1></center>").arg(i).arg(j);
    this -> setText(text);
}

void MyLabel::enterEvent(QEvent *)
{
    QString text = QString("<center><h1>Mouse Enter!</h1></center>");
    this -> setText(text);
}
void MyLabel::leaveEvent(QEvent *)
{
    QString text = QString("<center><h1>Mouse Leave!</h1></center>");
    this -> setText(text);
}

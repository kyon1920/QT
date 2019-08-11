#include "mybutton.h"
#include <QDebug>

MyButton::MyButton(QPushButton *parent) : QPushButton(parent)
{

}

MyButton::~MyButton()
{
    qDebug() << "按钮被析构！";
}

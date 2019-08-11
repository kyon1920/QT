#include "widget.h"
#include "ui_widget.h"


Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    domxml.createXMLfile("../demo.xml");
    QStringList list;
    list << "zhang" << "男" << "20" << "HelloWorld!";
    domxml.appendXML("../demo.xml", list);

    QStringList NList;
    QStringList SList;
    QStringList AList;
    QStringList JList;
    DomXML::readXML("../demo.xml", NList, SList, AList, JList);
    for (int i = 0; i < NList.size(); ++i)
    {
        QString str = QString("%1:%2:%3:%4").arg(NList.at(i)).arg(SList.at(i)).arg(AList.at(i)).arg(JList.at(i));
        qDebug() << str;
    }
}

Widget::~Widget()
{
    delete ui;
}

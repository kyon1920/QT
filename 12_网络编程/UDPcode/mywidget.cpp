#include "mywidget.h"
#include "ui_mywidget.h"
#include <QHostAddress>

MyWidget::MyWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MyWidget)
{
    ui->setupUi(this);
    setWindowTitle("端口:8888");
    move(500,300);

    udpSocket = new QUdpSocket(this);
    udpSocket->bind(8888);
    connect(udpSocket, &QUdpSocket::readyRead,
            [=]()
                {
                    char buf[1024] = {0};
                    QHostAddress addr;    // 对方地址
                    quint16 port;    // 对方端口
                    qint64 len = udpSocket -> readDatagram(buf, sizeof(buf), &addr, &port);
                    if (len > 0)
                    {
                        // 格式化
                        QString str = QString("[%1:%2] %3").arg(addr.toString()).arg(port).arg(buf);
                        //编辑器设置内容
                        ui -> read -> append(str);
                    }
                });
}

MyWidget::~MyWidget()
{
    delete ui;
}

void MyWidget::on_ButtonSend_clicked()
{
    // 发送数据
    // 先获取对方的IP和端口
    QString ip = ui -> IP -> text();
    qint16 port = ui -> port -> text().toInt();
    // 获取编辑区的内容
    QString str = ui -> write -> toPlainText();
    // 向指定的IP发送数据
    udpSocket -> writeDatagram(str.toUtf8(), QHostAddress(ip), port);
    ui -> read -> append("我:"+str);
    ui -> write -> clear();
}

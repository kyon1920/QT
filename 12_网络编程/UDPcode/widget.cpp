#include "widget.h"
#include "ui_widget.h"
#include <QHostAddress>


Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    setWindowTitle("端口:9000");
    move(1000,300);

    // 分配空间，指定父对象
    udpSocket = new QUdpSocket(this);
    // 绑定端口和地址
    udpSocket-> bind(9000);

    // 加入某个组播
    // 组播地址是D类地址
    // udpSocket-> bind(QHostAdress::AnyIPv4, 9000);
    // udpSocket -> joinMulticastGroup(QHostAddress("224.0.0.2"));
    // 离开，退出组播
    // udpSocket -> leaveMulticastGroup(QHostAddress("224.0.0.2"));

    // 当对方成功发送数据过来
    // 自动触发readyRead()
    connect(udpSocket, &QUdpSocket::readyRead, this, &Widget::dealMsg);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::dealMsg()
{
    // 读取对方发送的内容
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
}

void Widget::on_ButtonSend_clicked()
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

#include "clientwidget.h"
#include "ui_clientwidget.h"
#include <QHostAddress>

ClientWidget::ClientWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ClientWidget)
{
    ui->setupUi(this);

    this -> setWindowTitle("客户端");
    this -> move(1000,300);

    tcpSocket = nullptr;

    //分配空间，指定父对象
    tcpSocket = new QTcpSocket(this);

    connect(tcpSocket, &QTcpSocket::connected,
            [=]()
                {
                    ui -> read -> setText("成功和服务器建立连接");
                });
    connect(tcpSocket, &QTcpSocket::readyRead,
            [=]()
                {
                    // 获取对方发送的内容
                    QByteArray array = tcpSocket -> readAll();
                    // 追加到编辑区
                    ui -> read -> append("服务器:" + array);
                });
}

ClientWidget::~ClientWidget()
{
    delete ui;
}

void ClientWidget::on_ButtonSend_clicked()
{
    // 获取编辑框内容
    QString str = ui -> write -> toPlainText();
    // 发送数据
    tcpSocket -> write(str.toUtf8().data());
    ui -> read -> append("客户端:" + str);
    ui -> write -> clear();
}

void ClientWidget::on_ButtonConnect_clicked()
{
    // 获取服务器IP和端口
    QString ip = ui -> lineEditIP -> text();
    qint16 port = ui -> lineEditPort -> text().toInt();

    // 主动和服务器建立连接
    tcpSocket -> connectToHost(QHostAddress(ip),port);
}

void ClientWidget::on_ButtonClose_clicked()
{
    // 主动和对方断开链接
    tcpSocket -> disconnectFromHost();
    tcpSocket -> close();
}

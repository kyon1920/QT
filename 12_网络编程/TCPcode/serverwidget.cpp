#include "serverwidget.h"
#include "ui_serverwidget.h"

ServerWidget::ServerWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ServerWidget)
{
    ui->setupUi(this);
    tcpServer = nullptr;
    tcpSocket = nullptr;


    this -> setWindowTitle("服务器(端口:8888)");
    this -> resize(450,350);
    this -> move(500,300);
    // 指定父对象，让它自动回收空间
    tcpServer = new QTcpServer(this);    // 监听套接字
    // 监听 设定地址和端口
    tcpServer -> listen(QHostAddress::Any, 8888);
    connect(tcpServer, &QTcpServer::newConnection,
            [=]()
            {
                // 取出建立好链接的套接字
                tcpSocket = tcpServer -> nextPendingConnection();
                // 获取客户端的IP和端口
                QString ip = tcpSocket -> peerAddress().toString();
                qint16 port = tcpSocket -> peerPort();
                QString temp = QString("[%1:%2]:成功连接").arg(ip).arg(port);
                ui -> read -> setText(temp);

                connect(tcpSocket, &QTcpSocket::readyRead,
                        [=]()
                            {
                                // 从通信套接字中取出内容
                                QByteArray array = tcpSocket -> readAll();
                                ui -> read -> append("客户端:" + array);
                            });
            });
}

ServerWidget::~ServerWidget()
{
    delete ui;
}

void ServerWidget::on_ButtonSend_clicked()
{
    if (nullptr == tcpSocket)
    {
        return;
    }
    // 获取编辑区内容
    QString str = ui -> write -> toPlainText();
    // 给对方发送数据
    tcpSocket -> write(str.toUtf8().data());
    ui -> read -> append("服务器:" + str);
    ui -> write -> clear();
}

void ServerWidget::on_ButtonClose_clicked()
{
    if (nullptr == tcpSocket)
    {
        return;
    }
    // 主动和客户端断开连接
    tcpSocket -> disconnectFromHost();
    tcpSocket -> close();
    tcpSocket = nullptr;
}

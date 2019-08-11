#include "serverwidget.h"
#include "ui_serverwidget.h"
#include <QHostAddress>
#include <QFileDialog>
#include <QDebug>
#include <QFileInfo>

ServerWidget::ServerWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ServerWidget)
{
    ui->setupUi(this);
    move(550,300);

    tcpServer = new QTcpServer(this);
    // 绑定监听
    tcpServer -> listen(QHostAddress::Any, 8888);
    setWindowTitle("服务器:端口8888");

    // 一开始未连接，两个按钮都不能按下
    ui -> buttonFile -> setEnabled(false);
    ui -> buttonSend -> setEnabled(false);

    // 如果客户端和服务器连接成功
    // tcpServer会自动触发newConnection()
    connect(tcpServer, &QTcpServer::newConnection,
            [=]()
                {
                    // 取出建立好链接的套接字
                    tcpSocket = tcpServer -> nextPendingConnection();
                    QString ip = tcpSocket -> peerAddress().toString();
                    quint16 port = tcpSocket -> peerPort();
                    QString str = QString("[%1:%2] 成功连接").arg(ip).arg(port);
                    ui -> textEdit -> append(str);

                    // 成功连接后才能按选择文件
                    ui -> buttonFile -> setEnabled(true);

                    connect(tcpSocket, &QTcpSocket::readyRead,
                            [=]()
                                {
                                    // 取客户端的信息
                                    QByteArray buf = tcpSocket -> readAll();
                                    if (QString(buf) == "file done!")
                                    {
                                        // 文件接收完毕
                                        ui -> textEdit -> append("文件发送完毕!");
                                        file.close();

                                        // 断开客户端端口
                                        tcpSocket -> disconnectFromHost();
                                        tcpSocket -> close();
                                    }
                                    else
                                    {
                                        ui -> textEdit -> append("正在发送...已完成" + buf);
                                    }
                                });
                });
    connect(&timer, &QTimer::timeout,
            [=]()
                {
                    // 关闭定时器
                    timer.stop();
                    // 发送文件
                    sendData();
                });

}

ServerWidget::~ServerWidget()
{
    delete ui;
}

void ServerWidget::on_buttonFile_clicked()
{
    QString filePath = QFileDialog::getOpenFileName(this, "open", "../");
    // 如果选择文件有效
    if (false == filePath.isEmpty())
    {
        fileName.clear();
        fileSize = 0;
        // 读文件信息
        QFileInfo info(filePath);
        fileName = info.fileName();    // 获取文件名字
        fileSize = info.size();    // 获取文件大小
        sendSize = 0;
        // 只读方式打开文件
        // 指定文件名字
        file.setFileName(filePath);
        // 打开文件
        bool isOk = file.open(QIODevice::ReadOnly);
        if (false == isOk)
        {
            qDebug() << "只读方式打开文件失败！";
        }
        // 提示打开文件的路径
        ui -> textEdit -> append(filePath);
        ui -> buttonFile -> setEnabled(false);
        ui -> buttonSend -> setEnabled(true);
    }
    else
    {
            qDebug() << "选择文件路径无效！";
    }
}

void ServerWidget::on_buttonSend_clicked()
{
    // 先发送文件头信息
    QString head = QString("%1##%2").arg(fileName).arg(fileSize);
    qint64 len = tcpSocket -> write(head.toUtf8());
    if (len > 0)    // 头部信息发送成功
    {
        // 发送真正的文件信息
        // 防止TCP黏包文件
        // 需要通过定时器延时 20ms
        timer.start(20);
    }
    else
    {
        qDebug() << "头部信息发送失败！";
        file.close();
        ui -> buttonFile -> setEnabled(true);
        ui -> buttonSend -> setEnabled(false);
    }
    // 发送真正文件信息
}

void ServerWidget::sendData()
{
    qint64 len = 0;
    do
    {
        // 每次发送数据的大小为4K
        char buf[4*1024] = {0};
        int len = 0;
        // 往文件中读数据
        len = file.read(buf, sizeof(buf));
        // 发送数据，读多少，发多少
        len = tcpSocket -> write(buf, len);
        // 发送的数据需要累加
        sendSize += len;
    }while(sendSize != fileSize);

    // 是否发送文件完毕
    /*if (sendSize == fileSize)
    {

        file.close();
        // 把客户端断开
        tcpSocket -> disconnectFromHost();
        tcpSocket -> close();
    }*/
}

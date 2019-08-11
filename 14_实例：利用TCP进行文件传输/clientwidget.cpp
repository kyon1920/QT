#include "clientwidget.h"
#include "ui_clientwidget.h"
#include <QDebug>
#include <QMessageBox>
#include <QHostAddress>

clientWidget::clientWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::clientWidget)
{
    ui->setupUi(this);
    isStart = true;
    ui -> progressBar -> setValue(0);
    setWindowTitle("客户端");
    move(1000,300);

    tcpSocket = new QTcpSocket(this);
    ui -> textEdit -> append("等待连接到服务器...");
    connect(tcpSocket, &QTcpSocket::readyRead,
            [=]()
                {
                    // 取出接收的内容
                    QByteArray buf = tcpSocket -> readAll();
                    // 取出接收的内容
                    if (isStart == true)
                    {
                        ui -> textEdit -> append("正在接受文件头信息...");
                        // 接收头
                        isStart = false;
                        // 解析头部信息 buf = "xxx##1024"
                        // QString str = "hello##1024";
                        // 拆包
                        // str.section("##", 0, 0);
                        // 初始化
                        ui -> textEdit -> append("文件头信息接受完成!");
                        ui -> textEdit -> append("正在初始化文件信息到本地...");
                        fileName = QString(buf).section("##", 0, 0);
                        fileSize = QString(buf).section("##", 1, 1).toInt();
                        recvSize = 0;
                        ui -> textEdit -> append("初始化完成!");
                        // 打开文件
                        file.setFileName(fileName);
                        bool isOk = file.open(QIODevice::WriteOnly);
                        if (false == isOk)
                        {
                            qDebug() << "WriteOnly error!";
                            ui -> textEdit -> append("打开文件失败!");

                            tcpSocket -> disconnectFromHost();
                            tcpSocket -> close();
                            return;    // 如果打开失败，中断函数
                        }
                        ui -> textEdit -> append("打开文件成功!");

                        // 弹出对话框，显示接收文件的信息
                        QString str = QString("接收的文件: [%1:%2KB]").arg(fileName).arg(fileSize);
                        QMessageBox::information(this, "文件信息", str);

                        // 设置进度条
                        ui -> progressBar -> setMinimum(0);    // 最小值
                        ui -> progressBar -> setMaximum(fileSize/1024);    // 最大值
                        ui -> progressBar -> setValue(0);    // 当前值
                    }
                     // 文件信息
                    else
                    {
                        qint64 len = file.write(buf);
                        if (len > 0)
                        {
                            recvSize += len;    // 累计接收大小
                            QString str1 = QString("正在接收...已完成[%1]").arg(recvSize);
                            ui -> textEdit -> append(str1);
                        }

                        QString str2 = QString::number(recvSize);
                        tcpSocket -> write(str2.toUtf8().data());

                        // 更新进度条
                        ui -> progressBar -> setValue(recvSize/1024);

                        // 文件接收完毕
                        if (recvSize == fileSize)
                        {
                            // 先给服务器发送 接收文件完成的消息
                            tcpSocket -> write("file done!");
                            file.close();
                            ui -> textEdit -> append("文件接收已完成!");
                            QMessageBox::information(this, "完成", "文件接收完成!");
                            tcpSocket -> disconnectFromHost();
                            tcpSocket -> close();
                        }
                    }

                });
}

clientWidget::~clientWidget()
{
    delete ui;
}

void clientWidget::on_buttonConnect_clicked()
{
    // 获取服务器的IP和端口
    QString ip = ui -> IP -> text();
    quint16 port = ui -> port -> text().toInt();
    // 开始连接
    tcpSocket -> connectToHost(QHostAddress(ip), port);
    ui -> textEdit -> append("成功连接到服务器!");
}

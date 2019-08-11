#ifndef CLIENTWIDGET_H
#define CLIENTWIDGET_H

#include <QWidget>
#include <QTcpSocket>
#include <QFile>

namespace Ui {
class clientWidget;
}

class clientWidget : public QWidget
{
    Q_OBJECT

public:
    explicit clientWidget(QWidget *parent = nullptr);
    ~clientWidget();

private slots:
    void on_buttonConnect_clicked();

private:
    Ui::clientWidget *ui;

    QTcpSocket *tcpSocket;
    QFile file;    // 文件对象
    QString fileName;    // 文件名字
    qint64 fileSize;    // 文件大小
    qint64 recvSize;    // 已经发送文件大小

    bool isStart;
};

#endif // CLIENTWIDGET_H

#ifndef CLIENTWIDGET_H
#define CLIENTWIDGET_H

#include <QWidget>
#include <QTcpSocket>    // 通信套接字

namespace Ui {
class ClientWidget;
}

class ClientWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ClientWidget(QWidget *parent = nullptr);
    ~ClientWidget();

private slots:
    void on_ButtonSend_clicked();

    void on_ButtonConnect_clicked();

    void on_ButtonClose_clicked();

private:
    Ui::ClientWidget *ui;

    QTcpSocket *tcpSocket;
};

#endif // CLIENTWIDGET_H

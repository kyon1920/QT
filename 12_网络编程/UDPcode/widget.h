#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QUdpSocket>    // UDP套接字

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();
    void dealMsg();    // 槽函数

private slots:
    void on_ButtonSend_clicked();

private:
    Ui::Widget *ui;

    QUdpSocket *udpSocket;    // UDP套接字
};

#endif // WIDGET_H

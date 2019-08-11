#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QWidget>
#include <QUdpSocket>

namespace Ui {
class MyWidget;
}

class MyWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MyWidget(QWidget *parent = nullptr);
    ~MyWidget();

private slots:
    void on_ButtonSend_clicked();

private:
    Ui::MyWidget *ui;
    QUdpSocket *udpSocket;
};

#endif // MYWIDGET_H

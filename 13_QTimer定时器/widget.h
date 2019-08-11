#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTimer>    // 定时器对象头文件

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_ButtonStart_clicked();

    void on_ButtonStop_clicked();

private:
    Ui::Widget *ui;

    // 创建定时器对象
    // 一个定时器一个对象，不像前面需要定时器ID标识来区分多个定时器
    QTimer *myTimer;    // 创建定时器对象
};

#endif // WIDGET_H

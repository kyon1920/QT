#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();
    // 通过二进制操作文件
    void writeData();
    void readData();

    // 以文本方式操作文本
    void writeTextData();
    void readTextData();

private slots:
    void on_buttonRead_clicked();

    void on_buttonWrite_clicked();

    void on_buttonRead_pressed();

private:
    Ui::Widget *ui;
};

#endif // WIDGET_H

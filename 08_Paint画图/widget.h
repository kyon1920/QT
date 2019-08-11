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

private:
    Ui::Widget *ui;
    int x;

protected:
    // 重写绘图事件  虚函数
    // 如果在窗口绘图，必须放在绘图事件里面实现
    // 绘图事件内部自动调用，窗口需要重绘的时候
    void paintEvent(QPaintEvent *);


private slots:
    void on_pushButton_clicked();
};

#endif // WIDGET_H

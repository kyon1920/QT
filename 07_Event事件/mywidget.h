#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QWidget>

namespace Ui {
class MyWidget;
}

class MyWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MyWidget(QWidget *parent = nullptr);
    ~MyWidget();

protected:
    // 键盘按下事件
    void keyPressEvent(QKeyEvent *e);
    // 计时器事件
    void timerEvent(QTimerEvent *e);

    void mousePressEvent(QMouseEvent *e);

    // 关闭事件
    void closeEvent(QCloseEvent *);

    // 重写event()
    //bool event(QEvent *);

    // 事件过滤器
    bool eventFilter(QObject *obj, QEvent *);

private:
    Ui::MyWidget *ui;

    int timerId;
    int timerId2;
};

#endif // MYWIDGET_H

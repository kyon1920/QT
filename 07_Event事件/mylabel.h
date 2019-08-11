#ifndef MYLABEL_H
#define MYLABEL_H

#include <QLabel>

class MyLabel : public QLabel
{
    Q_OBJECT
public:
    explicit MyLabel(QWidget *parent = nullptr);

protected:
    // 鼠标事件：点击/释放/移动
    void mousePressEvent(QMouseEvent *ev);
    void mouseReleaseEvent(QMouseEvent *ev);
    void mouseMoveEvent(QMouseEvent *ev);

    // 进入窗口区域
    void enterEvent(QEvent *);
    // 离开窗口区域
    void leaveEvent(QEvent *);
signals:

public slots:
};

#endif // MYLABEL_H

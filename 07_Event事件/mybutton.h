#ifndef MYBUTTON_H
#define MYBUTTON_H

#include <QPushButton>

class MyButton : public QPushButton
{
    Q_OBJECT
public:
    explicit MyButton(QWidget *parent = nullptr);

signals:

public slots:

protected:
    // 事件的接收和忽略
    void mousePressEvent(QMouseEvent *e);
};

#endif // MYBUTTON_H

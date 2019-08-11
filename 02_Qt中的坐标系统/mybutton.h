#ifndef MYBUTTON_H
#define MYBUTTON_H

#include <QPushButton>

class MyButton : public QPushButton
{
    Q_OBJECT
public:
    explicit MyButton(QPushButton *parent = nullptr);

    ~MyButton();
signals:

public slots:
};

#endif // MYBUTTON_H

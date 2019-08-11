#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QPushButton>
#include "subwidget.h"    //子窗口头文件

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    MainWidget(QWidget *parent = 0);
    ~MainWidget();

//Qt4在此加 public slots

    void changeTextSlot();
    void changeWindowSlot();
    void changeWindowsSlot();
    void dealWindowSlot(int, QString);
private:
    QPushButton b1;
    QPushButton *b2;
    QPushButton b3;
    QPushButton *b4;
    QPushButton b5;

    SubWidget w;
};

#endif // MAINWIDGET_H

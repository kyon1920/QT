#ifndef WIDGET_H
#define WIDGET_H

#include "domxml.h"
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

    DomXML domxml;
};

#endif // WIDGET_H

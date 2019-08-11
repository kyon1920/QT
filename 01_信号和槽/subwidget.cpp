#include "subwidget.h"

SubWidget::SubWidget(QWidget *parent) : QWidget(parent)
{
    this -> setWindowTitle("老王");

    b.setParent(this);
    b.setText("切换到老张的窗口");
    b.move(150,150);
    b.setFixedSize(183,25);

    connect(&b, &QPushButton::clicked, this, &SubWidget::changeWindowsSlot);
}

void SubWidget::changeWindowsSlot()
{
    emit changeWindowSlot();
    emit changeWindowSlot(250, "我是老王");
}

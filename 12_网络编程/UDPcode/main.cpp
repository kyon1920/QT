#include "widget.h"
#include "mywidget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.show();
    MyWidget w2;
    w2.show();

    return a.exec();
}

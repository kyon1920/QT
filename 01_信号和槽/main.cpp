#include "mainwidget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWidget w;
    w.setMinimumSize(500,500);
    w.show();

    return a.exec();
}

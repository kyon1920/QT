#include "serverwidget.h"
#include "clientwidget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ServerWidget w;
    w.show();
    ClientWidget z;
    z.show();

    return a.exec();
}

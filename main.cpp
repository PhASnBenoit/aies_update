#include "fihm.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    fihm w;
    w.show();

    return a.exec();
}

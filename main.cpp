#include "havadurumu.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    havadurumu w;

    w.show();

    return a.exec();
}

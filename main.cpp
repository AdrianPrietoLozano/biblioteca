#include "dialog.h"
#include <QApplication>

#include "modificar.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Dialog w;
    w.show();

//    Modificar *m = new Modificar();
//    m->show();

    return a.exec();
}

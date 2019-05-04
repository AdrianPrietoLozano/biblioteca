#ifndef ELIMINAREMPLEADO_H
#define ELIMINAREMPLEADO_H

#include <QDialog>

namespace Ui {
class EliminarEmpleado;
}

class EliminarEmpleado : public QDialog
{
    Q_OBJECT

public:
    explicit EliminarEmpleado(QWidget *parent = 0);
    ~EliminarEmpleado();

private:
    Ui::EliminarEmpleado *ui;
};

#endif // ELIMINAREMPLEADO_H

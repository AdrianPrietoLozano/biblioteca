#include "eliminarempleado.h"
#include "ui_eliminarempleado.h"

EliminarEmpleado::EliminarEmpleado(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EliminarEmpleado)
{
    ui->setupUi(this);
}

EliminarEmpleado::~EliminarEmpleado()
{
    delete ui;
}

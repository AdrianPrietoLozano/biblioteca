#include "infoprestamo.h"
#include "ui_infoprestamo.h"

InfoPrestamo::InfoPrestamo(QWidget *parent, const QString &fechaPrestamo, const QString &fechaEntrega) :
    QDialog(parent),
    ui(new Ui::InfoPrestamo)
{
    ui->setupUi(this);

    ui->lineEditFechaPrestamo->setText(fechaPrestamo);
    ui->lineEditFechaEntrega->setText(fechaEntrega);
}

InfoPrestamo::~InfoPrestamo()
{
    delete ui;
}

void InfoPrestamo::on_pushButtonAceptar_clicked()
{
    close();
}

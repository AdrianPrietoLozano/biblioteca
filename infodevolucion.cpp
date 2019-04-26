#include "infodevolucion.h"
#include "ui_infodevolucion.h"
#include <QMessageBox>
#include <QDateTime>

InfoDevolucion::InfoDevolucion(QWidget *parent, const QString &titulo, const QString &nombre,
                               const QDateTime fecha_entrega, const QString &retraso, const float penalizacion) :
    QDialog(parent),
    ui(new Ui::InfoDevolucion)
{
    ui->setupUi(this);

    ui->lineEditTituloLibro->setText(titulo);
    ui->lineEditNombreCliente->setText(nombre);
    ui->lineEditFechaOriginal->setText(fecha_entrega.toString("dddd dd MMM yyyy,  hh:mm ap"));
    ui->lineEditFechaEntrega->setText(QDateTime::currentDateTime().toString("dddd dd MMM yyyy,  hh:mm ap"));
    ui->lineEditRetraso->setText(retraso);
    ui->lineEditPenalizacion->setText(QString::number(penalizacion));
}

InfoDevolucion::~InfoDevolucion()
{
    delete ui;
}

void InfoDevolucion::on_pushButton_clicked()
{
    close();
}

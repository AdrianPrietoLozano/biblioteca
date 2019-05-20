#include <QMessageBox>
#include <QDateTime>
#include <QDesktopServices>
#include <QUrl>
#include "infodevolucion.h"
#include "ui_infodevolucion.h"

InfoDevolucion::InfoDevolucion(QWidget *parent, const QString &titulo, const QString &nombre,
                               const QDateTime fecha_entrega, const QString &retraso, const float penalizacion,
                               const QString &nombreRecibo) :
    QDialog(parent),
    ui(new Ui::InfoDevolucion)
{
    ui->setupUi(this);

    ui->lineEditTituloLibro->setText(titulo);
    ui->lineEditNombreCliente->setText(nombre);
    ui->lineEditFechaOriginal->setText(fecha_entrega.toString("dddd dd MMM yyyy,  hh:mm ap"));
    ui->lineEditFechaEntrega->setText(QDateTime::currentDateTime().toString("dddd dd MMM yyyy,  hh:mm ap"));
    ui->lineEditRetraso->setText(retraso);
    ui->lineEditPenalizacion->setText("$" + QString::number(penalizacion));

    this->nombreRecibo = nombreRecibo;

    if(nombreRecibo == "") // si no hubo retrasos en la entrega
        ui->botonVerRecibo->setVisible(false);
    else // si hubo retraso
        ui->botonVerRecibo->setVisible(true);
}

InfoDevolucion::~InfoDevolucion()
{
    delete ui;
}

void InfoDevolucion::on_pushButton_clicked()
{
    close();
}

void InfoDevolucion::on_botonVerRecibo_clicked()
{
    QDesktopServices::openUrl(QUrl::fromLocalFile(nombreRecibo));
}

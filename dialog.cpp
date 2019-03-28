#include "dialog.h"
#include "ui_dialog.h"
#include "mainwindow.h"

#include <QString>
#include <QMessageBox>

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    principal = new MainWindow();

    ui->lineEditNombre->setPlaceholderText("Usuario");
    ui->lineEditPass->setPlaceholderText("Contraseña");
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_pushButtonAceptar_clicked()
{
    //QString usuario = "equipo 7";
    //QString contrasenia = "12345";
    QString usuario = ui -> lineEditNombre -> text();
    QString contrasenia = ui -> lineEditPass -> text();

    /*if(ui->lineEditNombre->text() == usuario &&
            ui->lineEditPass->text() == contrasenia)
    {
        this->hide();
        principal->show();
    }*/

    if(usuario == contrasenia){
        this -> hide();
        principal -> show();
    }

    else
    {
        QMessageBox msg;
        msg.setText( "Usuario o contraseña incorrectos" );
        msg.exec();
    }
}

void Dialog::on_pushButtonCancelar_clicked()
{
    close();
}

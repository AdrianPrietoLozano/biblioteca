#include "dialog.h"
#include "ui_dialog.h"
#include "mainwindow.h"
#include <QtSql>

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
    bool bandera = false;

    QString usuario = ui -> lineEditNombre -> text();
    QString contrasenia = ui -> lineEditPass -> text();

    QSqlDatabase db = QSqlDatabase::addDatabase("QPSQL", "coneccion");
    db.setHostName("localhost");
    db.setDatabaseName("biblioteca");
    db.setUserName("adrian");
    db.setPassword("12345");

    if(db.open())
    {
        QSqlQuery query(db);

        /*
        query.exec("SELECT * FROM usuarios");

        for(unsigned i = 0; query.next(); i++)
        {
            if(usuario == query.value(0) && contrasenia == query.value(1))
            {
                bandera = true;
            }
        }

        if(bandera)
        {
            this->hide();
            principal->show();
        }*/

        this->hide();
        principal->show();

        /*
        else
        {
            QMessageBox msg;
            msg.setText( "Usuario o contraseña incorrectos" );
            msg.exec();
        }
        */
    }

}

void Dialog::on_pushButtonCancelar_clicked()
{
    close();
}

void Dialog::on_pushButton_clicked()
{
    this->hide();

    p = new permiso(this);

    p->setModal(true);
    p->exec();

    if(p->result())
    {
        this->show();
    }
}

#include "dialog.h"
#include "ui_dialog.h"
#include "mainwindow.h"
#include <QtSql>
#include <QPixmap>

#include <QString>
#include <QMessageBox>

#define CLAVE "equipo7"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);

    ui->lineEditNombre->setPlaceholderText("Usuario");
    ui->lineEditPass->setPlaceholderText("Contraseña");

    QPixmap image(":/imagenes/libroBibliotecaSF.png");
    int w = ui->label_image->width(), h = ui->label_image->height();
    ui->label_image->setPixmap(image.scaled(w, h, Qt::KeepAspectRatio));
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_pushButtonAceptar_clicked()
{
    QString usuario = ui->lineEditNombre->text();
    QString contrasenia = ui->lineEditPass->text();

    QSqlDatabase db = QSqlDatabase::addDatabase("QPSQL", "coneccion");
    db.setHostName("localhost");
    db.setDatabaseName("biblioteca");
    db.setUserName("adrian");
    db.setPassword("12345");

    if(db.open())
    {
        QString select = "SELECT codigo, es_administrador FROM empleado WHERE nombre_usuario=? "\
                "AND PGP_SYM_DECRYPT(contrasenia, ?)=?";

        QSqlQuery query(db);
        query.prepare(select);
        query.bindValue(0, usuario);
        query.bindValue(1, CLAVE);
        query.bindValue(2, contrasenia);

        qDebug() << query.lastQuery();

        query.exec();

        if(query.next())
        {
            principal = new MainWindow(query.value("codigo").toString(), query.value("es_administrador").toBool());

            this->close();
            principal->show();
        }
        else
            QMessageBox::critical(this, "Error", "Usuario o contraseña incorrectos");
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

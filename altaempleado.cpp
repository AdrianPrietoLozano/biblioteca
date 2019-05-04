#include "altaempleado.h"
#include "ui_altaempleado.h"
#include "mainwindow.h"
#include <QtSql>
#include <QMessageBox>

AltaEmpleado::AltaEmpleado(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AltaEmpleado)
{
    ui->setupUi(this);
    db = QSqlDatabase::database("coneccion");
}

AltaEmpleado::~AltaEmpleado()
{
    delete ui;
}

void AltaEmpleado::on_pushButtonAceptar_clicked()
{
    QSqlQuery query(db);

    if(db.open())
    {
        QString select = "SELECT * FROM empleado WHERE nombre=? OR nombre_usuario=?";
        query.prepare(select);
        query.bindValue(0, ui->lineEditNombre->text());
        query.bindValue(1, ui->lineEditUsuario->text());
        query.exec();

        if(query.next()) // ya existe el empleado
            QMessageBox::critical(this, "Error", "Error: ya existe el empleado");
        else
        {
            if(ui->lineEditContrasenia->text() == ui->lineEditRepiteContrasenia->text()) // las contr. coinciden
                if(insertarEmpleado())
                    close();
                else
                    QMessageBox::critical(this, "Error", "Ocurrio algún error al insertar el empleado");
            else
                QMessageBox::critical(this, "Error", "Error: la contraseña no coincide");
        }
    }
}

bool AltaEmpleado::insertarEmpleado()
{
    QSqlQuery query(db);
    QString sexo = "H";

    if(db.open())
    {
        QString insert = "INSERT INTO empleado(nombre, nombre_usuario, contrasenia, edad, salario, sexo, es_administrador)"\
            "VALUES(?, ?, PGP_SYM_ENCRYPT(?, 'equipo7'), ?, ?, ?, FALSE)";

        if(ui->radioButtonMujer->isChecked())
            sexo = "M";

        query.prepare(insert);
        query.bindValue(0, ui->lineEditNombre->text());
        query.bindValue(1, ui->lineEditUsuario->text());
        query.bindValue(2, ui->lineEditContrasenia->text());
        query.bindValue(3, ui->spinBoxEdad->text());
        query.bindValue(4, ui->doubleSpinBoxSalario->text());
        query.bindValue(5, sexo);

        if(query.exec())
        {
            db.commit();
            return true;
        }
    }

    return false;
}

void AltaEmpleado::on_pushButtonCancelar_clicked()
{
    close();
}

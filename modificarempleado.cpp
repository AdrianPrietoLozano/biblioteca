#include "modificarempleado.h"
#include "ui_modificarempleado.h"
#include <QtSql>
#include <QMessageBox>

ModificarEmpleado::ModificarEmpleado(const QString &codigoEmpleado, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ModificarEmpleado)
{
    ui->setupUi(this);
    db = QSqlDatabase::database("coneccion");

    llenarCampos(codigoEmpleado);
}

ModificarEmpleado::~ModificarEmpleado()
{
    delete ui;
}

void ModificarEmpleado::on_buttonBox_accepted()
{
    QString sexo;

    if(existeEmpleado())
        QMessageBox::critical(this, "Error", "Ya existe un empleado con ese nombre de usuario");
    else
    {
        if(db.open())
        {
            QSqlQuery query(db);
            QString update = "UPDATE empleado SET nombre=?, nombre_usuario=?, contrasenia=PGP_SYM_ENCRYPT(?, 'equipo7'), "
                             "edad=?, salario=?, sexo=?, es_administrador=FALSE WHERE codigo=?";

            query.prepare(update);

            if(ui->radioButtonHombre->isChecked())
                sexo = "H";
            else
                sexo = "M";

            query.bindValue(0, ui->lineEditNombre->text());
            query.bindValue(1, ui->lineEditUsuario->text());
            query.bindValue(2, ui->lineEditContrasenia->text());
            query.bindValue(3, ui->spinBoxEdad->value());
            query.bindValue(4, ui->doubleSpinBoxSalario->value());
            query.bindValue(5, sexo);
            query.bindValue(6, ui->lineEditCodigo->text());

            if(query.exec())
            {
                db.commit();
                close();
            }
            else
                QMessageBox::critical(this, "Error", "Ocurrio un error al modificar el empleado");
        }
    }
}

void ModificarEmpleado::on_buttonBox_rejected()
{
    close();
}

void ModificarEmpleado::llenarCampos(const QString &codigoEmpleado)
{
    if(db.open())
    {
        QSqlQuery query(db);
        QString select = "SELECT codigo, nombre, nombre_usuario, PGP_SYM_DECRYPT(contrasenia, 'equipo7') AS contrasenia,"\
                "edad, salario, sexo FROM empleado WHERE codigo=" + codigoEmpleado;

        query.exec(select);

        if(query.next())
        {
            ui->lineEditCodigo->setText(query.value("codigo").toString());
            ui->lineEditNombre->setText(query.value("nombre").toString());
            ui->lineEditUsuario->setText(query.value("nombre_usuario").toString());
            ui->lineEditContrasenia->setText(query.value("contrasenia").toString());
            ui->spinBoxEdad->setValue(query.value("edad").toInt());
            ui->doubleSpinBoxSalario->setValue(query.value("salario").toFloat());

            if(query.value("sexo").toString() == "H")
                ui->radioButtonHombre->setChecked(true);
            else
                ui->radioButtonMujer->setChecked(true);
        }
    }
}

bool ModificarEmpleado::existeEmpleado()
{
    QString nombreUsuario = ui->lineEditUsuario->text();
    QString codigo = ui->lineEditCodigo->text();

    QSqlQuery query(db);

    if(db.open())
    {
        QString select = "SELECT * FROM empleado WHERE nombre_usuario=? AND codigo!=?";
        query.prepare(select);
        query.bindValue(0, nombreUsuario);
        query.bindValue(1, codigo);
        query.exec();

        if(!query.next()) //si no existe el empleado
            return false;
    }
    return true;
}

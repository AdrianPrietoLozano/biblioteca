#include "altacliente.h"
#include "ui_altacliente.h"
#include <QMessageBox>

AltaCliente::AltaCliente(QWidget *parent, const QString &codigoCliente, int tipoVentana, const QString &texto, const QString &titulo) :
    QDialog(parent),
    ui(new Ui::AltaCliente)
{
    ui->setupUi(this);
    db = QSqlDatabase::database("coneccion");
    ui->labelTexto->setText(texto);
    this->windowTitleChanged(titulo);

    this->tipoVentana = tipoVentana;
    this->codigoCliente = codigoCliente;

    modificar = "UPDATE cliente SET nombre=?, telefono=?, departamento=?, carrera=?, "\
                "grado=?, sexo=?, tipo=? WHERE codigo=" + codigoCliente;

    if(tipoVentana == MODIFICAR)
        llenarCampos();
}

AltaCliente::~AltaCliente()
{
    delete ui;
}

void AltaCliente::on_pushButtonAceptar_clicked()
{

    if(tipoVentana == MODIFICAR)
        procesarCliente(modificar, "Ocurrio un error al modificar el cliente");
    else
        procesarCliente(insertar, "Ocurrio un error al agregar el cliente");

}

void AltaCliente::on_pushButtonCancelar_clicked()
{
    close();
}

void AltaCliente::procesarCliente(const QString &sentencia, const QString &mensajeError)
{
    QString sexo, tipo;

    if(ui->lineEditNombre->text() == "") // el nombre no puede ser NULL
        QMessageBox::critical(this, "Error", "El nombre no puede estar vacío");
    else
    {
        if(db.open())
        {
            QSqlQuery query(db);

            if(ui->radioButtonMujer->isChecked())
                sexo = "M";
            else
                sexo = "H";

            if(ui->radioButtonProfesor->isChecked())
                tipo = "P";
            else if(ui->radioButtonAmbos->isChecked())
                tipo = "A";
            else
                tipo = "E";

            query.prepare(sentencia);
            query.bindValue(0, ui->lineEditNombre->text());
            query.bindValue(1, ui->lineEditTelefono->text());
            query.bindValue(2, ui->lineEditDepartamento->text());
            query.bindValue(3, ui->lineEditCarrera->text());
            query.bindValue(4, ui->spinBoxGrado->value());
            query.bindValue(5, sexo);
            query.bindValue(6, tipo);

            if(query.exec())
            {
                db.commit();
                close();
            }
            else
            {
                QMessageBox::critical(this, "Error", mensajeError);
                qDebug() << query.lastError();
            }
        }
    }
}

void AltaCliente::llenarCampos()
{
    if(db.open())
    {
        QSqlQuery query(db);
        QString select = "SELECT * FROM cliente WHERE codigo=" + codigoCliente;

        query.exec(select);

        if(query.next())
        {
            ui->lineEditNombre->setText(query.value("nombre").toString());
            ui->lineEditTelefono->setText(query.value("telefono").toString());
            ui->lineEditCarrera->setText(query.value("carrera").toString());
            ui->lineEditDepartamento->setText(query.value("departamento").toString());
            ui->spinBoxGrado->setValue(query.value("grado").toInt());
            completarSexo(query.value("sexo").toString());
            completarTipo(query.value("tipo").toString());
        }
    }
}

void AltaCliente::completarSexo(const QString &sexo)
{
    if(sexo == "H")
        ui->radioButtonHombre->setChecked(true);
    else if(sexo == "M")
        ui->radioButtonMujer->setChecked(true);
    else
    {
        ui->radioButtonHombre->setChecked(false);
        ui->radioButtonMujer->setChecked(false);
    }
}

void AltaCliente::completarTipo(const QString &tipo)
{
    if(tipo == "E")
        ui->radioButtonEstudiante->setChecked(true);

    else if(tipo == "P")
        ui->radioButtonProfesor->setChecked(true);

    else if(tipo == "A")
        ui->radioButtonAmbos->setChecked(true);

    else
    {
        ui->radioButtonEstudiante->setChecked(false);
        ui->radioButtonProfesor->setChecked(false);
        ui->radioButtonAmbos->setChecked(false);
    }
}

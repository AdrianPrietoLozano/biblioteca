#include "prestamo.h"
#include "ui_prestamo.h"
#include <QtSql>
#include <QDebug>
#include <QMessageBox>
#include <QDateTime>

// segundos en 3 horas
#define SEGUNDOS_PRESTAR_PRIMER_EJEMPLAR 10800
#define DIAS_PRESTAMO_ESTUDIANTE 7
#define DIAS_PRESTAMO_MAESTRO 15
#define MAX_PRESTAMOS_ESTUDIANTE 5
#define MAX_PRESTAMOS_MAESTRO 7

Prestamo::Prestamo(QWidget *parent, const QString &codigoEmpleado) :
    QDialog(parent),
    codigoEmpleado(codigoEmpleado),
    ui(new Ui::Prestamo)
{
    ui->setupUi(this);
    db = QSqlDatabase::database("coneccion");
}

Prestamo::~Prestamo()
{
    delete ui;
}

void Prestamo::on_botonCancelar_clicked()
{
    close();
}

bool Prestamo::existeLibro(const QString &codigo)
{
    QSqlQuery query(db);

    if(db.open())
    {
        QString select = "SELECT codigo FROM libro WHERE codigo=" + codigo;
        query.exec(select);

        return query.next();
    }

    return false;
}


bool Prestamo::libroDisponible(const QString &codigo)
{
    QSqlQuery query(db);

    if(db.open())
    {
        QString select = "SELECT codigo FROM prestamo WHERE codigo_libro=" + codigo;
        query.exec(select);

        return query.size() == 0;
    }
    return false;
}


bool Prestamo::sePuedePrestar(const QString &codigo)
{
    QSqlQuery query(db);

    if(db.open())
    {
        QString select = "SELECT ejemplar FROM libro WHERE codigo=" + codigo;
        query.exec(select);

        if(query.next())
        {
            int dia = QDate::currentDate().dayOfWeek();
            int ejemplar = query.value("ejemplar").toInt();

            if(ejemplar == 1 && dia == 5) // es primer ejemplar y es viernes
                return true;
            else if(ejemplar == 1 && dia != 5) // es primer ejemplar y no es viernes
                return false;

            return true; // es cualquier otro ejemplar
        }
    }
    return false;
}


void Prestamo::completarInfoLibro(const QString &codigo)
{
    QSqlQuery query(db);

    if(db.open())
    {
        QString select = "SELECT titulo, autor, ejemplar, isbn FROM libro WHERE codigo=" + codigo;
        query.exec(select);
        if(query.next())
        {
            ui->lineEditTitulo->setText(query.value("titulo").toString());
            ui->lineEditAutor->setText(query.value("autor").toString());
            ui->lineEditEjemplar->setText(query.value("ejemplar").toString());
            ui->lineEditIsbn->setText(query.value("isbn").toString());
        }
    }
}

void Prestamo::cambiarInfoLibro(const QString &mensaje, bool debeLimpiar)
{
    if(debeLimpiar)
    {
        ui->lineEditTitulo->clear();
        ui->lineEditAutor->clear();
        ui->lineEditEjemplar->clear();
        ui->lineEditIsbn->clear();
    }

    ui->labelLibro->setText("<font color='red'>" + mensaje + "</font>");
    ui->botonAceptar->setEnabled(false);
}


bool Prestamo::existeCliente(const QString &codigo)
{
    QSqlQuery query(db);

    if(db.open())
    {
        QString select = "SELECT codigo FROM usuario WHERE codigo=?";
        query.prepare(select);
        query.bindValue(0, codigo);
        query.exec();

        return query.next();
    }
    return false;
}


bool Prestamo::puedeHacerMasPrestamos(const QString &codigo)
{
    QSqlQuery query(db);

    if(db.open())
    {
        // regresa el tipo de usuario y la cantidad de préstamos que ha solicitado
        QString select = "SELECT usuario.tipo AS tipo, count(prestamo.codigo) AS num_prestamos "\
                "FROM usuario, prestamo WHERE usuario.codigo=? AND prestamo.codigo_cliente=? GROUP BY usuario.tipo";
        query.prepare(select);
        query.bindValue(0, codigo);
        query.bindValue(1, codigo);
        query.exec();
        query.next();

        int numMaxPrestamos = (query.value("tipo").toString() == "E" ? MAX_PRESTAMOS_ESTUDIANTE : MAX_PRESTAMOS_MAESTRO);

        return query.value("num_prestamos").toInt() < numMaxPrestamos;
    }
    return false;
}


void Prestamo::completarInfoCliente(const QString &codigo)
{
    QSqlQuery query(db);

    if(db.open())
    {
        QString select = "SELECT nombre, departamento, tipo FROM usuario WHERE codigo=" + codigo;
        query.exec(select);

        if(query.next())
        {
            ui->lineEditNombre->setText(query.value("nombre").toString());
            ui->lineEditDpto->setText(query.value("departamento").toString());

            QString tipoCliente = (query.value("tipo").toString() == "E" ? "Estudiante" : "Profesor");
            ui->lineEditTipo->setText(tipoCliente);

            ui->labelCliente->clear();
        }
    }

    // si la info. del libro es correcta se activa el botón Aceptar
    bool activarBoton = (esLibroValido ? true : false);
    ui->botonAceptar->setEnabled(activarBoton);
}


void Prestamo::cambiarInfoCliente(const QString &mensaje, bool debeLimpiar)
{
    if(debeLimpiar)
    {
        ui->lineEditNombre->clear();
        ui->lineEditDpto->clear();
        ui->lineEditTipo->clear();
    }

    ui->labelCliente->setText("<font color='red'>" + mensaje + "</font>");
    ui->botonAceptar->setEnabled(false);
}


void Prestamo::on_lineEditCodigoLibro_textEdited(const QString &arg1)
{
    esLibroValido = false;
    if(existeLibro(arg1))
    {
        completarInfoLibro(arg1);
        if(libroDisponible(arg1))
            if(sePuedePrestar(arg1))
            {
                esLibroValido = true;
                ui->labelLibro->clear();

                // si la info. del cliente es válida se activa el botón aceptar
                bool activarBoton = (esClienteValido ? true : false);
                ui->botonAceptar->setEnabled(activarBoton);
            }
            else
                 cambiarInfoLibro("El primer ejemplar solo se presta el viernes", false);
        else
             cambiarInfoLibro("El libro ya se presto", false);
    }
    else
        cambiarInfoLibro("No existe el libro", true);
}


void Prestamo::on_lineEditCodigoCliente_textEdited(const QString &arg1)
{
    esClienteValido = false;
    if(existeCliente(arg1))
    {
       completarInfoCliente(arg1);
       if(puedeHacerMasPrestamos(arg1))
       {
           esClienteValido = true;
           ui->labelCliente->clear();

           // si la info. del libro es válida se activa el botón aceptar
           bool activarBoton = (esLibroValido ? true : false);
           ui->botonAceptar->setEnabled(activarBoton);
       }
        else
            cambiarInfoCliente("Número de préstamos exedido", false);
    }
    else
        cambiarInfoCliente("No se encontró el cliente", true);
}

bool Prestamo::insertarRegistroPrestamo(const QString &codigoLibro, const QString &codigoCliente,
                                        const QString &codigoEmpleado, const QDateTime horaPrestamo,
                                        const QDateTime horaEntrega)
{
    QSqlQuery query(db);

    if(db.open())
    {
        QString insert = "INSERT INTO prestamo(codigo_libro, codigo_cliente, codigo_empleado, "\
                        "fecha_prestamo, fecha_entrega) VALUES ( "\
                        "?, ?, ?, to_timestamp(?, 'dd-mm-yyyy hh24:mi:ss'), "\
                        "to_timestamp(?, 'dd-mm-yyyy hh24:mi:ss'))";
        query.prepare(insert);
        query.bindValue(0, codigoLibro);
        query.bindValue(1, codigoCliente);
        query.bindValue(2, codigoEmpleado);
        query.bindValue(3, horaPrestamo.toString("dd-MM-yyyy hh:mm:ss"));
        query.bindValue(4, horaEntrega.toString("dd-MM-yyyy hh:mm:ss"));

        if(query.exec())
        {
            db.commit();
            return true;
        }
        qDebug() << query.lastError();
    }
    return false;
}


void Prestamo::mostrarInfoPrestamo(const QDateTime &horaPrestamo, const QDateTime &horaEntrega)
{
    InfoPrestamo *infoPrestamo = new InfoPrestamo(this,
                                                 horaPrestamo.toString("dddd dd MMM yyyy,  hh:mm ap"),
                                                 horaEntrega.toString("dddd dd MMM yyyy,  hh:mm ap"));
    infoPrestamo->exec();
}

void Prestamo::on_botonAceptar_clicked()
{
    if(QTime::currentTime() <= horaDeCerrar)
    {
        QString codigoLibro = ui->lineEditCodigoLibro->text();
        QString codigoCliente = ui->lineEditCodigoCliente->text();
        QString tipoUsuario = ui->lineEditTipo->text();
        int ejemplar = ui->lineEditEjemplar->text().toInt();

        QDateTime horaPrestamo = QDateTime::currentDateTime();
        QDateTime horaEntrega;

        if(ejemplar == 1) // es primer ejemplar, solo se presta 3 horas
            horaEntrega = horaPrestamo.addSecs(SEGUNDOS_PRESTAR_PRIMER_EJEMPLAR);
        else if(tipoUsuario == "Estudiante"){
            horaEntrega = horaPrestamo.addDays(DIAS_PRESTAMO_ESTUDIANTE);
            horaEntrega.setTime(horaDeCerrar);
        }
        else if(tipoUsuario == "Maestro"){
            horaEntrega = horaPrestamo.addDays(DIAS_PRESTAMO_MAESTRO);
            horaEntrega.setTime(horaDeCerrar);
        }

        if(insertarRegistroPrestamo(codigoLibro, codigoCliente, codigoEmpleado, horaPrestamo, horaEntrega))
            mostrarInfoPrestamo(horaPrestamo, horaEntrega);
        else
            qDebug() << "Error";
    }
    else
    {
        QMessageBox msg(this);
        msg.setText("No es posible realizar más préstamos");
        msg.setWindowTitle("Fuera de tiempo");
        msg.exec();
    }

    close();
}


//
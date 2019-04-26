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

QMap<QString, QString> Prestamo::atributosLibro(const QString &codigo)
{
    QSqlQuery query(db);
    QMap<QString, QString> valores;

    if(db.open())
    {
        QString select = "SELECT titulo, autor, ejemplar, isbn, COUNT(prestamo.codigo_libro) AS cantidad_prestamos "\
                "FROM libro LEFT JOIN prestamo ON libro.codigo=prestamo.codigo_libro "\
                "WHERE libro.codigo=" + codigo + " GROUP BY libro.codigo";
        query.exec(select);

        if(query.next())
        {
            valores["titulo"] = query.value("titulo").toString();
            valores["autor"] = query.value("autor").toString();
            valores["ejemplar"] = query.value("ejemplar").toString();
            valores["isbn"] = query.value("isbn").toString();
            valores["cantidad_prestamos"] = query.value("cantidad_prestamos").toString();
        }
    }

    return valores;
}

bool Prestamo::sePuedePrestar(const int ejemplar)
{
    int dia = QDate::currentDate().dayOfWeek();

    if(ejemplar == 1 && dia != 5) // es primer ejemplar y es viernes
        return false;

    return true;
}


void Prestamo::completarInfoLibro(const QString &titulo, const QString &autor,
                                  const QString &ejemplar, const QString &isbn)
{
    ui->lineEditTitulo->setText(titulo);
    ui->lineEditAutor->setText(autor);
    ui->lineEditEjemplar->setText(ejemplar);
    ui->lineEditIsbn->setText(isbn);
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



QMap<QString, QString> Prestamo::atributosCliente(const QString &codigo)
{
    QSqlQuery query(db);
    QMap<QString, QString> valores;

    if(db.open())
    {
        QString select = "SELECT nombre, departamento, tipo, COUNT(prestamo.codigo_cliente) AS cantidad_prestamos "\
                "FROM usuario LEFT JOIN prestamo ON usuario.codigo=prestamo.codigo_cliente "\
                "WHERE usuario.codigo=" + codigo + " GROUP BY usuario.codigo";
        query.exec(select);

        if(query.next())
        {
            valores["nombre"] = query.value("nombre").toString();
            valores["departamento"] = query.value("departamento").toString();
            valores["tipo"] = (query.value("tipo").toString() == "E" ? "Estudiante" : "Profesor");
            valores["cantidad_prestamos"] = query.value("cantidad_prestamos").toString();
        }
    }

    return valores;
}


bool Prestamo::puedeHacerMasPrestamos(const QString &tipoUsuario, const int cantidad_prestamos)
{
    int numMaxPrestamos = (tipoUsuario == "Estudiante" ? MAX_PRESTAMOS_ESTUDIANTE : MAX_PRESTAMOS_MAESTRO);

    return cantidad_prestamos < numMaxPrestamos;
}


void Prestamo::completarInfoCliente(const QString &nombre, const QString &departamento,
                                    const QString &tipo)
{
    ui->lineEditNombre->setText(nombre);
    ui->lineEditDpto->setText(departamento);
    ui->lineEditTipo->setText(tipo);
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
    QMap<QString, QString> atributos = atributosLibro(arg1);

    if(atributos.size() > 0)
    {
        completarInfoLibro(atributos["titulo"], atributos["autor"], atributos["ejemplar"],
                           atributos["isbn"]);
        if(atributos["cantidad_prestamos"].toInt() == 0) // aún no se presta (el libro esta disponible)
            if(sePuedePrestar(atributos["ejemplar"].toInt()))
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
    QMap<QString, QString> atributos = atributosCliente(arg1);

    if(atributos.size() > 0)
    {
       completarInfoCliente(atributos["nombre"], atributos["departamento"], atributos["tipo"]);
       if(puedeHacerMasPrestamos(atributos["tipo"], atributos["cantidad_prestamos"].toInt()))
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
        else if(tipoUsuario == "Profesor"){
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

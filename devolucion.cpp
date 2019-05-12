#include <QMessageBox>
#include "devolucion.h"
#include "ui_devolucion.h"
#include "infodevolucion.h"
#include "prestamo.h"

#define COBRO_HORA 1
#define COBRO_DIA 5

Devolucion::Devolucion(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Devolucion)
{
    ui->setupUi(this);
    db = QSqlDatabase::database("coneccion");
}

Devolucion::~Devolucion()
{
    delete ui;
}

void Devolucion::on_botonCancelar_clicked()
{
    close();
}

/* Retorna un QMap con algunos atributos y valores de un libro */
QMap<QString, QString> Devolucion::atributosLibro(const QString &codigo)
{
    QSqlQuery query(db);
    QMap<QString, QString> valores;

    if(db.open())
    {
        // selecciona info. del libro, si esta prestado y el cliente que se lo llevo
        QString select = "SELECT titulo, autor, ejemplar, isbn, COUNT(prestamo.codigo_libro) AS cantidad_prestamos, codigo_cliente "\
                         "FROM libro LEFT JOIN prestamo ON libro.codigo=prestamo.codigo_libro "\
                         "WHERE libro.codigo=" + codigo + " GROUP BY libro.codigo, codigo_cliente";
        query.exec(select);

        if(query.next())
        {
            valores["titulo"] = query.value("titulo").toString();
            valores["autor"] = query.value("autor").toString();
            valores["ejemplar"] = query.value("ejemplar").toString();
            valores["isbn"] = query.value("isbn").toString();
            valores["cantidad_prestamos"] = query.value("cantidad_prestamos").toString();
            valores["codigo_cliente"] = query.value("codigo_cliente").toString();
        }
    }

    return valores;
}


void Devolucion::completarInfoLibro(const QString &titulo, const QString &autor,
                                  const QString &ejemplar, const QString &isbn)
{
    ui->lineEditTitulo->setText(titulo);
    ui->lineEditAutor->setText(autor);
    ui->lineEditEjemplar->setText(ejemplar);
    ui->lineEditIsbn->setText(isbn);
}

void Devolucion::cambiarInfoLibro(const QString &mensaje, bool debeLimpiar)
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


void Devolucion::on_lineEditCodigoLibro_textEdited(const QString &arg1)
{
    QMap<QString, QString> atributos = atributosLibro(arg1);
    QString codigoCliente;

    if(atributos.size() > 0) // si existe el libro
    {
        completarInfoLibro(atributos["titulo"], atributos["autor"], atributos["ejemplar"],
                           atributos["isbn"]);
        if(atributos["cantidad_prestamos"].toInt() == 1) // el libro esta prestado (no esta disponible)
        {
            codigoCliente = ui->lineEditCodigoCliente->text();
            if(codigoCliente != "")
            {
                if(codigoCliente == atributos["codigo_cliente"]) // el cliente SI solicitó el libro
                {
                    ui->labelCliente->clear();
                    ui->labelLibro->clear();
                    ui->botonAceptar->setEnabled(true);
                }
                else
                {
                    cambiarInfoLibro("El cliente no solicito este libro", false);
                    ui->botonAceptar->setEnabled(false);
                }
            }
            else
            {
                ui->labelLibro->clear();
                ui->botonAceptar->setEnabled(false);
            }
        }
        else
             cambiarInfoLibro("El libro aún no se presta", false);
    }
    else
        cambiarInfoLibro("No existe el libro", true);
}








void Devolucion::completarInfoCliente(const QString &nombre, const QString &departamento,
                                    const QString &tipo)
{
    ui->lineEditNombre->setText(nombre);
    ui->lineEditDpto->setText(departamento);
    ui->lineEditTipo->setText(tipo);
}


void Devolucion::cambiarInfoCliente(const QString &mensaje, bool debeLimpiar)
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


/* Determina si un cliente solicitó un determinado libro */
bool Devolucion::clienteSolicitoLibro(const QString &codigoCliente, const QString &codigoLibro)
{
    QSqlQuery query(db);

    if(db.open())
    {
        QString select = "SELECT * FROM prestamo WHERE codigo_cliente=? AND codigo_libro=?";
        query.prepare(select);
        query.bindValue(0, codigoCliente);
        query.bindValue(1, codigoLibro);
        query.exec();

        return query.next();
    }

    return false;
}


void Devolucion::comprobarDevolucion()
{
    QString codigoLibro = ui->lineEditCodigoLibro->text();
    QString codigoCliente = ui->lineEditCodigoCliente->text();

    if(codigoLibro != "")
    {
        if(clienteSolicitoLibro(codigoCliente, codigoLibro))
        {
            ui->labelCliente->clear();
            ui->labelLibro->clear();
            ui->botonAceptar->setEnabled(true);
        }
        else
        {
            cambiarInfoCliente("El cliente no solicitó el libro", false);
            ui->botonAceptar->setEnabled(false);
        }
    }
    else
    {
        ui->labelCliente->clear();
        ui->botonAceptar->setEnabled(false);
    }
}



QString Devolucion::calcularRetraso(const int ejemplar, const QDateTime fecha_entrega)
{
    QString retraso;

    if(ejemplar == 1) // si es primer ejemplar se cobra por hora
    {
        int horasRetraso = fecha_entrega.secsTo(QDateTime::currentDateTime()) / 3600;
        if(horasRetraso < 0)
            horasRetraso = 0;

        retraso = QString::number(horasRetraso) + " horas";

    }
    else // no es primer ejemplar, se cobra por día
    {
        int diasRetraso = fecha_entrega.daysTo(QDateTime::currentDateTime()) - 1;
        if(diasRetraso < 0)
            diasRetraso = 0;

        retraso = QString::number(diasRetraso) + " días";
    }

    return retraso;
}

float Devolucion::calcularPenalizacion(const int ejemplar, const QDateTime fecha_entrega)
{
    float penalizacion = 0.0;

    if(ejemplar == 1) // si es primer ejemplar se cobra por hora
    {
        int horasRetraso = fecha_entrega.secsTo(QDateTime::currentDateTime()) / 3600;
        if(horasRetraso < 0)
            horasRetraso = 0;

        penalizacion = (float)horasRetraso * COBRO_HORA;

    }
    else // no es primer ejemplar, se cobra por día
    {
        int diasRetraso = fecha_entrega.daysTo(QDateTime::currentDateTime()) - 1;
        if(diasRetraso < 0)
            diasRetraso = 0;

        penalizacion = (float)diasRetraso * COBRO_DIA;
    }

    return penalizacion;
}

bool Devolucion::eliminarPrestamo(const QString &codigoLibro, const QString &codigoCliente)
{
    QSqlQuery query(db);

    if(db.open())
    {
        QString eliminar = "DELETE FROM prestamo WHERE codigo_libro=? AND codigo_cliente=?";
        query.prepare(eliminar);
        query.bindValue(0, codigoLibro);
        query.bindValue(1, codigoCliente);

        if(query.exec())
        {
            db.commit();
            return true;
        }
    }

    return false;
}


void Devolucion::on_lineEditCodigoCliente_textEdited(const QString &arg1)
{
    QMap<QString, QString> atributos = Prestamo::atributosCliente(arg1);

    if(atributos.size() > 0)
    {
        completarInfoCliente(atributos["nombre"], atributos["departamento"], atributos["tipo"]);
        if(atributos["cantidad_prestamos"].toInt() > 0) // el cliente se ha llevado algún libro
        {
            comprobarDevolucion();
        }
        else
            cambiarInfoCliente("El cliente no ha solicitado libros", false);
    }
    else
        cambiarInfoCliente("No existe el cliente", true);
}

void Devolucion::on_botonAceptar_clicked()
{
    float penalizacion = 0.0;
    QString retraso = "Sin retraso";
    QString codigoLibro = ui->lineEditCodigoLibro->text();
    QString codigoCliente = ui->lineEditCodigoCliente->text();

    //QTime::currentTime() <= horaDeCerrar
    if(true)
    {
        QSqlQuery query(db);

        if(db.open())
        {
            QString select = "SELECT ejemplar, fecha_entrega FROM prestamo, libro WHERE codigo_libro=? AND libro.codigo=?";
            query.prepare(select);
            query.bindValue(0, codigoLibro);
            query.bindValue(1, codigoLibro);
            query.exec();

            if(query.next()) // si existe el prestamo
            {
                if(QDateTime::currentDateTime() > query.value("fecha_entrega").toDateTime()) // si se entrega con retraso
                {
                    penalizacion = calcularPenalizacion(query.value("ejemplar").toInt(),
                                                        query.value("fecha_entrega").toDateTime());

                    retraso = calcularRetraso(query.value("ejemplar").toInt(),
                                              query.value("fecha_entrega").toDateTime());

                    // FALTA GENERAR RECIBO
                }

                eliminarPrestamo(codigoLibro, codigoCliente);
                InfoDevolucion *infoDevolucion = new InfoDevolucion(this, ui->lineEditTitulo->text(),
                                                                    ui->lineEditNombre->text(),
                                                                    query.value("fecha_entrega").toDateTime(),
                                                                    retraso, penalizacion);
                infoDevolucion->exec();
                delete infoDevolucion;
            }
            else
                QMessageBox::critical(this, "Error", "No se encontró el préstamo");
        }
    }
    else
        QMessageBox::information(this, "Fuera de tiempo", "No es posible realizar devoluciones");

    close();
}

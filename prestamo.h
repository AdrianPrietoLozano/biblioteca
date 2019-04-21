#ifndef PRESTAMO_H
#define PRESTAMO_H

#include <QDialog>
#include <QTime>
#include <QtSql>

#include "infoprestamo.h"

namespace Ui {
class Prestamo;
}

class Prestamo : public QDialog
{
    Q_OBJECT

public:
    explicit Prestamo(QWidget *parent, const QString &codigoEmpleado);
    ~Prestamo();

private slots:
    void on_botonCancelar_clicked();

    void on_lineEditCodigoLibro_textEdited(const QString &arg1);

    void on_lineEditCodigoCliente_textEdited(const QString &arg1);

    void on_botonAceptar_clicked();

private:
    Ui::Prestamo *ui;
    QTime horaDeCerrar = getHoraCerrar();
    QString codigoEmpleado;
    QSqlDatabase db;
    bool esClienteValido;
    bool esLibroValido;

    // libro
    bool existeLibro(const QString &codigo);
    bool libroDisponible(const QString &codigo);
    bool sePuedePrestar(const QString &codigo);
    void completarInfoLibro(const QString &codigo);
    void cambiarInfoLibro(const QString &mensaje, bool debeLimpiar);

    // cliente
    bool existeCliente(const QString &codigo);
    bool puedeHacerMasPrestamos(const QString &codigo);
    void completarInfoCliente(const QString &codigo);
    void cambiarInfoCliente(const QString &mensaje, bool debeLimpiar);

    void mostrarInfoPrestamo(const QDateTime &horaPrestamo, const QDateTime &horaEntrega);
    bool insertarRegistroPrestamo(const QString &codigoLibro, const QString &codigoCliente,
                                  const QString &codigoEmpleado, const QDateTime horaPrestamo,
                                  const QDateTime horaEntrega);

    QTime getHoraCerrar()
    {
        if(QDate::currentDate().dayOfWeek() == 6) // es sabado
            return QTime(14, 0); // se cierra a las 2pm el sábado
        else
            return QTime(17, 0); // se ciera a las 5pm de lunes a viernes
    }
};

#endif // PRESTAMO_H

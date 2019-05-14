#ifndef DEVOLUCION_H
#define DEVOLUCION_H

#include <QDialog>
#include <QtSql>

namespace Ui {
class Devolucion;
}

class Devolucion : public QDialog
{
    Q_OBJECT

public:
    explicit Devolucion(QWidget *parent = 0);
    ~Devolucion();

private slots:
    void on_botonCancelar_clicked();
    void on_lineEditCodigoLibro_textEdited(const QString &arg1);
    void on_lineEditCodigoCliente_textEdited(const QString &arg1);

    void on_botonAceptar_clicked();

private:
    Ui::Devolucion *ui;
    QSqlDatabase db;
    QTime horaDeCerrar = getHoraCerrar();

    // Libro
    QMap<QString, QString> atributosLibro(const QString &codigo);
    void completarInfoLibro(const QString &titulo, const QString &autor,
                            const QString &ejemplar, const QString &isbn);
    void cambiarInfoLibro(const QString &mensaje, bool debeLimpiar);


    // Cliente
    void completarInfoCliente(const QString &nombre, const QString &departamento, const QString &tipo);
    void cambiarInfoCliente(const QString &mensaje, bool debeLimpiar);
    bool clienteSolicitoLibro(const QString &codigoCliente, const QString &codigoLibro);
    void comprobarDevolucion();


    QString calcularRetraso(const int ejemplar, const QDateTime fecha_entrega);
    float calcularPenalizacion(const int ejemplar, const QDateTime fecha_entrega);
    bool eliminarPrestamo(const QString &codigoLibro, const QString &codigoCliente);
    void generarRecibo(const QString &codigoPrestamo, const QString &retraso, const QString &penalizacion);

    QTime getHoraCerrar()
    {
        if(QDate::currentDate().dayOfWeek() == 6) // es sabado
            return QTime(14, 0); // se cierra a las 2pm el sábado
        else
            return QTime(17, 0); // se ciera a las 5pm de lunes a viernes
    }
};

#endif // DEVOLUCION_H

#ifndef ALTACLIENTE_H
#define ALTACLIENTE_H

#include <QDialog>
#include <QtSql>

namespace Ui {
class AltaCliente;
}

class AltaCliente : public QDialog
{
    Q_OBJECT

public:
    AltaCliente(QWidget *parent, const QString &codigoCliente, int tipoVentana,
                const QString &texto, const QString &titulo);
    ~AltaCliente();

    const static int MODIFICAR = 1;
    const static int INSERTAR = 2;

private slots:
    void on_pushButtonAceptar_clicked();

    void on_pushButtonCancelar_clicked();

private:
    Ui::AltaCliente *ui;
    QSqlDatabase db;
    int tipoVentana;
    QString codigoCliente;

    const QString insertar = "INSERT INTO cliente(nombre, telefono, departamento, carrera, grado, sexo, tipo) "\
            "VALUES(?, ?, ?, ?, ?, ?, ?)";

    QString modificar;

    void procesarCliente(const QString &sentencia, const QString &mensajeError);
    void llenarCampos();
    void completarSexo(const QString &sexo);
    void completarTipo(const QString &tipo);

};

#endif // ALTACLIENTE_H

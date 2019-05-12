#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "nuevo_libro.h"
#include "modificar.h"
#include <QtSql>
#include <QTableWidget>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(const QString &codigoEmpleado, const bool esAdministrador, QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_4_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_5_clicked();
    void on_botonCerrarSesion_clicked();
    void on_botonMostrarEmpleados_clicked();
    void on_botonAgregarEmpleado_clicked();

    void mostrarMenuEmpleado();
    void modificarEmpleado();
    void eliminarEmpleado();

    void mostrarMenuCliente();
    void modificarCliente();
    void eliminarCliente();


    void on_botonMostrarClientes_clicked();
    void on_botonAgregarClientes_clicked();
    void on_botonMostrarPrestamos_clicked();

private:

    QString getSeleccionPrestamos();
    QString getSeleccionEmpleados();
    QString getSeleccionClientes();
    bool estaATiempo();
    QTime horaCerrar();
    QTime horaAbrir();
    void consultaLibros(QSqlQuery &query);
    void consultaEmpleados(QSqlQuery &query);
    void consultaClientes(QSqlQuery &query);
    void consultaPrestamos(QSqlQuery &query);
    bool clienteTienePendientes(const QString &codigoCliente);
    void _query(QSqlQuery &query);
    void llenarLista(QStringList &);
    void llenarTabla(QTableWidget *tabla, const QString &datoABuscar,
                                 const QString &seleccion, const uint numColumnas);

    Ui::MainWindow *ui;
    QString codigoEmpleadoActual;
    QSqlDatabase db;


    QString seleccionEmpleados = "SELECT codigo, nombre, edad, salario, sexo, nombre_usuario, contrasenia "\
                                 "FROM (SELECT codigo, nombre, edad, salario, "
                                 "CASE WHEN sexo='H' THEN 'Hombre' "\
                                 "     WHEN sexo='M' THEN 'Mujer' "\
                                 "END AS sexo, nombre_usuario, "\
                                 "PGP_SYM_DECRYPT(contrasenia, 'equipo7') AS contrasenia, es_administrador " \
                                 "FROM empleado) AS temporal WHERE es_administrador=FALSE ";

    QString seleccionClientes = "SELECT codigo, nombre, telefono, departamento, carrera, grado, sexo, tipo "\
                                "FROM (SELECT codigo, nombre, telefono, departamento, carrera, grado, "\
                                    "CASE WHEN sexo='H' THEN 'Hombre' "\
                                        "WHEN sexo='M' THEN 'Mujer' "\
                                    "END AS sexo, "\
                                    "CASE WHEN tipo='E' THEN 'Estudiante' "\
                                        "WHEN tipo='P' THEN 'Profesor' "\
                                        "WHEN tipo='A' THEN 'Ambos' "\
                                    "END AS tipo FROM cliente) AS temporal ";

    QString seleccionPrestamos = "SELECT codigo, titulo, nombre_cliente, nombre_empleado, fecha_prestamo, fecha_entrega, "\
                        "CASE WHEN ejemplar = 1 THEN CONCAT(TRUNC(retraso / 3600), ' horas') "\
                             "WHEN ejemplar <> 1 THEN CONCAT(TRUNC(retraso / 86400), ' días') "\
                        "END AS retraso2, "\
                        "CASE WHEN ejemplar = 1 THEN CONCAT('$', TRUNC(retraso / 3600) * 1) "\
                                 "WHEN ejemplar <> 1 THEN CONCAT('$', TRUNC(retraso / 86400) * 5) "\
                        "END AS penalizacion2 "\

                        "FROM "\

                    "(SELECT prestamo.codigo, titulo, cliente.nombre AS nombre_cliente, empleado.nombre AS nombre_empleado, "\
                            "fecha_prestamo, fecha_entrega, ejemplar, "\
                        "CASE WHEN EXTRACT(EPOCH from now() - fecha_entrega) <= 0 THEN 0 "\
                             "WHEN EXTRACT(EPOCH from now() - fecha_entrega) > 0 THEN EXTRACT(EPOCH from now() - fecha_entrega) "\
                        "END AS retraso "\
                        "FROM prestamo LEFT JOIN libro ON libro.codigo=codigo_libro "\
                        "LEFT JOIN cliente ON cliente.codigo=codigo_cliente "\
                        "LEFT JOIN empleado ON empleado.codigo=codigo_empleado) AS temporal ";
};

#endif // MAINWINDOW_H

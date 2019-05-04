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

    void on_tabWidget_tabBarClicked(int index);

    void on_pushButton_4_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_5_clicked();

    void on_botonCerrarSesion_clicked();

    void on_botonMostrarEmpleados_clicked();

    void on_botonAgregarEmpleado_clicked();

    void mostrarMenuEmpleado();
    void modificarEmpleado();
    void eliminarEmpleado();

private:
    Ui::MainWindow *ui;
    QString codigoEmpleadoActual;
    QSqlDatabase db;

    bool estaATiempo();
    QTime horaCerrar();
    QTime horaAbrir();
    void consultaLibros(QSqlQuery &query);
    void consultaEmpleados(QSqlQuery &query);
    void _query(QSqlQuery &query);
    void llenarLista(QStringList &);
    void llenarTabla(QTableWidget *tabla, const QString &datoABuscar,
                                 const QString &seleccion, const uint numColumnas);
};

#endif // MAINWINDOW_H

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "nuevo_libro.h"
#include "modificar.h"
#include <QtSql>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(const QString &codigoEmpleado, QWidget *parent = 0);
    void mostrarLibros();
    void _query(QSqlQuery &query);
    void llenarLista(QStringList &);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_tabWidget_tabBarClicked(int index);

    void on_pushButton_4_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::MainWindow *ui;
    QString codigoEmpleadoActual;

    bool estaATiempo();
    QTime horaCerrar();
    QTime horaAbrir();
};

#endif // MAINWINDOW_H

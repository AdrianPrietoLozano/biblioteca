#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "nuevo_libro.h"
#include <QtSql>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
    void mostrarLibros();
    void _query(QSqlQuery &query);
    void llenarLista(QStringList &);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_tabWidget_tabBarClicked(int index);

private:
    Ui::MainWindow *ui;
    //alta_libro *ventana;
};

#endif // MAINWINDOW_H

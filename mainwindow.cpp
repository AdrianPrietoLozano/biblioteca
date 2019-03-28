#include "ui_mainwindow.h"
#include "alta_libro.h"
#include "mainwindow.h"
#include <QtSql>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

void MainWindow::mostrarLibros()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QPSQL");
    db.setHostName("localhost");
    db.setDatabaseName("biblioteca");
    db.setUserName("adrian");
    db.setPassword("12345");

    if(db.open())
    {
        QSqlQuery query(db);

        query.exec("SELECT * FROM libro");
        uint numTuplas = query.size();
        uint numColumnas = 7;
        //query.clear();

        ui->tableLibros->setColumnCount(numColumnas);
        ui->tableLibros->setRowCount(numTuplas);
        ui->tableLibros->verticalHeader()->setVisible(false);
        //ui->tableLibros->horizontalHeader()->setDefaultAlignment(Qt::AlignHCenter);

        for(uint i = 0; query.next(); i++)
            for(uint j = 0; j < numColumnas; j++)
                ui->tableLibros->setItem(i, j, new QTableWidgetItem(query.value(j).toString()));

        db.close();
    }
    else
        qDebug() << "Error: no se pudo acceder a la base de datos.";
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    nuevo_libro *ventana = new nuevo_libro(this);
    ventana->exec();
    delete ventana;
}

void MainWindow::on_pushButton_2_clicked()
{
    mostrarLibros();
}

void MainWindow::on_tabWidget_tabBarClicked(int index)
{
    mostrarLibros();
}

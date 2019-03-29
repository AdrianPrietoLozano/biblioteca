#include "ui_mainwindow.h"
#include "mainwindow.h"
#include <QtSql>
#include <QSqlTableModel>

enum {
    CODIGO,
    ISBN,
    TITULO,
    AUTOR,
    EDITORIAL,
    EJEMPLAR,
    ANIO
};

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
        QSqlTableModel *mModel = new QSqlTableModel(this, db);
        mModel->setTable("libro");
        mModel->select();
        mModel->setHeaderData(CODIGO, Qt::Horizontal, tr("Código"));
        mModel->setHeaderData(ISBN, Qt::Horizontal, tr("ISBN"));
        mModel->setHeaderData(TITULO, Qt::Horizontal, tr("Título"));
        mModel->setHeaderData(AUTOR, Qt::Horizontal, tr("Autor"));
        mModel->setHeaderData(EDITORIAL, Qt::Horizontal, tr("Editorial"));
        mModel->setHeaderData(EJEMPLAR, Qt::Horizontal, tr("Ejemplar"));
        mModel->setHeaderData(ANIO, Qt::Horizontal, tr("Año de publicación"));
        ui->tableViewLibros->setModel(mModel);
        ui->tableViewLibros->verticalHeader()->setVisible(false);

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

    mostrarLibros();

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

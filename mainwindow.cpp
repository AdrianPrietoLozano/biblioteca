#include "ui_mainwindow.h"
#include "alta_libro.h"
#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->line_Buscar->setPlaceholderText("Buscar");

    QStringList a;

    llenarLista(a);

    ui->comboBox->addItems(a);

}

void MainWindow::mostrarLibros()
{


    QSqlDatabase db = QSqlDatabase::database("coneccion");

    if(db.open())
    {
        QSqlQuery query(db);

        query.clear();
        if(ui->line_Buscar->text() != "")
        {
            _query(query);
            qDebug() << "Filtro";
        }
        else
            query.exec("SELECT * FROM libro ORDER BY codigo_libro");

        uint numTuplas = query.size();
        uint numColumnas = 7;
        //query.clear();

        ui->tableLibros->clearContents();
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

void MainWindow::_query(QSqlQuery &query)
{
    switch(ui->comboBox->currentIndex())
    {
    case 0://Entero

        query.exec("SELECT * FROM libro WHERE codigo_libro =" + ui->line_Buscar->text() + " ORDER BY codigo_libro");
        break;
    case 1:

        query.exec("SELECT * FROM libro WHERE isbn LIKE '%" + ui->line_Buscar->text() + "%' ORDER BY codigo_libro");
        break;
    case 2:

        query.exec("SELECT * FROM libro WHERE UPPER(titulo) LIKE UPPER('%" + ui->line_Buscar->text() + "%') ORDER BY codigo_libro");
        break;
    case 3:

        query.exec("SELECT * FROM libro WHERE UPPER(autor) LIKE UPPER('%" + ui->line_Buscar->text() + "%') ORDER BY codigo_libro");
        break;
    case 4:

        query.exec("SELECT * FROM libro WHERE UPPER(editorial) LIKE UPPER('%" + ui->line_Buscar->text() + "%') ORDER BY codigo_libro");
        break;
    case 5://Entero

        query.exec("SELECT * FROM libro WHERE anio_publicacion LIKE '%" + ui->line_Buscar->text() + "%' ORDER BY codigo_libro");
        break;
    }
    ui->line_Buscar->clear();
}

void MainWindow::llenarLista(QStringList &a)
{
    a.append("Codigo");
    a.append("ISBN");
    a.append("Titulo");
    a.append("Autor");
    a.append("Editorial");
    a.append("Año");
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

    qDebug() << ui->comboBox->currentText();
}

void MainWindow::on_tabWidget_tabBarClicked(int index)
{
    //mostrarLibros();
}

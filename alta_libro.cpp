#include "alta_libro.h"
#include "ui_alta_libro.h"

alta_libro::alta_libro(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::alta_libro)
{
    ui->setupUi(this);
}

alta_libro::~alta_libro()
{
    delete ui;
}

void alta_libro::on_pushButton_7_clicked()
{
    close();
}

void alta_libro::on_pushButton_6_clicked()
{

    db.setHostName("localhost");
    db.setDatabaseName("biblioteca");
    db.setUserName("adrian");
    db.setPassword("12345");

    QString isbn = ui->lineEdit->text();
    QString titulo = ui->lineEdit_2->text();
    QString autor = ui->lineEdit_3->text();
    QString editorial = ui->lineEdit_4->text();
    QString anio = ui->lineEdit_5->text();

    if(db.open())
    {
        qDebug() << "Entro";
        QSqlQuery query(db);

        query.exec("INSERT INTO libro(isbn, titulo, autor, editorial, ejemplar, anio_publicacion) VALUES ('isbn', 'titulo', 'autor', 'editorial', 'ejemplar', 'anio_publicacion')");
        //query.
        /*
        query.exec("SELECT * FROM libro");
        uint numTuplas = query.size();
        uint numColumnas = nombreColumnas.size();
        //query.clear();

        ui->tableLibros->setColumnCount(numColumnas);
        ui->tableLibros->setRowCount(numTuplas);
        ui->tableLibros->setHorizontalHeaderLabels(nombreColumnas);
        ui->tableLibros->verticalHeader()->setVisible(false);

        for(uint i = 0; query.next(); i++)
            for(uint j = 0; j < numColumnas; j++)
                ui->tableLibros->setItem(i, j, new QTableWidgetItem(query.value(j).toString()));
        */

        db.close();
    }
    else
    {
         qDebug() << "Error: no se pudo acceder a la base de datoss.";
    }



}

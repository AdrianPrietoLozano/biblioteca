#include "nuevo_libro.h"
#include "ui_nuevo_libro.h"
#include <QtSql>
#include <QMessageBox>

nuevo_libro::nuevo_libro(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::nuevo_libro)
{
    ui->setupUi(this);
}

nuevo_libro::~nuevo_libro()
{
    delete ui;
}


void nuevo_libro::on_botonCancelar_clicked()
{
    close();
}

void nuevo_libro::on_botonFinalizar_clicked()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QPSQL");
    db.setHostName("localhost");
    db.setDatabaseName("biblioteca");
    db.setUserName("adrian");
    db.setPassword("12345");

    QString isbn = ui->lineEditIsbn->text();
    QString titulo = ui->lineEditTitulo->text();
    QString autor = ui->lineEditAutor->text();
    QString editorial = ui->lineEditEditorial->text();
    QString ejemplar = ui->lineEditEjemplar->text();
    QString anio = ui->lineEditAnio->text();

    if(db.open())
    {
        QSqlQuery query(db);

        query.prepare("INSERT INTO libro(isbn, titulo, autor, editorial, ejemplar, anio_publicacion)"
                "VALUES (?, ?, ?, ?, ?, ?)");

        //qDebug() << insert;
        query.bindValue(0, isbn);
        query.bindValue(1, titulo);
        query.bindValue(2, autor);
        query.bindValue(3, editorial);
        query.bindValue(4, ejemplar);
        query.bindValue(5, anio);

        if(query.execBatch())
        {
            query.exec();
            db.commit(); // guarda los cambios en la base de datos
        }
        else
        {
            QMessageBox msg;
            msg.setText(query.lastError().text());
            msg.exec();
        }

        db.close();
    }
    else
        qDebug() << "Error: no se pudo acceder a la base de datos.";

    close();
}

#include "nuevo_libro.h"
#include "ui_nuevo_libro.h"
#include "mainwindow.h"
#include <QMessageBox>

nuevo_libro::nuevo_libro(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::nuevo_libro)
{
    ui->setupUi(this);
    db = QSqlDatabase::database("coneccion");
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
    if(db.open())
    {
        if(verificarCampos())
        {
            QSqlQuery query(db);

            QString select = "SELECT * FROM libro WHERE isbn=? AND ejemplar=?";
            query.prepare(select);
            query.bindValue(0, ui->lineEditIsbn->text());
            query.bindValue(1, ui->spinBoxEjemplar->value());
            query.exec();

            if(query.next()) // si ya existe el libro
                QMessageBox::critical(this, "Error", "Error: el libro ya existe");
            else
                if(insertarLibro())
                    close();
                else
                    QMessageBox::critical(this, "Error", "Ocurrio un error al insertar el libro");
        }
        else
            QMessageBox::critical(this, "Campos vacíos", "Los campos ISBN, título y ejemplar son obligatorios");
    }
    else
        qDebug() << "Error: no se pudo acceder a la base de datos.";
}

bool nuevo_libro::insertarLibro()
{
    if(db.open())
    {
        QSqlQuery query(db);

        QString insert = "INSERT INTO libro(isbn, titulo, autor, editorial, ejemplar, anio_publicacion)"
                "VALUES (?, ?, ?, ?, ?, ?)";

        query.prepare(insert);
        query.bindValue(0, ui->lineEditIsbn->text());
        query.bindValue(1, ui->lineEditTitulo->text());
        query.bindValue(2, ui->lineEditAutor->text());
        query.bindValue(3, ui->lineEditEditorial->text());
        query.bindValue(4, ui->spinBoxEjemplar->value());
        query.bindValue(5, ui->spinBoxAnio->value());

        if(query.exec())
        {
            db.commit(); // guarda los cambios en la base de datos
            return true;
        }
    }

    return false;
}

bool nuevo_libro::verificarCampos()
{
    if(ui->lineEditIsbn->text() == "" ||
            ui->lineEditTitulo->text() == "")
        return false;

   return true;

}

#include "modificar.h"
#include "ui_modificar.h"

Modificar::Modificar(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Modificar)
{
    ui->setupUi(this);

//    QStringList a;

//    llenarLista(a);

    QPixmap image(":/imagenes/banner_biblioteca.jpg"), est(":/imagenes/estante3.jpg");
    int w = ui->banner->width(), h = ui->banner->height(), w1 = ui->estante->width(), h1 = ui->estante->height();
    ui->banner->setPixmap(image.scaled(w, h, Qt::KeepAspectRatio));
    ui->estante->setPixmap(est.scaled(w1, h1, Qt::KeepAspectRatio));
}

void Modificar::llenarTabla()
{
    QSqlDatabase db = QSqlDatabase::database("coneccion");

    QString _query = "SELECT * FROM LIBRO ORDER BY codigo";

    QSqlQuery query(db);

    query.exec(_query);

    uint numTuplas = query.size();
    tabla->clearContents();
    tabla->setColumnCount(7);
    tabla->setRowCount(numTuplas);
    //tabla->verticalHeader->setVisible(false);

    for(uint i = 0; query.next(); i++)
        for(uint j = 0; j < 7; j++)
            tabla->setItem(i, j, new QTableWidgetItem(query.value(j).toString()));
}

Modificar::~Modificar()
{
    delete ui;
}

//void Modificar::on_button_Mod_clicked()
//{

//    QSqlDatabase db = QSqlDatabase::database("coneccion");

//    QSqlQuery query(db);

//    if(db.open())
//    {
//        query.exec("SELECT * FROM libro ORDER BY codigo");

//        QListWidgetItem *item;

//        while(query.next())
//        {
//            item = new QListWidgetItem(QIcon(":/imagenes/libroBibliotecaSF.png"), query.value(2).toString());

//        }
//    }
//}

void Modificar::on_list_Mod_itemDoubleClicked(QListWidgetItem *item)
{
    QSqlDatabase db = QSqlDatabase::database("coneccion");

    if(db.open())
    {
        QSqlQuery query(db);

        query.exec("SELECT * FROM libro WHERE UPPER (titulo) like UPPER('%" + item->text() + "%') ORDER BY codigo");
        query.next();

        ui->line_Cod->setText(query.value(0).toString());
        ui->line_isbn->setText(query.value(1).toString());
        ui->line_Titulo->setText(query.value(2).toString());
        ui->line_Autor->setText(query.value(3).toString());
        ui->line_Edit->setText(query.value(4).toString());
        ui->line_Eje->setText(query.value(5).toString());
        ui->line_Anio->setText(query.value(6).toString());
    }
}

//void Modificar::on_pushButton_clicked()
//{
//    ui->line_Eje->setText(QString::number(ui->line_Eje->text().toInt() - 1));
//}

//void Modificar::on_pushButton_2_clicked()
//{
//    ui->line_Eje->setText(QString::number(ui->line_Eje->text().toInt() + 1));
//}

void Modificar::on_pushButton_3_clicked()
{
    if(ejemplar != ui->line_Eje->text())
    {
        QSqlDatabase db = QSqlDatabase::database("coneccion");

        QSqlQuery temp(db);

        temp.exec("SELECT * FROM libro WHERE isbn = '" + ui->line_isbn->text() +
                  "' AND ejemplar = " + ui->line_Eje->text());

        temp.next();

        if(!temp.isValid())
        {
            actualizar();
        }
        else
        {
            QMessageBox::critical(this, "Error", "Ya existe ese ejemplar.",
                                  QMessageBox::Ok);
        }
    }
    else
    {
        actualizar();
    }
}

void Modificar::setTabla(QTableWidget *value)
{
    tabla = value;
}

void Modificar::actualizar()
{
    if(ui->line_Titulo->text() == "" || ui->line_Eje->text() == "" ||
            ui->line_isbn->text() == "")
    {
        QMessageBox::critical(this, "Campos vacíos", "Los campos ISBN, título y ejemplar son obligatorios");
    }
    else
    {
        QSqlDatabase db = QSqlDatabase::database("coneccion");

        QSqlQuery query(db);

        query.exec("UPDATE libro SET isbn = '" + ui->line_isbn->text() + "', " +
                   "titulo = '" + ui->line_Titulo->text() + "', " +
                   "autor = '" + ui->line_Autor->text() + "', " +
                   "editorial = '" + ui->line_Edit->text() + "', " +
                   "ejemplar = " + ui->line_Eje->text() + ", " +
                   "anio_publicacion = " + ui->line_Anio->text() + " " +
                   "WHERE codigo = " + ui->line_Cod->text());

        llenarTabla();
        this->close();
    }
}

void Modificar::setCodigoLibro(const QString &value)
{
    codigoLibro = value;
}

Modificar::llenarInterfaz()
{
    QSqlDatabase db = QSqlDatabase::database("coneccion");

    QSqlQuery query(db);

    query.exec("SELECT * FROM libro WHERE codigo = " + codigoLibro);

    query.next();

    ejemplar = query.value(5).toString();

    ui->line_Cod->setText(query.value(0).toString());
    ui->line_isbn->setText(query.value(1).toString());
    ui->line_Titulo->setText(query.value(2).toString());
    ui->line_Autor->setText(query.value(3).toString());
    ui->line_Edit->setText(query.value(4).toString());
    ui->line_Eje->setText(query.value(5).toString());
    ui->line_Anio->setText(query.value(6).toString());
}

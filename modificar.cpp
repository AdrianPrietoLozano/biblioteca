#include "modificar.h"
#include "ui_modificar.h"

Modificar::Modificar(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Modificar)
{
    ui->setupUi(this);

    QStringList a;

    llenarLista(a);

    ui->combo_Mod->addItems(a);

    QPixmap image(":/imagenes/banner_biblioteca.jpg"), est(":/imagenes/estante_libros.jpg");
    int w = ui->banner->width(), h = ui->banner->height(), w1 = ui->estante->width(), h1 = ui->estante->height();
    ui->banner->setPixmap(image.scaled(w, h, Qt::KeepAspectRatio));
    ui->estante->setPixmap(est.scaled(w1, h1, Qt::KeepAspectRatio));
}

void Modificar::llenarLista(QStringList &a)
{
    a.append("Código");
    a.append("ISBN");
    a.append("Titulo");
    a.append("Autor");
    a.append("Editorial");
    a.append("Año");
}

Modificar::~Modificar()
{
    delete ui;
}

void Modificar::on_button_Mod_clicked()
{
    ui->list_Mod->clear();

    QSqlDatabase db = QSqlDatabase::database("coneccion");

    QSqlQuery query(db);

    if(db.open())
    {
        query.exec("SELECT * FROM libro ORDER BY codigo");

        QListWidgetItem *item;

        while(query.next())
        {
            item = new QListWidgetItem(QIcon(":/imagenes/libroBibliotecaSF.png"), query.value(2).toString());

            ui->list_Mod->addItem(item);
        }
    }
}

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

void Modificar::on_pushButton_clicked()
{
    ui->line_Eje->setText(QString::number(ui->line_Eje->text().toInt() - 1));
}

void Modificar::on_pushButton_2_clicked()
{
    ui->line_Eje->setText(QString::number(ui->line_Eje->text().toInt() + 1));
}

void Modificar::on_pushButton_3_clicked()
{
    QSqlDatabase db = QSqlDatabase::database("coneccion");

    if(db.open())
    {
        QSqlQuery query(db);

        query.exec("UPDATE libro SET isbn = '" + ui->line_isbn->text() + "', " +
                   "titulo = '" + ui->line_Titulo->text() + "', " +
                   "autor = '" + ui->line_Autor->text() + "', " +
                   "editorial = '" + ui->line_Edit->text() + "', " +
                   "ejemplar = " + ui->line_Eje->text() + ", " +
                   "anio_publicacion = " + ui->line_Anio->text() + " " +
                   "WHERE codigo = " + ui->line_Cod->text());
    }
}

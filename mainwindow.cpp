#include "ui_mainwindow.h"
#include "alta_libro.h"
#include "mainwindow.h"
#include "prestamo.h"
#include <QMessageBox>

MainWindow::MainWindow(const QString &codigoEmpleado, QWidget *parent) :
    codigoEmpleadoActual(codigoEmpleado),
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->line_Buscar->setPlaceholderText("Buscar");

    QStringList a;

    llenarLista(a);

    ui->comboBox->addItems(a);

    qDebug() << "Empleado actual = " << codigoEmpleadoActual;

//    ui->tableLibros->setDisabled(true);
//    ui->tableLibros->horizontalHeader()->setStretchLastSection(true);
}

void MainWindow::mostrarLibros()
{
    QSqlDatabase db = QSqlDatabase::database("coneccion");

    if(db.open())
    {
        QSqlQuery query(db);

        query.clear();
        ui->tableLibros->clearContents();
        if(ui->line_Buscar->text() != "")
        {
            qDebug() << "Filtro" + ui->line_Buscar->text();
            _query(query);
        }
        else
            query.exec("SELECT * FROM libro ORDER BY codigo");

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

void MainWindow::_query(QSqlQuery &query)
{
    switch(ui->comboBox->currentIndex())
    {
    case 0://Entero

        query.exec("SELECT * FROM libro WHERE cast(codigo as varchar) like '%" + ui->line_Buscar->text() + "%' ORDER BY codigo");
        break;
    case 1:

        query.exec("SELECT * FROM libro WHERE isbn like '%" + ui->line_Buscar->text() + "%' ORDER BY codigo");
        break;
    case 2:

        query.exec("SELECT * FROM libro WHERE UPPER (titulo) like UPPER('%" + ui->line_Buscar->text() + "%') ORDER BY codigo");
        break;
    case 3:

        query.exec("SELECT * FROM libro WHERE UPPER (autor) like UPPER ('%" + ui->line_Buscar->text() + "%') ORDER BY codigo");
        break;
    case 4:

        query.exec("SELECT * FROM libro WHERE UPPER (editorial) like UPPER ('%" + ui->line_Buscar->text() + "%') ORDER BY codigo");
        break;
    case 5://Entero

        query.exec("SELECT * FROM libro WHERE cast(anio_publicacion as varchar) like '%" + ui->line_Buscar->text() + "%' ORDER BY codigo");
        break;
    }
    ui->line_Buscar->clear();
}

void MainWindow::llenarLista(QStringList &a)
{
    a.append("Código");
    a.append("ISBN");
    a.append("Título");
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
    mostrarLibros();
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

void MainWindow::on_pushButton_4_clicked()
{
    Modificar *mod = new Modificar(this);
    mod->exec();
    delete mod;
}

void MainWindow::on_pushButton_3_clicked()
{
    if(estaATiempo())
    {
        Prestamo *prestamo = new Prestamo(this, codigoEmpleadoActual);
        prestamo->exec();

        delete prestamo;
    }
    else
    {
        QMessageBox msg(this);
        msg.setText("Fuera de tiempo para realizar préstamos.");
        msg.setWindowTitle("Fuera de tiempo");
        msg.exec();
    }
}

bool MainWindow::estaATiempo()
{
    int diaActual = QDate::currentDate().dayOfWeek();
    QTime horaActual = QTime::currentTime();

    if(diaActual >= 1 && diaActual <= 6) // dia actual entre lunes-sabado
        if(horaActual >= horaAbrir() && horaActual <= horaCerrar())
            return true;
    return false;
}

QTime MainWindow::horaCerrar()
{
    int diaActual = QDate::currentDate().dayOfWeek();

    if(diaActual >= 1 && diaActual <= 5) // lun-viernes
        return QTime(17, 0); // lun-viernes cierra a las 5pm

    if(diaActual == 6)
        return QTime(14, 0); // sábado cierra a las 2pm

    QTime(0, 0); // domingo no abre
}

QTime MainWindow::horaAbrir()
{
    return QTime(8, 0); // todos los días habre a las 8am
}

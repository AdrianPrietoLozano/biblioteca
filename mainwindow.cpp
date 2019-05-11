#include "ui_mainwindow.h"
#include "alta_libro.h"
#include "mainwindow.h"
#include "prestamo.h"
#include "devolucion.h"
#include "dialog.h"
#include "altaempleado.h"
#include "modificarempleado.h"
#include "altacliente.h"
#include <QMessageBox>

#define NUM_COLUMNAS_LIBRO 7
#define NUM_COLUMNAS_EMPLEADO 7
#define NUM_COLUMNAS_CLIENTE 8

MainWindow::MainWindow(const QString &codigoEmpleado, const bool esAdministrador, QWidget *parent) :
    codigoEmpleadoActual(codigoEmpleado),
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    db = QSqlDatabase::database("coneccion");

    ui->line_Buscar->setPlaceholderText("Buscar");

    if(esAdministrador)
        ui->tabEmpleados->setEnabled(true);
    else
        ui->tabEmpleados->setEnabled(false);

    QStringList a;
    llenarLista(a);
    ui->comboBox->addItems(a);

    QStringList listaEmpleados = {"Código", "Nombre", "Edad", "Salario", "Sexo", "Nombre de usuario"};
    ui->comboBoxEmpleados->addItems(listaEmpleados);

    QStringList listaClientes = {"Código", "Nombre", "Teléfono", "Departamento", "Carrera",
                                 "Grado", "Sexo", "Tipo"};
    ui->comboBoxClientes->addItems(listaClientes);

    connect(ui->tableEmpleados, SIGNAL(cellPressed(int,int)),
            this, SLOT(mostrarMenuEmpleado()));

    connect(ui->tableClientes, SIGNAL(cellPressed(int,int)),
            this, SLOT(mostrarMenuCliente()));
}

void MainWindow::llenarTabla(QTableWidget *tabla, const QString &datoABuscar,
                             const QString &seleccion, const uint numColumnas)
{
    if(db.open())
    {
        QSqlQuery query(db);

        if(datoABuscar != "")
            _query(query);
        else
            query.exec(seleccion);

        uint numTuplas = query.size();
        tabla->setColumnCount(numColumnas);
        tabla->setRowCount(numTuplas);
        tabla->verticalHeader()->setVisible(false);

        for(uint i = 0; query.next(); i++)
            for(uint j = 0; j < numColumnas; j++)
                tabla->setItem(i, j, new QTableWidgetItem(query.value(j).toString()));
        db.close();
    }
    else
        qDebug() << "Error: no se pudo acceder a la base de datos.";
}

void MainWindow::_query(QSqlQuery &query)
{
    switch(ui->tabWidget->currentIndex())
    {
        case 1:
            consultaLibros(query);
            break;

        case 2:
            consultaClientes(query);
            break;

        case 3:
            consultaEmpleados(query);
            break;
    }
}

void MainWindow::consultaLibros(QSqlQuery &query)
{
    QString datoABuscar = ui->line_Buscar->text();

    switch(ui->comboBox->currentIndex())
    {
    case 0:
        query.exec("SELECT * FROM libro WHERE cast(codigo as varchar) like '%" + datoABuscar + "%' ORDER BY codigo");
        break;

    case 1:
        query.exec("SELECT * FROM libro WHERE isbn like '%" + datoABuscar + "%' ORDER BY codigo");
        break;

    case 2:
        query.exec("SELECT * FROM libro WHERE UPPER (titulo) like UPPER('%" + datoABuscar + "%') ORDER BY codigo");
        break;

    case 3:
        query.exec("SELECT * FROM libro WHERE UPPER (autor) like UPPER ('%" + datoABuscar + "%') ORDER BY codigo");
        break;

    case 4:
        query.exec("SELECT * FROM libro WHERE UPPER (editorial) like UPPER ('%" + datoABuscar + "%') ORDER BY codigo");
        break;

    case 5:
        query.exec("SELECT * FROM libro WHERE cast(anio_publicacion as varchar) like '%" + datoABuscar + "%' ORDER BY codigo");
        break;
    }
    ui->line_Buscar->clear();
}

void MainWindow::consultaEmpleados(QSqlQuery &query)
{
    QString seleccion = "SELECT codigo, nombre, edad, salario, "\
                        "CASE WHEN sexo='H' THEN 'Hombre' "\
                        "     WHEN sexo='M' THEN 'Mujer' "\
                        "END AS sexo, "\
                        "nombre_usuario, PGP_SYM_DECRYPT(contrasenia, 'equipo7') " \
                        "FROM empleado WHERE es_administrador=FALSE AND ";

    QString datoABuscar = ui->lineBuscarEmpleado->text();
    QString complemento;

    switch(ui->comboBoxEmpleados->currentIndex())
    {
        case 0:
            complemento = "CAST(codigo as varchar)='" + datoABuscar +"'";
            break;

        case 1:
            complemento = "UPPER(nombre) LIKE UPPER('%" + datoABuscar + "%') ";
            break;

        case 2:
            complemento = "CAST(edad as varchar)='" + datoABuscar + "'";
            break;

        case 3:
            complemento = "CAST(salario as varchar)='" + datoABuscar + "'";
            break;

        case 4:
            complemento = "UPPER(sexo) LIKE UPPER('%" + datoABuscar + "%') ";
            break;

        case 5:
            complemento = "UPPER(nombre_usuario) LIKE UPPER('%" + datoABuscar + "%') " ;
            break;
    }

    seleccion += complemento + " ORDER BY codigo";
    query.exec(seleccion);
    ui->lineBuscarEmpleado->clear();
}

void MainWindow::consultaClientes(QSqlQuery &query)
{
    QString seleccion = "SELECT codigo, nombre, telefono, departamento, carrera, grado, "\
                        "CASE WHEN sexo='H' THEN 'Hombre' "\
                        "     WHEN sexo='M' THEN 'Mujer' "\
                        "END AS sexo, "\
                        "CASE WHEN tipo='E' THEN 'Estudiante' "\
                        "     WHEN tipo='P' THEN 'Profesor' "\
                        "     WHEN tipo='A' THEN 'Estudiante y profesor' "\
                        "END AS tipo "\
                        "FROM cliente ";

    QString datoABuscar = ui->lineBuscarClientes->text();
    QString complemento;

    switch(ui->comboBoxClientes->currentIndex())
    {
        case 0: // código
            complemento = "WHERE CAST(codigo as varchar)='" + datoABuscar + "'";
            break;

        case 1: // nombre
            complemento = "WHERE UPPER(nombre) LIKE UPPER('%" + datoABuscar + "%') ";
            break;

        case 2: // teléfono
            complemento = "WHERE UPPER(telefono) LIKE UPPER('%" + datoABuscar + "%') ";
            break;

        case 3: // departamento
            complemento = "WHERE UPPER(departamento) LIKE UPPER('%" + datoABuscar + "%') ";
            break;
        case 4: // carrera
            complemento = "WHERE UPPER(carrera) LIKE UPPER('%" + datoABuscar + "%') ";
            break;

        case 5: // grado
            complemento = "WHERE CAST(grado as varchar)='" + datoABuscar + "'";
            break;

        case 6: // sexo
            complemento = "WHERE sexo='" + datoABuscar + "'";
            break;

        case 7: // tipo
            complemento = "WHERE tipo='" + datoABuscar + "'";
            break;
    }

    seleccion += complemento + " ORDER BY codigo";
    query.exec(seleccion);
    ui->lineBuscarClientes->clear();
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
    delete ventana;

    on_pushButton_2_clicked();
}

void MainWindow::on_pushButton_2_clicked()
{
    QString query = "SELECT * FROM LIBRO ORDER BY codigo";

    llenarTabla(ui->tableLibros, ui->line_Buscar->text(), query, NUM_COLUMNAS_LIBRO);

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
    //estaATiempo()
    if(true)
    {
        Prestamo *prestamo = new Prestamo(this, codigoEmpleadoActual);
        prestamo->exec();

        delete prestamo;
    }
    else
        QMessageBox::information(this, "Fuera de tiempo", "Fuera de tiempo para realizar préstamos");
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

    return QTime(0, 0); // domingo no abre
}

QTime MainWindow::horaAbrir()
{
    return QTime(8, 0); // todos los días habre a las 8am
}

void MainWindow::on_pushButton_5_clicked()
{
    //estaATiempo()
    if(true)
    {
        Devolucion *devolucion = new Devolucion(this);
        devolucion->exec();

        delete devolucion;
    }
    else
        QMessageBox::information(this, "Fuera de tiempo", "Fuera de tiempo para devoluciones");
}

void MainWindow::on_botonCerrarSesion_clicked()
{
    this->close();

    Dialog *ventanInicioSesion = new Dialog();
    ventanInicioSesion->show();
}

void MainWindow::on_botonMostrarEmpleados_clicked()
{
    QString query = "SELECT codigo, nombre, edad, salario, "\
                    "CASE WHEN sexo='H' THEN 'Hombre'"\
                    "     WHEN sexo='M' THEN 'Mujer'"\
                    "END AS sexo, "\
                    "nombre_usuario, PGP_SYM_DECRYPT(contrasenia, 'equipo7')" \
                    "FROM empleado WHERE es_administrador=FALSE ORDER BY codigo";

    llenarTabla(ui->tableEmpleados, ui->lineBuscarEmpleado->text(), query, NUM_COLUMNAS_EMPLEADO);
}

void MainWindow::on_botonAgregarEmpleado_clicked()
{
    AltaEmpleado *ventana = new AltaEmpleado(this);
    ventana->exec();
    delete ventana;

    on_botonMostrarEmpleados_clicked();
}

void MainWindow::modificarEmpleado()
{
    QString codigoEmpleado = ui->tableEmpleados->item(ui->tableEmpleados->currentRow(), 0)->text();

    ModificarEmpleado *ventana = new ModificarEmpleado(codigoEmpleado, this);
    ventana->exec();
    delete ventana;

    on_botonMostrarEmpleados_clicked();
}

void MainWindow::eliminarEmpleado()
{
    QString codigoEmpleado = ui->tableEmpleados->item(ui->tableEmpleados->currentRow(), 0)->text();
    QString nombreEmpleado = ui->tableEmpleados->item(ui->tableEmpleados->currentRow(), 1)->text();

    if(codigoEmpleado == codigoEmpleadoActual)
        QMessageBox::critical(this, "Error", "El empleado actual esta activo");

    else
    {
        int ret = QMessageBox::question(this, "Eliminar empleado",
                                        "¿Seguro que desea eliminar al empleado " + nombreEmpleado + "?",
                                        QMessageBox::Ok | QMessageBox::Cancel, QMessageBox::Cancel);

        if(ret == QMessageBox::Ok)
        {
            if(db.open())
            {
                QSqlQuery query(db);
                QString eliminar = "DELETE FROM empleado WHERE codigo=" + codigoEmpleado;
                if(query.exec(eliminar))
                {
                    db.commit();
                    on_botonMostrarEmpleados_clicked();
                }
                else
                    QMessageBox::critical(this, "Error", "No se pudo eliminar el empleado");
            }
        }
    }
}

bool MainWindow::clienteTienePendientes(const QString &codigoCliente)
{
    if(db.open())
    {
        QSqlQuery query(db);

        QString select = "SELECT * FROM prestamo WHERE codigo_cliente=" + codigoCliente;
        qDebug() << select;
        query.exec(select);
        qDebug() << query.lastError();

        return query.next();
    }
    return true;
}

void MainWindow::eliminarCliente()
{
    QString codigoCliente = ui->tableClientes->item(ui->tableClientes->currentRow(), 0)->text();
    QString nombreCliente = ui->tableClientes->item(ui->tableClientes->currentRow(), 1)->text();

    if(clienteTienePendientes(codigoCliente))
    {
        QMessageBox::critical(this, "Error", "El cliente no se puede eliminar porque tiene libros prestados");
    }
    else
    {
        int ret = QMessageBox::question(this, "Eliminar cliente",
                                        "¿Seguro que desea eliminar al cliente "+ nombreCliente +"?",
                                        QMessageBox::Ok | QMessageBox::Cancel, QMessageBox::Cancel);
        if(ret == QMessageBox::Ok)
        {
            QSqlQuery query(db);
            QString eliminar = "DELETE FROM cliente WHERE codigo=" + codigoCliente;

            if(query.exec(eliminar))
            {
                db.commit();
                on_botonMostrarClientes_clicked();
            }
            else
                QMessageBox::critical(this, "Error", "El cliente no se pudo eliminar");
        }
    }
}



void MainWindow::mostrarMenuEmpleado()
{
    ui->tableEmpleados->selectRow(ui->tableEmpleados->currentRow());

    QMenu opciones(tr("Opciones"));

    QAction editar(QIcon(":/imagenes/editar.png"), "Modificar", this);
    QAction eliminar(QIcon(":/imagenes/eliminar.png"), "Eliminar", this);

    connect(&editar, SIGNAL(triggered(bool)), this, SLOT(modificarEmpleado()));
    connect(&eliminar, SIGNAL(triggered(bool)), this, SLOT(eliminarEmpleado()));

    opciones.addAction(&editar);
    opciones.addAction(&eliminar);

    opciones.exec(QCursor::pos());
}

void MainWindow::mostrarMenuCliente()
{
    ui->tableClientes->selectRow(ui->tableClientes->currentRow());

    QMenu opciones(tr("Opciones"));

    QAction editar(QIcon(":/imagenes/editar.png"), "Modificar", this);
    QAction eliminar(QIcon(":/imagenes/eliminar.png"), "Eliminar", this);

    connect(&editar, SIGNAL(triggered(bool)), this, SLOT(modificarCliente()));
    connect(&eliminar, SIGNAL(triggered(bool)), this, SLOT(eliminarCliente()));

    opciones.addAction(&editar);
    opciones.addAction(&eliminar);

    opciones.exec(QCursor::pos());
}


void MainWindow::on_botonMostrarClientes_clicked()
{
    QString query = "SELECT codigo, nombre, telefono, departamento, carrera, grado, "\
                    "CASE WHEN sexo='H' THEN 'Hombre' "\
                    "     WHEN sexo='M' THEN 'Mujer' "\
                    "END AS sexo, "\
                    "CASE WHEN tipo='E' THEN 'Estudiante' "\
                    "     WHEN tipo='P' THEN 'Profesor' "\
                    "     WHEN tipo='A' THEN 'Estudiante y profesor' "\
                    "END AS tipo "\
                    "FROM cliente ORDER BY codigo";

    llenarTabla(ui->tableClientes, ui->lineBuscarClientes->text(), query, NUM_COLUMNAS_CLIENTE);
}

void MainWindow::on_botonAgregarClientes_clicked()
{
    QString codigoCliente = ui->tableClientes->item(ui->tableClientes->currentRow(), 0)->text();

    AltaCliente *ventana = new AltaCliente(this, codigoCliente, AltaCliente::INSERTAR,
                                           "Agregar cliente", "Agregar cliente");
    ventana->exec();
    delete ventana;

    on_botonMostrarClientes_clicked();
}

void MainWindow::modificarCliente()
{
    QString codigoCliente = ui->tableClientes->item(ui->tableClientes->currentRow(), 0)->text();

    AltaCliente *ventanaModificar = new AltaCliente(this, codigoCliente, AltaCliente::MODIFICAR,
                                                    "Modificar cliente", "Modificar cliente");
    ventanaModificar->exec();
    delete ventanaModificar;

    on_botonMostrarClientes_clicked();
}

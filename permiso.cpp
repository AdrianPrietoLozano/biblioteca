#include "permiso.h"
#include "ui_permiso.h"

permiso::permiso(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::permiso)
{
    ui->setupUi(this);
}

permiso::~permiso()
{
    delete ui;
}

void permiso::on_buttonBox_accepted()
{
    bool bandera = false;

    QString usuario = ui -> line_admin -> text();
    QString contrasenia = ui -> line_pass -> text();

    QSqlDatabase db = QSqlDatabase::addDatabase("QPSQL");
    db.setHostName("localhost");
    db.setDatabaseName("biblioteca");
    db.setUserName("adrian");
    db.setPassword("12345");

    if(db.open())
    {
        QSqlQuery query(db);

        query.exec("SELECT * FROM usuarios");

        for(unsigned i = 0; query.next(); i++)
        {
            if(usuario == query.value(0) && contrasenia == query.value(1))
            {
                QString admin = QVariant(query.value(2)).toString();
                if(query.value(2).toBool())
                    bandera = true;
            }
        }

        if(bandera)
        {
            close();
            reg = new registro();

            reg->show();
        }
        else
        {
            QMessageBox msg;
            msg.setText( "Usuario o contraseña incorrectos" );
            msg.exec();
        }
    }
}

void permiso::on_buttonBox_rejected()
{
    close();
}

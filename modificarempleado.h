#ifndef MODIFICAREMPLEADO_H
#define MODIFICAREMPLEADO_H

#include <QDialog>
#include <QtSql>

namespace Ui {
class ModificarEmpleado;
}

class ModificarEmpleado : public QDialog
{
    Q_OBJECT

public:
    ModificarEmpleado(const QString &codigoEmpleado, QWidget *parent = 0);
    ~ModificarEmpleado();

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::ModificarEmpleado *ui;
    QSqlDatabase db;

    void llenarCampos(const QString &codigoEmpleado);
    bool existeEmpleado();
};

#endif // MODIFICAREMPLEADO_H

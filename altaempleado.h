#ifndef ALTAEMPLEADO_H
#define ALTAEMPLEADO_H

#include <QDialog>
#include <QtSql>

namespace Ui {
class AltaEmpleado;
}

class AltaEmpleado : public QDialog
{
    Q_OBJECT

public:
    explicit AltaEmpleado(QWidget *parent = 0);
    ~AltaEmpleado();

private slots:
    void on_pushButtonAceptar_clicked();

    void on_pushButtonCancelar_clicked();

private:
    Ui::AltaEmpleado *ui;
    QSqlDatabase db;

    bool insertarEmpleado();
    bool verificarCampos();
};

#endif // ALTAEMPLEADO_H

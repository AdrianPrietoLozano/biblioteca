#ifndef PERMISO_H
#define PERMISO_H

#include <QDialog>
#include "registro.h"
#include <QtSql>
#include <QString>
#include <QMessageBox>

namespace Ui {
class permiso;
}

class permiso : public QDialog
{
    Q_OBJECT

public:
    explicit permiso(QWidget *parent = 0);
    ~permiso();

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::permiso *ui;
    registro *reg;
};

#endif // PERMISO_H

#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include "mainwindow.h"
#include "permiso.h"

#include <QString>
#include <QMessageBox>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

private slots:
    void on_pushButtonAceptar_clicked();
    void on_pushButtonCancelar_clicked();

private:
    Ui::Dialog *ui;
    MainWindow *principal;
    permiso *p;
};

#endif // DIALOG_H

#ifndef MODIFICAR_H
#define MODIFICAR_H

#include <QDialog>
#include <QtSql>
#include <QListWidgetItem>
#include <QPixmap>
#include <QTableWidget>
#include <QMessageBox>

namespace Ui {
class Modificar;
}

class Modificar : public QDialog
{
    Q_OBJECT

public:
    explicit Modificar(QWidget *parent = 0);
    void llenarTabla();
    ~Modificar();

    void setCodigoLibro(const QString &value);

    llenarInterfaz();

    void setTabla(QTableWidget *value);

    void actualizar();

private slots:
    //    void on_button_Mod_clicked();

    void on_list_Mod_itemDoubleClicked(QListWidgetItem *item);

//    void on_pushButton_clicked();

//    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::Modificar *ui;
    QString codigoLibro, ejemplar;
    QTableWidget *tabla;
};

#endif // MODIFICAR_H

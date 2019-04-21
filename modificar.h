#ifndef MODIFICAR_H
#define MODIFICAR_H

#include <QDialog>
#include <QtSql>
#include <QListWidgetItem>
#include <QPixmap>

namespace Ui {
class Modificar;
}

class Modificar : public QDialog
{
    Q_OBJECT

public:
    explicit Modificar(QWidget *parent = 0);
    void llenarLista(QStringList &);
    ~Modificar();

private slots:
    void on_button_Mod_clicked();

    void on_list_Mod_itemDoubleClicked(QListWidgetItem *item);

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::Modificar *ui;
};

#endif // MODIFICAR_H

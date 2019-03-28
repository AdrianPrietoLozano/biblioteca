#ifndef NUEVO_LIBRO_H
#define NUEVO_LIBRO_H

#include <QDialog>

namespace Ui {
class nuevo_libro;
}

class nuevo_libro : public QDialog
{
    Q_OBJECT

public:
    explicit nuevo_libro(QWidget *parent = 0);
    ~nuevo_libro();

private slots:

    void on_botonCancelar_clicked();

    void on_botonFinalizar_clicked();

private:
    Ui::nuevo_libro *ui;
};

#endif // NUEVO_LIBRO_H

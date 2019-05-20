#ifndef INFODEVOLUCION_H
#define INFODEVOLUCION_H

#include <QDialog>

namespace Ui {
class InfoDevolucion;
}

class InfoDevolucion : public QDialog
{
    Q_OBJECT

public:
    InfoDevolucion(QWidget *parent, const QString &titulo, const QString &nombre,
                   const QDateTime fecha_entrega, const QString &retraso,
                   const float penalizacion, const QString &nombreRecibo);
    ~InfoDevolucion();

private slots:
    void on_pushButton_clicked();

    void on_botonVerRecibo_clicked();

private:
    Ui::InfoDevolucion *ui;
    QString nombreRecibo;
};

#endif // INFODEVOLUCION_H

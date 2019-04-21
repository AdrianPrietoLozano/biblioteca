#ifndef INFOPRESTAMO_H
#define INFOPRESTAMO_H

#include <QDialog>

namespace Ui {
class InfoPrestamo;
}

class InfoPrestamo : public QDialog
{
    Q_OBJECT

public:
    explicit InfoPrestamo(QWidget *parent, const QString &fechaPrestamo,
                          const QString &fechaEntrega);
    ~InfoPrestamo();

private slots:
    void on_pushButtonAceptar_clicked();

private:
    Ui::InfoPrestamo *ui;
};

#endif // INFOPRESTAMO_H

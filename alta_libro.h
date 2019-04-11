#ifndef ALTA_LIBRO_H
#define ALTA_LIBRO_H

#include <QWidget>
#include <QtSql>

namespace Ui {
class alta_libro;
}

class alta_libro : public QWidget
{
    Q_OBJECT

public:
    explicit alta_libro(QWidget *parent = 0);
    ~alta_libro();

private slots:
    void on_pushButton_7_clicked();

    void on_pushButton_6_clicked();

private:
    Ui::alta_libro *ui;
    QSqlDatabase db = QSqlDatabase::addDatabase("QPSQL");
};

#endif // ALTA_LIBRO_H

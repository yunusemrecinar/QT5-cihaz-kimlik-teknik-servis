#ifndef SERVISDIALOG_H
#define SERVISDIALOG_H

#include <QDialog>
#include <QSqlDatabase>
#include "notekledialog.h"

namespace Ui {
class ServisDialog;
}

class ServisDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ServisDialog(QWidget *parent = nullptr);
    ~ServisDialog();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::ServisDialog *ui;

    QSqlDatabase database;

    QString malzemeler = "";
    QString servisNo;
    QString UIDno;
    QString gelisTarihi;
    QString musteriAdi;
    QString arizaTarifi;
    QString yapilanIslem;
    QString tamirBitisTarihi;
    QString testSuresi;
    QString sevkTarihi;
    QString notlar = "";

    NotEkleDialog *idNot;

};

#endif // SERVISDIALOG_H

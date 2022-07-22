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
    QString notSakla;
    QString notlar = "";
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
    bool check = true;
public slots:
    void initialize(QSqlDatabase d,QString sNo);
private slots:
    void on_pushButton_clicked();

    //void on_pushButton_2_clicked();

private:
    Ui::ServisDialog *ui;

    QSqlDatabase database;


    NotEkleDialog *idNot;

};

#endif // SERVISDIALOG_H

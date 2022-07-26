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

    QString servisNo = "";
    QString tarih = "";
    QString saat = "";
    QString musteriAdi = "";
    QString olay = "";
    QString arizaTarifi = "";
    QString yapilanIslem = "";
    QString malzemeler = "";
    QString degisenParcalar = "";
    QString testSuresi = "";
    QString notlar = "";

    bool check = true;
public slots:
    void initialize(QSqlDatabase d,QString sNo);
    void changes();
private slots:
    void on_pushButton_clicked();
    void commandChangedOlay(const QString& command_text);
    //void on_pushButton_2_clicked();

private:
    Ui::ServisDialog *ui;

    QSqlDatabase database;


    NotEkleDialog *idNot;

};

#endif // SERVISDIALOG_H

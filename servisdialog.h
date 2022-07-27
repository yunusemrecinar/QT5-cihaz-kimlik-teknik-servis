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
    QString olay = "";
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



    void on_donanim_1_clicked();

    void on_donanim_2_clicked();

    void on_donanim_3_clicked();

    void on_donanim_4_clicked();

    void on_donanim_8_clicked();

    void on_donanim_7_clicked();

    void on_donanim_9_clicked();

    void on_donanim_5_clicked();

    void on_donanim_6_clicked();

    void on_donanim_11_clicked();

    void on_donanim_10_clicked();

private:
    Ui::ServisDialog *ui;

    QSqlDatabase database;


    NotEkleDialog *idNot;

};

#endif // SERVISDIALOG_H

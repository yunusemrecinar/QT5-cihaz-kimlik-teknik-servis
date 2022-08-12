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

    QString name = "";

    QList<QString> commandsMusteri;

    QString servisNo = "";
    QString tarih = "";
    QString saat = "";
    QString olay = "";
    QString yapilanIslem = "";
    QString malzemeler = "";
    QString degisenParcalar = "";
    QString testSuresi = "";
    QString notlar = "";

    QString musteriAdi;

    bool musteriCheck = false;

    bool check = true;

public slots:
    void initialize(QSqlDatabase d, QString sNo, QString username);
    void changes();
private slots:
    void setLog(QString log);

    void on_pushButton_clicked();

    void commandChangedOlay(const QString& command_text);

    void setOrginalMusteri();

    //void on_pushButton_2_clicked();

    void addMusteri();

    void insertNewMusteri(QString isim);

    void commandChangedMusteriAdi(const QString& command_text);

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

    bool checkMusteriChange = false;

};

#endif // SERVISDIALOG_H

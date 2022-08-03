#ifndef INFORMATIONSERVERDIALOG_H
#define INFORMATIONSERVERDIALOG_H

#include <QDialog>
#include <QSqlDatabase>

namespace Ui {
class InformationServerDialog;
}

class InformationServerDialog : public QDialog
{
    Q_OBJECT

public:
    explicit InformationServerDialog(QWidget *parent = nullptr);
    ~InformationServerDialog();

    QList<QString> commandsMusteri;

    QString oldAnakartNo;
    QString oldDurum;
    QString oldKasaTipi;
    QString oldDeckLink;
    QString oldRam;
    QString oldTestDurumu;
    QString oldIslemci;
    QString oldHDD;
    QString oldUidNo;

    QString tarihLog = "";
public slots:
  void initialize(QString s, QSqlDatabase d);
private:
    Ui::InformationServerDialog *ui;

    QSqlDatabase database;
    QString seriNo;

    QString model;
    QString anakartNo;
    QString cihazSeriNo;
    QString uidNo;
    QString ram;
    QString islemci;
    QString tarih;
    QString hdd;
    QString notlar;
    QString musteriAdi;
    QString durum = "SATIŞ";
    QString testDurumu = "Test Edilecek";
    QString kasaTipi = "1U";
    QString decklink = "Quad";

    bool checkSeriNo = false;
private slots:
    void changes();

    void addMusteri();
    void commandChangedDurum(const QString& command_text);
    void commandChangedTestDurum(const QString& command_text);
    void commandChangedMusteriAdi(const QString& command_text);
    void commandChangedKasaTipi(const QString& command_text);
    void commandChangedDecklink(const QString& command_text);
    void on_pushButton_clicked();
};

#endif // INFORMATIONSERVERDIALOG_H

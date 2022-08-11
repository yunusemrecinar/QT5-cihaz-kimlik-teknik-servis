#ifndef INFORMATIONMOBIOTDIALOG_H
#define INFORMATIONMOBIOTDIALOG_H

#include <QDialog>
#include <QSqlDatabase>

namespace Ui {
class InformationMobiotDialog;
}

class InformationMobiotDialog : public QDialog
{
    Q_OBJECT

public:
    explicit InformationMobiotDialog(QWidget *parent = nullptr);
    ~InformationMobiotDialog();

    QString musteriAdi;
    QList<QString> commandsMusteri;
    QList<QString> commandsModemTipi;

    QString changesNotes = "";



    QString oldDurum = "";
    QString oldAnakartNo = "";
    QString oldUidNo = "";
    QString oldTestDurum = "";
    QString oldModemTipi = "";

    QString tarihLog = "";

    QString username;
public slots:
    void initialize(QString s, QSqlDatabase d, QString username);


private:
    Ui::InformationMobiotDialog *ui;

    QSqlDatabase database;
    QString seriNo;


    QString model = "Mobiot";
    QString anakartNo;
    QString uidNo;
    QString imei1;
    QString imei2;
    QString imei3;
    QString tarih;
    QString notlar;
    QString durum = "SATIŞ";
    QString testDurumu = "Test Edilecek";
    QString modemTipi = "";
private slots:
    void on_pushButton_clicked();
    void changes();

    void addModemTipi();
    void commandChangedDurum(const QString& command_text);
    void commandChangedTestDurum(const QString& command_text);
    void commandChangedMusteriAdi(const QString& command_text);
    void commandChangedModemTipi(const QString& command_text);

    void setLog(QString log);
};

#endif // INFORMATIONMOBIOTDIALOG_H

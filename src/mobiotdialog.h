#ifndef MOBIOTDIALOG_H
#define MOBIOTDIALOG_H

#include <QDialog>
#include <QSqlDatabase>

namespace Ui {
class MobiotDialog;
}

class MobiotDialog : public QDialog
{
    Q_OBJECT

public:
    explicit MobiotDialog(QWidget *parent = nullptr);
    ~MobiotDialog();

    QString musteriAdi;
    QList<QString> commandsMusteri;
    QList<QString> commandsModemTipi;
    QString username;
public slots:
    void initialize(QSqlDatabase d,QString username);
    void commandChangedModel(const QString& command_text);
private slots:
    void on_pushButton_clicked();
    void changes();

    void addMusteri();
    void addModemTipi();
    void commandChangedDurum(const QString& command_text);
    void commandChangedTestDurum(const QString& command_text);
    void commandChangedMusteriAdi(const QString& command_text);
    void commandChangedModemTipi(const QString& command_text);

    void addModels();

    void setLog(QString log);
private:
    Ui::MobiotDialog *ui;

    QList<QString> commandsModel;

    QSqlDatabase database;

    QString model = "Mobiot";
    QString anakartNo;
    QString cihazSeriNo;
    QString uidNo;
    QString imei1;
    QString imei2;
    QString imei3;
    QString tarih;
    QString notlar;
    QString durum = "SATIŞ";
    QString testDurumu = "Test Edilecek";
    QString modemTipi = "";

    bool checkSeriNo = false;
};

#endif // MOBIOTDIALOG_H

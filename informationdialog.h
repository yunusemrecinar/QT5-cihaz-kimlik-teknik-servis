#ifndef INFORMATIONDIALOG_H
#define INFORMATIONDIALOG_H

#include <QDialog>
#include <QMainWindow>
#include <QtSql>
#include <QSqlDatabase>
#include <QMessageBox>
#include "secdialog.h"


namespace Ui {
class InformationDialog;
}

class InformationDialog : public QDialog
{
    Q_OBJECT

public:
    explicit InformationDialog(QWidget *parent = nullptr);  
    void onMessageSent(const QString &);
    ~InformationDialog();

    QString changesNotes = "";
    QString oldModel = "";
    QString oldLcdKart = "";
    QString oldSarjKart = "";
    QString oldDurum = "";
    QString oldAnakartNo = "";
    QString oldModemKart = "";
    QString oldUidNo = "";
    QString oldTestDurum = "";
    QString oldModemTipi = "";

    int countAnakart = 0;
    int countModel = 0;
    int countModemKarti = 0;
    int countDurum = 0;
    int countTestDurum = 0;
    int countSarjKarti = 0;
    int countLcdKarti = 0;
    int countUidNo = 0;

    QString tarihLog = "";

    QString musteriAdi;

public slots:
    void initialize(QString s, QSqlDatabase d);
private slots:
    //void onMessageSent(const QString &);
    void on_pushButton_clicked();

    void changes();
    void commandChanged(const QString& command_text);
    void commandChangedModemKart(const QString& command_text);
    void commandChangedDurum(const QString& command_text);
    void commandChangedSarjKarti(const QString& command_text);
    void commandChangedLcdKarti(const QString& command_text);
    void commandChangedModel(const QString& command_text);
    void commandChangedTestDurum(const QString& command_text);
    void commandChangedModemTipi(const QString& command_text);
    void commandChangedMusteriAdi(const QString& command_text);

private:
    Ui::InformationDialog *ui;
    QString values;
    QString seriNo;
    QMainWindow* _mainWindow;

    QString model;
    QString lcdKart;
    QString sarjKart;
    QString durum;
    QString anakartNo;
    QString modemKart;
    QString modemTipi;

    QSqlDatabase database;
};

#endif // INFORMATIONDIALOG_H

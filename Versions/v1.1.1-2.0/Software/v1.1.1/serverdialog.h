#ifndef SERVERDIALOG_H
#define SERVERDIALOG_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDialog>

namespace Ui {
class ServerDialog;
}

class ServerDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ServerDialog(QWidget *parent = nullptr);
    ~ServerDialog();

    QList<QString> commandsMusteri;
    QList<QString> commandsModel;

    QString username;
public slots:
    void initialize(QSqlDatabase d, QString username);
    void commandChangedModel(const QString& command_text);
private:
    Ui::ServerDialog *ui;

    QSqlDatabase database;

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
    void addModels();
    void addMusteri();
    void commandChangedDurum(const QString& command_text);
    void commandChangedTestDurum(const QString& command_text);
    void commandChangedMusteriAdi(const QString& command_text);
    void commandChangedKasaTipi(const QString& command_text);
    void commandChangedDecklink(const QString& command_text);
    void on_pushButton_clicked();

    void setLog(QString log);
};

#endif // SERVERDIALOG_H

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
    QString degisenParcalar;
public slots:
    void initialize(QString s, QSqlDatabase d);
private slots:
    //void onMessageSent(const QString &);
    void on_pushButton_clicked();
    void degisenParca();
    void changes();
    void commandChanged(const QString& command_text);
    void commandChangedModemKart(const QString& command_text);
    void commandChangedDurum(const QString& command_text);
    void commandChangedSarjKarti(const QString& command_text);
    void commandChangedLcdKarti(const QString& command_text);
    void commandChangedModel(const QString& command_text);
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

    QSqlDatabase database;
};

#endif // INFORMATIONDIALOG_H

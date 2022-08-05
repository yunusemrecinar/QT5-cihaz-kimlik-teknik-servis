#ifndef SECDIALOG_H
#define SECDIALOG_H
#include <QtSql>

#include <QSqlDatabase>
#include <QMessageBox>
#include <QDialog>
#include <QMenu>
#include "serverdialog.h"
#include "mobiotdialog.h"


class QMenu;
class LineEditPopUpForm;

namespace Ui {
class SecDialog;
}

class SecDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SecDialog(QWidget *parent = nullptr);
    ~SecDialog();
    QString musteriAdi;
    QList<QString> commandsMusteri;
    QList<QString> commandsModel;
    QList<QString> commandsModemTipi;

    int count = 0;
public slots:
    void initialize(QSqlDatabase d);
    void commandChangedModel(const QString& command_text);
private slots:
    void addModels();
    void addMusteri();
    void addModemTipi();
    void on_pushButton_clicked();
    void commandChangedDurum(const QString& command_text);

    void commandChangedTestDurum(const QString& command_text);
    void commandChangedMusteriAdi(const QString& command_text);
    void commandChangedModemTipi(const QString& command_text);
    void changes();   

    void on_model__currentTextChanged();

    void checkModelChosen();


private:
    Ui::SecDialog *ui;
    QSqlDatabase database;

    QString anakartNo = "MDO-01-v02-6-b/2013";
    QString modemKarti = "MD10-02-v04/2012";
    QString sarjKarti = "MHD-B7-v.0.0";
    QString durum = "SATIŞ";
    QString lcdKarti = "MHD-B5-v0.0/811/2014";
    QString model = "Mobiot Cihazı";
    QString testDurumu = "Test Edilecek";
    QString modemTipi = "";

    QMenu *m_lineedit_menu;
    LineEditPopUpForm *m_lineedit_popup_form;

    bool checkSeriNo = false;

    ServerDialog *serverDialog;
    MobiotDialog *mobiotDialog;

    bool modelChosen = false;
};

#endif // SECDIALOG_H

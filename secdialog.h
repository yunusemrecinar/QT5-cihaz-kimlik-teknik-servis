#ifndef SECDIALOG_H
#define SECDIALOG_H
#include <QtSql>

#include <QSqlDatabase>
#include <QMessageBox>
#include <QDialog>
#include <QMenu>


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
public slots:
    void initialize(QSqlDatabase d);
private slots:
    void on_pushButton_clicked();
    void commandChanged(const QString& command_text);
    void commandChangedModemKart(const QString& command_text);
    void commandChangedDurum(const QString& command_text);
    void commandChangedSarjKarti(const QString& command_text);
    void commandChangedLcdKarti(const QString& command_text);
    void commandChangedModel(const QString& command_text);
    void degisenParca();
    void changes();
private:
    Ui::SecDialog *ui;
    QSqlDatabase database;

    QString anakartNo = "MDO-01-v02-6-b/2013";
    QString modemKarti = "MD10-02-v04/2012";
    QString sarjKarti = "MHD-B7-v.0.0";
    QString durum = "SATIŞ";
    QString lcdKarti = "MHD-B5-v0.0/811/2014";
    QString model = "Mobiot Cihazı";
    QString degisenParcalar = "";

    QMenu *m_lineedit_menu;
    LineEditPopUpForm *m_lineedit_popup_form;
};

#endif // SECDIALOG_H

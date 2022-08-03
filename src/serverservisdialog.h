#ifndef SERVERSERVISDIALOG_H
#define SERVERSERVISDIALOG_H

#include <QDialog>
#include <QSqlDatabase>

namespace Ui {
class ServerServisDialog;
}

class ServerServisDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ServerServisDialog(QWidget *parent = nullptr);
    ~ServerServisDialog();

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
private:
    Ui::ServerServisDialog *ui;

    QSqlDatabase database;
private slots:
    void on_pushButton_clicked();

    void commandChangedOlay(const QString& command_text);

    void on_donanim_1_clicked();

    void on_donanim_2_clicked();

    void on_donanim_3_clicked();
};

#endif // SERVERSERVISDIALOG_H

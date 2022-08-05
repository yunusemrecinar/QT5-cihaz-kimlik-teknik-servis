#ifndef NOTEKLEDIALOG_H
#define NOTEKLEDIALOG_H

#include <QDialog>
#include <QSqlDatabase>

namespace Ui {
class NotEkleDialog;
}

class NotEkleDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NotEkleDialog(QWidget *parent = nullptr);
    ~NotEkleDialog();
    QString malzemeler = "";
    QString servisNo = "";
    QString UIDno = "";
    QString gelisTarihi = "";
    QString musteriAdi = "";
    QString arizaTarifi = "";
    QString yapilanIslem = "";
    QString tamirBitisTarihi = "";
    QString testSuresi = "";
    QString sevkTarihi = "";

public slots:
    void initialize(QString s, QSqlDatabase d,QString malzemeler,
                    QString UIDno,QString gelisTarihi,QString musteriAdi,
                    QString arizaTarifi,QString yapilanIslem,
                    QString tamirBitisTarihi,QString testSuresi,QString sevkTarihi);
private slots:
    void on_pushButton_clicked();

private:
    Ui::NotEkleDialog *ui;

    QSqlDatabase database;


};

#endif // NOTEKLEDIALOG_H

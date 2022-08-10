#include "notekledialog.h"
#include "ui_notekledialog.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include "mainwindow.h"
#include <QMessageBox>
#include <QSqlError>

#include <iostream>
using namespace std;

NotEkleDialog::NotEkleDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NotEkleDialog)
{
    ui->setupUi(this);
    this->setWindowTitle("");
}

NotEkleDialog::~NotEkleDialog()
{
    delete ui;
}

void NotEkleDialog::on_pushButton_clicked()
{

    if(database.isOpen()) {

        QSqlQuery qry;
        QString not1 = ui->textEdit->toPlainText();

        qry.prepare("INSERT INTO teknikservis(`Cihaz Seri No`,`Geliş Tarihi`,"
                            "`Müşteri Adı`,`Arıza Tarifi`,`Yapılan İşlem`,`Cihazla Gelen Malzemeler`,"
                            "`Tamir Bitiş Tarihi`,`Test Süresi`,`Sevk Tarihi`,`Notlar`)"
                            "VALUES(:servisNo,:uidNo,:gelisTarihi,"
                            ":musteriAdi,:arizaTarifi,:yapilanIslem,:malzemeler,"
                            ":tamirBitisTarih,:testSuresi,:sevkTarihi,:notlar)");
                qry.bindValue(":servisNo",servisNo);
                qry.bindValue(":gelisTarihi",gelisTarihi);
                qry.bindValue(":musteriAdi",musteriAdi);
                qry.bindValue(":arizaTarifi",arizaTarifi);
                qry.bindValue(":yapilanIslem",yapilanIslem);
                qry.bindValue(":malzemeler",malzemeler);
                qry.bindValue(":tamirBitisTarih",tamirBitisTarihi);
                qry.bindValue(":testSuresi",testSuresi);
                qry.bindValue(":sevkTarihi",sevkTarihi);
                qry.bindValue(":notlar",not1);

        if(qry.exec()) {
            QMessageBox::information(this,"Inserted", "Data Inserted Succesfully");
        }else {
            QMessageBox::information(this,"Not Inserted","+"+qry.lastError().text());
        }

    }else {
        QMessageBox::information(this, "Not Connected", "Database Is Not Connected");
        cout << "Database not connected!" << endl;
    }

    this->close();

}

void NotEkleDialog::initialize(QString s, QSqlDatabase d,QString malzemeler,
                               QString UIDno,QString gelisTarihi,QString musteriAdi,
                               QString arizaTarifi,QString yapilanIslem,
                               QString tamirBitisTarihi,QString testSuresi,QString sevkTarihi) {
    servisNo = s;
    database = d;
    this->malzemeler = malzemeler;
    this->UIDno = UIDno;
    this->gelisTarihi = gelisTarihi;
    this->musteriAdi = musteriAdi;
    this->arizaTarifi = arizaTarifi;
    this->yapilanIslem = yapilanIslem;
    this->tamirBitisTarihi = tamirBitisTarihi;
    this->testSuresi = testSuresi;
    this->sevkTarihi = sevkTarihi;
}

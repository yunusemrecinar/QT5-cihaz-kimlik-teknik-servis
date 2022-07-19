#include "servisgetdialog.h"
#include "ui_servisgetdialog.h"
#include <QSqlQuery>
#include <QMessageBox>
#include <QSqlError>
#include "mainwindow.h"

#include <iostream>
using namespace std;

ServisGetDialog::ServisGetDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ServisGetDialog)
{
    ui->setupUi(this);
    this->setFixedSize(this->width(),this->height());
    database = QSqlDatabase::addDatabase("QMYSQL");
    database.setHostName("localhost");
    database.setUserName("root");
    database.setPassword("");
    database.setDatabaseName("modeo");
    this->setWindowTitle(" ");
}

ServisGetDialog::~ServisGetDialog()
{
    delete ui;
}

void ServisGetDialog::initialize(QString s) {
    key = s;



    if(database.open()) {

        QSqlQuery* qry = new QSqlQuery(database);

        qry ->prepare("select * from teknikservis where `Servis No` = '" + s + "'");

        if(qry->exec()) {
            while(qry->next()) {
                ui->servisNo_1->setText(qry->value(0).toString());
                ui->UIDNo_1->setText(qry->value(1).toString());
                ui->gelisTarihi_1->setText(qry->value(2).toString());
                ui->musteriAdi_1->setText(qry->value(3).toString());
                ui->arizaTanimi_1->setText(qry->value(4).toString());
                ui->yapilanIslem_1->setText(qry->value(5).toString());
                ui->donanim_->setText(qry->value(6).toString());
                ui->bitisTarihi1->setText(qry->value(7).toString());
                ui->testSuresi_1->setText(qry->value(8).toString());
                ui->sevkTarihi_1->setText(qry->value(9).toString());
                ui->notlar_->setText(qry->value(10).toString());
            }
        }else {
            QMessageBox::critical(this, tr("error::"), qry->lastError().text());
        }
        //qDebug() << (modal->rowCount());


    }else {
        QMessageBox::information(this, "Not Connected", "Database Is Not Connected");
        cout << "Database not connected!" << endl;
    }
    //database.close();

}

void ServisGetDialog::on_pushButton_clicked()
{
   notlarDialog *notlar = new notlarDialog();
   notlar->initialize(key);
   notlar->exec();


}


void ServisGetDialog::on_pushButton_2_clicked()
{

    //database = QSqlDatabase::addDatabase("QMYSQL");
    //database.setHostName("localhost");
    //database.setUserName("root");
    //database.setPassword("");
    //database.setDatabaseName("modeo");

    if(database.open()) {

        QSqlQuery qry;
        QString UIDNo = ui->UIDNo_1->text();
        QString gelis = ui->gelisTarihi_1->text();
        QString musteriAdi = ui->musteriAdi_1->text();
        QString arizaTarif = ui->arizaTanimi_1->text();
        QString yapilanIslem = ui->yapilanIslem_1->text();
        QString bitis = ui->bitisTarihi1->text();
        QString sevk = ui->sevkTarihi_1->text();
        QString testSure = ui->testSuresi_1->text();
        QString donanim = ui->donanim_->text();
        QString notlar = ui->notlar_->text();

        qry.prepare("UPDATE teknikservis SET `UID No` = '" + UIDNo + "' WHERE `Servis No` = '" + ui->servisNo_1->text() + "';");
        qry.exec();
        qry.clear();
        qry.prepare("UPDATE teknikservis SET `Geliş Tarihi` = '" + gelis + "' WHERE `Servis No` = '" + ui->servisNo_1->text() + "';");
        qry.exec();
        qry.clear();
        qry.prepare("UPDATE teknikservis SET `Müşteri Adı` = '" + musteriAdi + "' WHERE `Servis No` = '" + ui->servisNo_1->text() + "';");
        qry.exec();
        qry.clear();
        qry.prepare("UPDATE teknikservis SET `Arıza Tarifi` = '" + arizaTarif + "' WHERE `Servis No` = '" + ui->servisNo_1->text() + "';");
        qry.exec();
        qry.clear();
        qry.prepare("UPDATE teknikservis SET `Yapılan İşlem` = '" + yapilanIslem + "' WHERE `Servis No` = '" + ui->servisNo_1->text() + "';");
        qry.exec();
        qry.clear();
        qry.prepare("UPDATE teknikservis SET `Cihazla Gelen Malzemeler` = '" + donanim + "' WHERE `Servis No` = '" + ui->servisNo_1->text() + "';");
        qry.exec();
        qry.clear();
        qry.prepare("UPDATE teknikservis SET `Tamir Bitiş Tarihi` = '" + bitis + "' WHERE `Servis No` = '" + ui->servisNo_1->text() + "';");
        qry.exec();
        qry.clear();
        qry.prepare("UPDATE teknikservis SET `Test Süresi` = '" + testSure + "' WHERE `Servis No` = '" + ui->servisNo_1->text() + "';");
        qry.exec();
        qry.clear();
        qry.prepare("UPDATE teknikservis SET `Sevk Tarihi` = '" + sevk + "' WHERE `Servis No` = '" + ui->servisNo_1->text() + "';");



        if(qry.exec()) {
            QMessageBox::information(this,"Inserted","Data Updated Succesfully");
        }else {
            QMessageBox::critical(this, tr("error::"), qry.lastError().text());
        }



    }else {
        QMessageBox::information(this, "Not Connected", "Database Is Not Connected");
        cout << "Database not connected!" << endl;
    }
    //database.close();
    this->close();

}


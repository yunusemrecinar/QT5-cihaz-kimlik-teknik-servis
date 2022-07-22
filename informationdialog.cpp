#include "informationdialog.h"
#include "ui_informationdialog.h"
#include "mainwindow.h"
#include <iostream>
using namespace std;

InformationDialog::InformationDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::InformationDialog)
{
    ui->setupUi(this);

    this->setWindowTitle(" ");
    //MainWindow w;
    //ui->Model->setText(QString::number(w.database.isOpen()));
    //w.database.open();
    //ui->cihazSeriNo->setText(QString::number(w.database.isOpen()));

}



InformationDialog::~InformationDialog()
{
    delete ui;
}
void InformationDialog::initialize(QString s,QSqlDatabase d) {
    database = d;
    //ainWindow w;
    //database = w.database;
    //database = w.database;
    //database = QSqlDatabase::addDatabase("QMYSQL");
    //database.setHostName(w.hostName);
    //database.setUserName(w.userName);
    //database.setPassword(w.password);
    //database.setDatabaseName(w.dbName);
    seriNo = s;

    if(database.isOpen()) {

        QSqlQuery* qry = new QSqlQuery(database);

        qry ->prepare("select * from cihazkimlik where `Cihaz Seri No` = '" + s + "'");

        if(qry->exec()) {
            while(qry->next()) {
                ui->model_->setText(qry->value(0).toString());
                ui->cihaz_seri_no->setText(qry->value(1).toString());
                ui->anakart_->setText(qry->value(2).toString());
                ui->modem_karti_->setText(qry->value(3).toString());
                ui->lcd_karti_->setText(qry->value(4).toString());
                ui->sarj_karti_->setText(qry->value(5).toString());
                ui->durum_->setText(qry->value(6).toString());
                ui->modemSeri1_->setText(qry->value(7).toString());
                ui->modemSeri2_->setText(qry->value(8).toString());
                ui->modemSeri3_->setText(qry->value(9).toString());
                ui->modemSeri4_->setText(qry->value(10).toString());
                ui->modemSeri5_->setText(qry->value(11).toString());
                ui->modemSeri6_->setText(qry->value(12).toString());
                ui->date_->setText(qry->value(13).toString());
                ui->test_durum_->setText(qry->value(14).toString());
                ui->degisenParcalar_->setText(qry->value(15).toString());
                ui->notlar_->setText(qry->value(16).toString());
            }
        }else {
            QMessageBox::critical(this, tr("error::"), qry->lastError().text());
        }

    }else {
        QMessageBox::information(this, "Not Connected", "Database Is Not Connected1");
        cout << "Database not connected!" << endl;
    }
    //database.close();
}


void InformationDialog::on_pushButton_clicked()
{

    //database = QSqlDatabase::addDatabase("QMYSQL");
    //database.setHostName(w.hostName);
    //database.setUserName(w.userName);
    //database.setPassword(w.password);
    //database.setDatabaseName(w.dbName);

    if(database.isOpen()) {

        QSqlQuery qry;
        QString model = ui->model_->text();
        QString anakartNo = ui->anakart_->text();
        QString modemKart = ui->modem_karti_->text();
        QString lcdKart = ui->lcd_karti_->text();
        QString sarjKart = ui->sarj_karti_->text();
        QString modemSeri1 = ui->modemSeri1_->text();
        QString modemSeri2 = ui->modemSeri2_->text();
        QString modemSeri3 = ui->modemSeri3_->text();
        QString modemSeri4 = ui->modemSeri4_->text();
        QString modemSeri5 = ui->modemSeri5_->text();
        QString modemSeri6 = ui->modemSeri6_->text();
        QString durum = ui->durum_->text();
        QString uretimTarih = ui->uretim_tarih->text();
        QString test = ui->test_durum_->text();
        QString degisenParca = ui->degisenParcalar_->text();
        QString notlar = ui->notlar_->text();

        qry.prepare("UPDATE cihazkimlik SET `Model` = '" + model + "' WHERE `Cihaz Seri No` = '" + ui->cihaz_seri_no->text() + "';");
        qry.exec();
        qry.clear();
        qry.prepare("UPDATE cihazkimlik SET `Anakart No` = '" + anakartNo + "' WHERE `Cihaz Seri No` = '" + ui->cihaz_seri_no->text() + "';");
        qry.exec();
        qry.clear();
        qry.prepare("UPDATE cihazkimlik SET `Modem Kartı` = '" + modemKart + "' WHERE `Cihaz Seri No` = '" + ui->cihaz_seri_no->text() + "';");
        qry.exec();
        qry.clear();
        qry.prepare("UPDATE cihazkimlik SET `Lcd Kartı` = '" + lcdKart + "' WHERE `Cihaz Seri No` = '" + ui->cihaz_seri_no->text() + "';");
        qry.exec();
        qry.clear();
        qry.prepare("UPDATE cihazkimlik SET `Şarj Kartı` = '" + sarjKart + "' WHERE `Cihaz Seri No` = '" + ui->cihaz_seri_no->text() + "';");
        qry.exec();
        qry.clear();
        qry.prepare("UPDATE cihazkimlik SET `Durumu` = '" + durum + "' WHERE `Cihaz Seri No` = '" + ui->cihaz_seri_no->text() + "';");
        qry.exec();
        qry.clear();
        qry.prepare("UPDATE cihazkimlik SET `Modem Seri Num 1` = '" + modemSeri1 + "' WHERE `Cihaz Seri No` = '" + ui->cihaz_seri_no->text() + "';");
        qry.exec();
        qry.clear();
        qry.prepare("UPDATE cihazkimlik SET `Modem Seri Num 2` = '" + modemSeri2 + "' WHERE `Cihaz Seri No` = '" + ui->cihaz_seri_no->text() + "';");
        qry.exec();
        qry.clear();
        qry.prepare("UPDATE cihazkimlik SET `Modem Seri Num 3` = '" + modemSeri3 + "' WHERE `Cihaz Seri No` = '" + ui->cihaz_seri_no->text() + "';");
        qry.exec();
        qry.clear();
        qry.prepare("UPDATE cihazkimlik SET `Modem Seri Num 4` = '" + modemSeri4 + "' WHERE `Cihaz Seri No` = '" + ui->cihaz_seri_no->text() + "';");
        qry.exec();
        qry.clear();
        qry.prepare("UPDATE cihazkimlik SET `Modem Seri Num 5` = '" + modemSeri5 + "' WHERE `Cihaz Seri No` = '" + ui->cihaz_seri_no->text() + "';");
        qry.exec();
        qry.clear();
        qry.prepare("UPDATE cihazkimlik SET `Modem Seri Num 6` = '" + modemSeri6 + "' WHERE `Cihaz Seri No` = '" + ui->cihaz_seri_no->text() + "';");
        qry.exec();
        qry.clear();
        qry.prepare("UPDATE cihazkimlik SET `Uretim Tarihi` = '" + uretimTarih + "' WHERE `Cihaz Seri No` = '" + ui->cihaz_seri_no->text() + "';");
        qry.exec();
        qry.clear();
        qry.prepare("UPDATE cihazkimlik SET `Test Durumu` = '" + test + "' WHERE `Cihaz Seri No` = '" + ui->cihaz_seri_no->text() + "';");
        qry.exec();
        qry.clear();
        qry.prepare("UPDATE cihazkimlik SET `Degisen Parcalar` = '" + degisenParca + "' WHERE `Cihaz Seri No` = '" + ui->cihaz_seri_no->text() + "';");
        qry.exec();
        qry.clear();
        qry.prepare("UPDATE cihazkimlik SET `Notlar` = '" + notlar + "' WHERE `Cihaz Seri No` = '" + ui->cihaz_seri_no->text() + "';");

        if(qry.exec()) {
            QMessageBox::information(this,"Inserted","Data Updated Succesfully");
        }else {
            QMessageBox::critical(this, tr("error::"), qry.lastError().text());
        }



    }else {
        QMessageBox::information(this, "Not Connected", "Database Is Not Connected");
        cout << "Database not connected!" << endl;
    }

    this->close();

}


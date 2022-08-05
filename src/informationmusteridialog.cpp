#include "informationmusteridialog.h"
#include "ui_informationmusteridialog.h"
#include <QSqlDatabase>
#include <iostream>
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
using namespace std;

InformationMusteriDialog::InformationMusteriDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::InformationMusteriDialog)
{
    ui->setupUi(this);
}

InformationMusteriDialog::~InformationMusteriDialog()
{
    delete ui;
}

void InformationMusteriDialog::initialize(QSqlDatabase d, QString s)
{
    database = d;
    seriNo = s;
    QString adresTemp;
    if(database.isOpen()) {

        QSqlQuery* qry = new QSqlQuery(database);

        qry ->prepare("select * from `müsteri` where `Cihaz Seri No` = '" + seriNo + "'");

        if(qry->exec()) {
            while(qry->next()) {
                ui->textEditIsim->setText(qry->value(1).toString());
                ui->textEditAdres->setText(qry->value(2).toString());
                if(qry->value(3).toString().contains("\n")) {
                    adresTemp = qry->value(3).toString().replace("\n"," - ");
                    ui->cihazSeriNo->setText(adresTemp);
                }else {
                    ui->cihazSeriNo->setText(qry->value(3).toString());
                }
            }
        }else {
            QMessageBox::critical(this, tr("error::"), qry->lastError().text());
        }

    }else {
        QMessageBox::information(this, "Not Connected", "Database Is Not Connected1");
        cout << "Database not connected!" << endl;
    }
}

void InformationMusteriDialog::on_pushButton_clicked()
{
    if(database.isOpen()) {

        QSqlQuery qry;

        QString isim = ui->textEditIsim->toPlainText();
        QString adres = ui->textEditAdres->toPlainText();

        qry.prepare("UPDATE `müsteri` SET `İsim` = '" + isim + "' WHERE `Cihaz Seri No` = '" + seriNo + "';");
        qry.exec();
        qry.clear();
        qry.prepare("UPDATE `müsteri` SET `Adres` = '" + adres + "' WHERE `Cihaz Seri No` = '" + seriNo + "';");
        if(qry.exec()){

        }else {
            QMessageBox::critical(this, tr("error::"), qry.lastError().text());
        }
        qry.clear();
    }else{
        QMessageBox::information(this, "Not Connected", "Database Is Not Connected");
        cout << "Database not connected!" << endl;
    }
    this->close();
}


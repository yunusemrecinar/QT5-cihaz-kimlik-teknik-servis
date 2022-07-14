#include "servisgetdialog.h"
#include "ui_servisgetdialog.h"
#include <QSqlQuery>
#include <QMessageBox>
#include <QSqlError>
#include "getNotlar.h"

#include <iostream>
using namespace std;

ServisGetDialog::ServisGetDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ServisGetDialog)
{
    ui->setupUi(this);
}

ServisGetDialog::~ServisGetDialog()
{
    delete ui;
}

void ServisGetDialog::initialize(QString s) {
    key = s;
    database = QSqlDatabase::addDatabase("QMYSQL");
    database.setHostName("localhost");
    database.setUserName("root");
    database.setPassword("");
    database.setDatabaseName("modeo");


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
    database.close();

}

void ServisGetDialog::on_pushButton_clicked()
{
   notlarDialog *notlar = new notlarDialog();
   notlar->initialize(key);
   notlar->exec();


}


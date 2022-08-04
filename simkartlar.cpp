#include "simkartlar.h"
#include "ui_simkartlar.h"
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QMessageBox>
#include <QSqlError>

#include <iostream>
using namespace std;

SimKartlar::SimKartlar(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SimKartlar)
{
    ui->setupUi(this);

}

SimKartlar::~SimKartlar()
{
    delete ui;
}

void SimKartlar::initialize(QSqlDatabase d) {
    database = d;

    refresh();
}
void SimKartlar::refresh() {
    QSqlQueryModel * modal = new QSqlQueryModel();
    if(database.isOpen()) {

        QSqlQuery* qry = new QSqlQuery(database);

        qry ->prepare("select * from `simkart`");
        qry -> exec();
        modal->setQuery(*qry);
        ui->tableView->setModel(modal);
        ui->tableView->resizeColumnsToContents();
        ui->tableView->resizeRowsToContents();
        //ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    }else {
        QMessageBox::information(this, "Not Connected", "Database Is Not Connected");
        cout << "Database not connected!" << endl;
    }
}

void SimKartlar::on_pushButtonEkle_clicked()
{
    QString numara = ui->numara_->text();
    QString kartSeriNo = ui->kartSeriNo_->text();
    QString kota = ui->kota_->text();
    QString taahhüt = ui->taahhut_->text();
    QString musteri = ui->musteri_->text();
    QString tarih = ui->tarih_->text();

    if(database.isOpen()) {

        QSqlQuery qry;

            qry.prepare("INSERT INTO `simkart` (`Num`, `Kart Seri No`, `Kota`, `Taahhüt`, `Müşteri`, `Tarih`) VALUES(:numara,:kartSeriNo,:kota,:taahhut,:musteri,:tarih)");
            qry.bindValue(":numara",numara);
            qry.bindValue(":kartSeriNo",kartSeriNo);
            qry.bindValue(":kota",kota);
            qry.bindValue(":taahhut",taahhüt);
            qry.bindValue(":musteri",musteri);
            qry.bindValue(":tarih",tarih);
            if(qry.exec()) {
                QMessageBox::information(this,"Inserted","Data Inserted Succesfully");
            }else {
                QMessageBox::information(this,"Not Inserted",qry.lastError().text());
            }
            ui->numara_->clear();
            ui->kartSeriNo_->clear();
            ui->kota_->clear();
            ui->taahhut_->clear();
            ui->musteri_->clear();
            ui->tarih_->clear();
        refresh();
    }else {
        QMessageBox::information(this, "Not Connected", "Database Is Not Connected");
        cout << "Database not connected!" << endl;
    }
}


void SimKartlar::on_pushButtonSil_clicked()
{
    if(database.isOpen()) {

        QSqlQuery qry;

                qry.prepare("DELETE FROM `simkart` WHERE `Kart Seri No` = '" + rowLocation + "';");
                if(qry.exec()){

                }else {
                    QMessageBox::information(this,"Not Inserted",qry.lastError().text());
                }

        refresh();
    }else {
        QMessageBox::information(this, "Not Connected", "Database Is Not Connected");
        cout << "Database not connected!" << endl;
    }
}


void SimKartlar::on_tableView_clicked()
{
    int row = ui->tableView->currentIndex().row();
    rowLocation = ui->tableView->model()->data(ui->tableView->model()->index(row,1)).toString();
}


#include "simkartlar.h"
#include "ui_simkartlar.h"
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QMessageBox>
#include <QSqlError>
#include <QTime>

#include <iostream>
using namespace std;

SimKartlar::SimKartlar(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SimKartlar)
{
    ui->setupUi(this);
    changes();
}

SimKartlar::~SimKartlar()
{
    delete ui;
}

void SimKartlar::changes() {
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableView->horizontalHeader()->setStyleSheet("QHeaderView { font-size: 18pt; color:#002B5B; font-weight: bold; }");

    ui->numara_->setValidator(new QRegularExpressionValidator(QRegularExpression("\\d*")));
    ui->kartSeriNo_->setValidator(new QRegularExpressionValidator(QRegularExpression("\\d*")));


}

void SimKartlar::initialize(QSqlDatabase d, QString user) {
    database = d;
    username = user;
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

    }else {
        QMessageBox::information(this, "Not Connected", "Database Is Not Connected");
        setLog("[ERROR] simkartlar.cpp : " + database.lastError().text());
        cout << "Database not connected!" << endl;
    }
}
void SimKartlar::setLog(QString content) {

    QSqlQuery qry;
    QString date = QDateTime::currentDateTime().toString("dd.MM.yyyy hh:mm:ss");
    qry.prepare("INSERT INTO processlogs(`tarih`,`username`,`process`) VALUES (:tarih,:username,:process)");
    qry.bindValue(":tarih",date);
    qry.bindValue(":username",username);
    qry.bindValue(":process",content);
    qry.exec();
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
                setLog("[NOTE] simkartlar.cpp : sim kart eklendi.");
            }else {
                QMessageBox::information(this,"Not Inserted",qry.lastError().text());
                setLog("[NOTE] simkartlar.cpp : " + qry.lastError().text());
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
        setLog("[NOTE] simkartlar.cpp : " + database.lastError().text());
        cout << "Database not connected!" << endl;
    }
}


void SimKartlar::on_pushButtonSil_clicked()
{
    if(database.isOpen()) {

        QSqlQuery qry;

                qry.prepare("DELETE FROM `simkart` WHERE `Kart Seri No` = '" + rowLocation + "';");
                if(qry.exec()){
                    setLog("[NOTE] simkartlar.cpp : sim kart silindi");
                }else {
                    QMessageBox::information(this,"Not Inserted",qry.lastError().text());
                    setLog("[NOTE] simkartlar.cpp : " + qry.lastError().text());
                }

        refresh();
    }else {
        QMessageBox::information(this, "Not Connected", "Database Is Not Connected");
        setLog("[NOTE] simkartlar.cpp : " + database.lastError().text());
        cout << "Database not connected!" << endl;
    }
}


void SimKartlar::on_tableView_clicked()
{
    int row = ui->tableView->currentIndex().row();
    rowLocation = ui->tableView->model()->data(ui->tableView->model()->index(row,1)).toString();
}


#include "musteri.h"
#include "ui_musteri.h"
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QMessageBox>
#include <QSqlError>

#include <iostream>
using namespace std;

Musteri::Musteri(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Musteri)
{
    ui->setupUi(this);
    ui->cihazSeriNo->setMaxLength(9);
    ui->cihazSeriNo->setValidator(new QRegularExpressionValidator(QRegularExpression("\\d*")));
}

void Musteri::initialize(QSqlDatabase d) {
    database = d;

    QSqlQueryModel * modal = new QSqlQueryModel();
    if(database.isOpen()) {

        QSqlQuery* qry = new QSqlQuery(database);

        qry ->prepare("select * from `müsteri`");
        qry -> exec();
        modal->setQuery(*qry);
        ui->tableView->setModel(modal);
        ui->tableView->hideColumn(0);
        ui->tableView->resizeColumnsToContents();
        ui->tableView->resizeRowsToContents();
        ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    }else {
        QMessageBox::information(this, "Not Connected", "Database Is Not Connected");
        cout << "Database not connected!" << endl;
    }
}

Musteri::~Musteri()
{
    delete ui;
}

void Musteri::on_pushButton_clicked()
{
    if(database.isOpen()) {

        QString isim = ui->textEditIsim->toPlainText();
        QString adres = ui->textEditAdres->toPlainText();
        QString cihazSeriNo = ui->cihazSeriNo->text();
        QSqlQuery qry;

        int count;
        QString temp = "";
        if(ui->cihazSeriNo->text().length() == 9) {
                    checkSeriNo = true;
                }
        if(checkSeriNo) {
            qry.prepare("SELECT COUNT(*) FROM `müsteri` WHERE `İsim` = '" + isim + "';");
            qry.exec();
            while(qry.next()) {
                count = qry.value(0).toInt();
            }
            qry.clear();
            if(count == 1) {
                qry.prepare("SELECT `Cihaz Seri No` FROM `müsteri` WHERE İsim = '" + isim + "';");
                qry.exec();
                while(qry.next()) {
                    temp = qry.value(0).toString();
                }
                temp += "\n"+cihazSeriNo;
                qry.clear();
                qry.prepare("UPDATE `müsteri` SET `Cihaz Seri No` = '"+temp+"' WHERE İsim = '" + isim + "';");
                qry.exec();
            }else {
                qry.prepare("SELECT `Cihaz Seri No` FROM `müsteri`");
                qry.exec();
                QList<QString> list;
                while(qry.next()) { list.append(qry.value(0).toString()); }

                if(list.contains(cihazSeriNo)){
                    QMessageBox::information(this,"HATA","Bir Cihaz Seri No birden çok müşteriye ait olamaz!!");
                }else {
                    qry.clear();
                    qry.prepare("INSERT INTO müsteri(`İsim`,`Adres`,`Cihaz Seri No`) "
                                "VALUES(:isim,:adres,:cihazSeriNo)");
                    qry.bindValue(":isim",isim);
                    qry.bindValue(":adres",adres);
                    qry.bindValue(":cihazSeriNo",cihazSeriNo);

                    qry.exec();
                }
            }
        }else {
            QMessageBox::information(this,"Error", "Cihaz Seri Numarasını Kontrol Edin!!");
        }
        ui->textEditIsim->clear();
        ui->textEditAdres->clear();
        ui->cihazSeriNo->clear();
        qry.clear();

        QSqlQueryModel *model = new QSqlQueryModel();

        if(database.isOpen()) {
            QSqlQuery* qry = new QSqlQuery(database);

            //model = new QSqlQueryModel();

            //setValue("select * from cihazkimlik");
            //ui->tableView->setModel(model);
            qry ->prepare("select * from müsteri");
            qry -> exec();
            model->setQuery(*qry);
            ui->tableView->setModel(model);
            ui->tableView->resizeColumnsToContents();
            ui->tableView->resizeRowsToContents();
            ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

        }else {
            QMessageBox::information(this, "Not Connected", database.lastError().text());
            cout << "Database not connected!" << endl;
        }

    }else {
        QMessageBox::information(this, "Not Connected", "Database Is Not Connected");
        cout << "Database not connected!" << endl;
    }

}


void Musteri::on_tableView_clicked(const QModelIndex &index)
{
    int row = ui->tableView->currentIndex().row();
    rowId = ui->tableView->model()->data(ui->tableView->model()->index(row,0)).toString();
}


void Musteri::on_pushButton_sil_clicked()
{
    QSqlQuery qry;

    qry.prepare("DELETE FROM müsteri WHERE `Id` = " + rowId);
    qry.exec();

    qry.clear();

    QSqlQueryModel *model = new QSqlQueryModel();

    if(database.isOpen()) {
        QSqlQuery* qry = new QSqlQuery(database);

        //model = new QSqlQueryModel();

        //setValue("select * from cihazkimlik");
        //ui->tableView->setModel(model);
        qry ->prepare("select * from müsteri");
        qry -> exec();
        model->setQuery(*qry);
        ui->tableView->setModel(model);
        ui->tableView->resizeColumnsToContents();
        ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    }else {
        QMessageBox::information(this, "Not Connected", database.lastError().text());
        cout << "Database not connected!" << endl;
    }
}


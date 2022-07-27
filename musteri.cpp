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
    if(database.open()) {

        QSqlQuery* qry = new QSqlQuery(database);

        qry ->prepare("select * from `müsteri`");
        qry -> exec();
        modal->setQuery(*qry);
        ui->tableView->setModel(modal);
        ui->tableView->resizeColumnsToContents();
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

        if(ui->cihazSeriNo->text().length() == 9) {
                    checkSeriNo = true;
                }

        qry.prepare("INSERT INTO müsteri(`İsim`,`Adres`,`Cihaz Seri No`) "
                    "VALUES(:isim,:adres,:cihazSeriNo)");
        qry.bindValue(":isim",isim);
        qry.bindValue(":adres",adres);
        qry.bindValue(":cihazSeriNo",cihazSeriNo);

        if(checkSeriNo) {
            qry.exec();
        }else {
            QMessageBox::information(this,"Error", "Cihaz Seri Numarasını Kontrol Edin!!");
        }

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

    }else {
        QMessageBox::information(this, "Not Connected", "Database Is Not Connected");
        cout << "Database not connected!" << endl;
    }

}


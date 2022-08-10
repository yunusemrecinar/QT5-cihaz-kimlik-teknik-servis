#include "notlardialog.h"
#include "ui_notlardialog.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QMessageBox>
#include "mainwindow.h"
#include <QSqlError>

#include <iostream>
using namespace std;

notlarDialog::notlarDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::notlarDialog)
{
    ui->setupUi(this);
    this->setWindowTitle(" ");
}

notlarDialog::~notlarDialog()
{
    delete ui;
}

void notlarDialog::initialize(QString sira, QSqlDatabase d) {

    //servisNo = s;
    database = d;
    data = sira;

    if(database.isOpen()) {

        QSqlQuery* qry = new QSqlQuery(database);

        qry ->prepare("select Notlar from teknikservis where `Sıra` = '" + data +"';");

        if(qry->exec()) {

            while(qry->next()) {
                ui->lineEdit->setText(qry->value(0).toString());
            }

        }else {
            QMessageBox::critical(this, tr("error::"), qry->lastError().text());
        }

    }else {
        QMessageBox::information(this, "Not Connected", "Database Is Not Connected");
        cout << "Database not connected!" << endl;
    }

}

void notlarDialog::on_pushButton_clicked()
{

    if(database.isOpen()) {

        QSqlQuery qry;
        QString not1 = ui->lineEdit->toPlainText();
        qry.prepare("UPDATE teknikservis SET Notlar = '" + not1 + "' WHERE `Sıra` = '" + data + "';");
        qry.bindValue(":not",not1);

        if(qry.exec()) {
            QMessageBox::information(this,"Inserted","Data Inserted Succesfully");
        }else {
            QMessageBox::critical(this, tr("error::"), qry.lastError().text());
        }



    }else {
        QMessageBox::information(this, "Not Connected", "Database Is Not Connected");
        cout << "Database not connected!" << endl;
    }

    this->close();

}


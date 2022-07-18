#include "notlardialog.h"
#include "ui_notlardialog.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QMessageBox>
#include <QSqlError>

#include <iostream>
using namespace std;

notlarDialog::notlarDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::notlarDialog)
{
    ui->setupUi(this);
    this->setFixedSize(this->width(),this->height());
    this->setWindowTitle(" ");
}

notlarDialog::~notlarDialog()
{
    delete ui;
}

void notlarDialog::initialize(QString s) {

    servisNo = s;
    database = QSqlDatabase::addDatabase("QMYSQL");
    database.setHostName("localhost");
    database.setUserName("root");
    database.setPassword("");
    database.setDatabaseName("modeo");

    if(database.open()) {

        QSqlQuery* qry = new QSqlQuery(database);

        qry ->prepare("select Notlar from teknikservis where `Servis No` = '" + s + "'");

        if(qry->exec()) {

            while(qry->next()) {
                ui->lineEdit->setText(qry->value(0).toString());
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

void notlarDialog::on_pushButton_clicked()
{
    database = QSqlDatabase::addDatabase("QMYSQL");
    database.setHostName("localhost");
    database.setUserName("root");
    database.setPassword("");
    database.setDatabaseName("modeo");

    if(database.open()) {

        QSqlQuery qry;
        QString not1 = ui->lineEdit->toPlainText();
        qry.prepare("UPDATE teknikservis SET Notlar = '" + not1 + "' WHERE `Servis No` = '" + servisNo + "'");
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
    database.close();
    this->close();

}


#include "notekledialog.h"
#include "ui_notekledialog.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QMessageBox>
#include <QSqlError>

#include <iostream>
using namespace std;

NotEkleDialog::NotEkleDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NotEkleDialog)
{
    ui->setupUi(this);
    this->setFixedSize(this->width(),this->height());
    this->setWindowTitle("");
}

NotEkleDialog::~NotEkleDialog()
{
    delete ui;
}

void NotEkleDialog::on_pushButton_clicked()
{

    database = QSqlDatabase::addDatabase("QMYSQL");
    database.setHostName("localhost");
    database.setUserName("root");
    database.setPassword("");
    database.setDatabaseName("modeo");

    if(database.open()) {

        QSqlQuery qry;
        QString not1 = ui->textEdit->toPlainText();
        qry.prepare("UPDATE teknikservis SET Notlar = ':not' WHERE `Servis No` = '" + servisNo + "'");
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

void NotEkleDialog::initialize(QString s) {
    servisNo = s;
}

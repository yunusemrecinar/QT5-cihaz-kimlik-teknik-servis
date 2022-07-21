#include "notekledialog.h"
#include "ui_notekledialog.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include "mainwindow.h"
#include <QMessageBox>
#include <QSqlError>

#include <iostream>
using namespace std;

NotEkleDialog::NotEkleDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NotEkleDialog)
{
    ui->setupUi(this);
    this->setWindowTitle("");
}

NotEkleDialog::~NotEkleDialog()
{
    delete ui;
}

void NotEkleDialog::on_pushButton_clicked()
{
    MainWindow w;
    database = QSqlDatabase::addDatabase("QMYSQL");
    database.setHostName(w.hostName);
    database.setUserName(w.userName);
    database.setPassword(w.password);
    database.setDatabaseName(w.dbName);

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

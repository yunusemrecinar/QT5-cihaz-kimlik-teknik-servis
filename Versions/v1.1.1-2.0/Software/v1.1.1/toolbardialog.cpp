#include "toolbardialog.h"
#include "ui_toolbardialog.h"
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QMessageBox>
#include <QTime>
#include <QSqlError>

#include <iostream>
using namespace std;

ToolBarDialog::ToolBarDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ToolBarDialog)
{
    ui->setupUi(this);
}

ToolBarDialog::~ToolBarDialog()
{
    delete ui;
}

void ToolBarDialog::initialize(QSqlDatabase d, QString type, QString databaseName, QString user)
{
    ui->label->setText(type);
    database = d;
    databaseName_ = databaseName;
    refresh();
}
void ToolBarDialog::setLog(QString content) {

    QSqlQuery qry;
    QString date = QDateTime::currentDateTime().toString("dd.MM.yyyy hh:mm:ss");
    qry.prepare("INSERT INTO processlogs(`tarih`,`username`,`process`) VALUES (:tarih,:username,:process)");
    qry.bindValue(":tarih",date);
    qry.bindValue(":username",username);
    qry.bindValue(":process",content);
    qry.exec();
}
void ToolBarDialog::refresh() {
    QSqlQueryModel * modal = new QSqlQueryModel();
    if(database.isOpen()) {

        QSqlQuery* qry = new QSqlQuery(database);

        qry ->prepare("select * from `" + databaseName_ +"`");
        qry -> exec();
        modal->setQuery(*qry);
        ui->tableView->setModel(modal);
        ui->tableView->resizeColumnsToContents();
        ui->tableView->resizeRowsToContents();
        ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    }else {
        QMessageBox::information(this, "Not Connected", "Database Is Not Connected");
        setLog("[ERROR] toolbardialog.cpp : " + database.lastError().text());
        cout << "Database not connected!" << endl;
    }
}

void ToolBarDialog::on_pushButtonEkle_clicked()
{
    QString name = ui->lineEdit->text();

    if(database.isOpen()) {

        QSqlQuery qry;

                qry.prepare("INSERT INTO `" + databaseName_ +"` VALUES(:isim)");
                qry.bindValue(":isim",ui->lineEdit->text());
                if(name.length() != 0) {
                    if(qry.exec()) {
                        setLog("[NOTE] toolbardialog.cpp : " + databaseName_ + " tablosuna ekleme yapıldı");
                    }else {
                        setLog("[ERROR] toolbardialog.cpp : " + qry.lastError().text());
                    }
                }

        ui->lineEdit->clear();
        refresh();
    }else {
        QMessageBox::information(this, "Not Connected", "Database Is Not Connected");
        setLog("[ERROR] toolbardialog.cpp : " + database.lastError().text());
        cout << "Database not connected!" << endl;
    }
}


void ToolBarDialog::on_pushButtonSil_clicked()
{
    if(database.isOpen()) {

        QSqlQuery qry;

                qry.prepare("DELETE FROM `" + databaseName_ +"` WHERE name = '" + rowLocation + "';");
                if(qry.exec()) {
                    setLog("[NOTE] toolbardialog.cpp : " + databaseName_ + " tablosundan veri silindi");
                }else {
                    setLog("[ERROR] toolbardialog.cpp : " + qry.lastError().text());
                }

        refresh();
    }else {
        QMessageBox::information(this, "Not Connected", "Database Is Not Connected");
        setLog("[ERROR] toolbardialog.cpp : " + database.lastError().text());
        cout << "Database not connected!" << endl;
    }
}


void ToolBarDialog::on_tableView_clicked()
{
    int row = ui->tableView->currentIndex().row();
    rowLocation = ui->tableView->model()->data(ui->tableView->model()->index(row,0)).toString();
}


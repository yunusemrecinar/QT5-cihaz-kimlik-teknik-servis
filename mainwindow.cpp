#include "mainwindow.h"
#include <QMessageBox>
#include "ui_mainwindow.h"
#include <QMessageBox>
#include "lineeditpopupform.h"
#include "secdialog.h"
#include "servisdialog.h"
#include "informationdialog.h"
#include "servisgetdialog.h"
#include <QTableView>
#include <QScrollArea>

#include <iostream>
using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow),
      _information(nullptr)
{
    ui->setupUi(this);

    readFile("test.txt");
    addColumns();

    this->setWindowTitle("ANA MENÜ");
    ui->pushButton_servis_verigetir->setVisible(false);


}

void MainWindow::readFile(QString filename)
{
    QFile file(filename);
    if(!file.exists())
    {
        hostName = "localhost";
        userName = "root";
        password = "";
        dbName = "modeo";

    }
    if(!file.open(QIODevice::ReadOnly))
    {

    }

    QTextStream stream(&file);
    bool first = true;
    bool second = false;
    bool third = false;
    bool fourth = false;
    while(!stream.atEnd()) {
        if(first) {
            QString temp1 = stream.readLine();
            QStringList temp = temp1.split("=");
            hostName = temp.value(temp.length()-1).trimmed();
            first = false;
            second = true;
        }
        else if(second) {
            QString temp1 = stream.readLine();
            QStringList temp = temp1.split("=");
            userName = temp.value(temp.length()-1).trimmed();
            second = false;
            third = true;
        }
        else if(third) {
            QString temp1 = stream.readLine();
            QStringList temp = temp1.split("=");
            password = temp.value(temp.length()-1).trimmed();
            third = false;
            fourth = true;
        }
        else if(fourth) {
            QString temp1 = stream.readLine();
            QStringList temp = temp1.split("=");
            dbName = temp.value(temp.length()-1).trimmed();
            break;
        }        
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
}

void MainWindow::on_pushButton_load_clicked()
{

    //database = QSqlDatabase::addDatabase("QMYSQL");
    //database.setHostName(hostName);
    //database.setUserName(userName);
    //database.setPassword(password);
    //database.setDatabaseName(dbName);
    //modal = new QSqlQueryModel();
    QSqlQueryModel *model = new QSqlQueryModel();

    if(database.isOpen()) {
        QSqlQuery* qry = new QSqlQuery(database);

        //model = new QSqlQueryModel();

        //setValue("select * from cihazkimlik");
        //ui->tableView->setModel(model);
        qry ->prepare("select * from cihazkimlik");
        qry -> exec();
        model->setQuery(*qry);
        ui->tableView->setModel(model);
        ui->tableView->resizeColumnsToContents();
        //modal->submit();
        foreach(int col, columnsToHide)
            ui->tableView->hideColumn(col);
        //columnsToHide.append(0);
    }else {
        QMessageBox::information(this, "Not Connected", database.lastError().text());
        cout << "Database not connected!" << endl;
    }

}

void MainWindow::addColumns() {
    columnsToHide.append(2);
    columnsToHide.append(4);
    columnsToHide.append(5);
    columnsToHide.append(6);
    columnsToHide.append(8);
    columnsToHide.append(9);
    columnsToHide.append(10);
    columnsToHide.append(11);
    columnsToHide.append(12);
    columnsToHide.append(13);
    columnsToHide.append(15);
    columnsToHide.append(16);
    columnsToHide.append(17);
}
//QSqlQueryModel* MainWindow::setValue(QString value) {
//    model->setQuery(value);
//
//    return model;
    //model->setQuery(value);
//}
void MainWindow::on_pushButton_2_clicked()
{
    //SecDialog secdialog;
    //secdialog.setModal(true);
    //secdialog.exec();
    secdialog = new SecDialog(this);
    secdialog->initialize(database);
    secdialog->show();    
}

void MainWindow::on_getInformation_clicked()
{
    InformationDialog *inform = new InformationDialog();
    inform->initialize(mainWindowValue,database);
    inform->show();
}

void MainWindow::on_pushButton_servis_bilgial_clicked()
{
    ServisGetDialog *servisDialog = new ServisGetDialog();
    servisDialog->initialize(rowCount, database);
    servisDialog->exec();
}

void MainWindow::on_pushButton_servis_verigetir_clicked()
{
    //database2 = QSqlDatabase::addDatabase("QMYSQL");
    //database2.setHostName("localhost");
    //database2.setUserName("root");
    //database2.setPassword("");
    //database2.setDatabaseName("modeo");

    QSqlQueryModel * modal = new QSqlQueryModel();

    if(database1.open()) {

        QSqlQuery* qry = new QSqlQuery(database1);

        qry ->prepare("select * from teknikservis");
        qry -> exec();
        modal->setQuery(*qry);
        ui->tableView_teknikServis->setModel(modal);
        ui->tableView_teknikServis->resizeColumnsToContents();

    }else {
        QMessageBox::information(this, "Not Connected", "Database Is Not Connected");
        cout << "Database not connected!" << endl;
    }
}

void MainWindow::on_pushButton_servis_ekle_clicked()
{
    servisDialog = new ServisDialog(this);
    servisDialog->initialize(database,mainWindowValue);
    servisDialog->show();
}

void MainWindow::on_tableView_clicked(const QModelIndex &index)
{
    QString value = ui->tableView->model()->data(index).toString();
    mainWindowValue = value;

    QSqlQueryModel * modal = new QSqlQueryModel();

    if(database.open()) {

        QSqlQuery* qry = new QSqlQuery(database1);

        qry ->prepare("select * from teknikservis where `Servis No` = " + mainWindowValue);
        qry -> exec();
        modal->setQuery(*qry);
        ui->tableView_teknikServis->setModel(modal);
        ui->tableView_teknikServis->resizeColumnsToContents();


    }else {
        QMessageBox::information(this, "Not Connected", "Database Is Not Connected");
        cout << "Database not connected!" << endl;
    }

}

void MainWindow::on_tableView_teknikServis_clicked(const QModelIndex &index)
{
    QString value = ui->tableView_teknikServis->model()->data(index).toString();
    int row = ui->tableView_teknikServis->currentIndex().row();
    QString rowValue = ui->tableView_teknikServis->model()->data(ui->tableView_teknikServis->model()->index(row,0)).toString();

    serviceValue = value;
    rowCount = rowValue;

}

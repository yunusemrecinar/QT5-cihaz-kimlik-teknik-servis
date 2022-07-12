#include "mainwindow.h"
#include <QMessageBox>
#include "ui_mainwindow.h"
#include <QMessageBox>
#include "lineeditpopupform.h"
#include "secdialog.h"
#include "servisdialog.h"
#include "informationdialog.h"


#include <iostream>
using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow),
      _information(nullptr)
{

    ui->setupUi(this);



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

    database1 = QSqlDatabase::addDatabase("QMYSQL");
    database1.setHostName("localhost");
    database1.setUserName("root");
    database1.setPassword("");
    database1.setDatabaseName("modeo");

    QSqlQueryModel * modal = new QSqlQueryModel();

    if(database1.open()) {

        QSqlQuery* qry = new QSqlQuery(database1);

        qry ->prepare("select * from cihazkimlik");
        qry -> exec();
        modal->setQuery(*qry);
        ui->tableView->setModel(modal);


    }else {
        QMessageBox::information(this, "Not Connected", "Database Is Not Connected");
        cout << "Database not connected!" << endl;
    }
    database1.close();
}


void MainWindow::on_pushButton_2_clicked()
{
    //SecDialog secdialog;
    //secdialog.setModal(true);
    //secdialog.exec();
    secdialog = new SecDialog(this);
    secdialog->show();
}
/*
void MainWindow::on_getInformation_clicked() {
    QString message(ui->label->text());
    emit notifyMessageSent(message);
}*/

void MainWindow::on_tableView_activated(const QModelIndex &index)
{
    QString value = ui->tableView->model()->data(index).toString();
    mainWindowValue = value;
    //ui->label->setText(value);
    /*
    QString value = ui->tableView->model()->data(index).toString();

    ui->label->setText(value);
    qDebug() << (value);
    selectedValue = value;
    qDebug() << (selectedValue);
    database = QSqlDatabase::addDatabase("QMYSQL");
    database.setHostName("localhost");
    database.setUserName("root");
    database.setPassword("");
    database.setDatabaseName("modeo");

    QSqlQueryModel * modal = new QSqlQueryModel();

    if(database.open()) {
        QSqlQuery* qry = new QSqlQuery(database);

        qry ->prepare("select `Uretim Tarihi`, `Durumu` from cihazkimlik where `Cihaz Seri No` = "+value);
        qry->exec();
        modal->setQuery(*qry);
        ui->tableView_teknikServis->setModel(modal);

    }


*/
}


void MainWindow::on_getInformation_clicked()
{
    //InformationDialog informationDialog;
    //informationDialog.setModal(true);
    //informationDialog.exec();

    // üstteki gibi yaptığımızda açılan yeni ekran kapanmadan bi önceki ekran tıklanmaz hala gelir.
    // alttaki gibi yaptığımızda açılan yeni ekrana bakmadan farklı ekranlara geçebiliriz.
    //selectedVal = ui->label->text();
    //QString message(ui->label->text());
    //emit notifyMessageSent(message);
/*
    if(_information) {
        _information = new InformationDialog(this);

        connect(this,SIGNAL(on_getInformation_clicked),
                _information, SLOT(onMessageSent));

    }

    informationdialog = new InformationDialog(this);
    informationdialog->show();*/
    InformationDialog *inform = new InformationDialog();
    inform->initialize(mainWindowValue);
    inform->exec();
}


void MainWindow::on_pushButton_servis_verigetir_clicked()
{
    database2 = QSqlDatabase::addDatabase("QMYSQL");
    database2.setHostName("localhost");
    database2.setUserName("root");
    database2.setPassword("");
    database2.setDatabaseName("modeo");

    QSqlQueryModel * modal = new QSqlQueryModel();

    if(database2.open()) {

        QSqlQuery* qry = new QSqlQuery(database2);

        qry ->prepare("select * from teknikservis");
        qry -> exec();
        modal->setQuery(*qry);
        ui->tableView_teknikServis->setModel(modal);


    }else {
        QMessageBox::information(this, "Not Connected", "Database Is Not Connected");
        cout << "Database not connected!" << endl;
    }
    database1.close();
}


void MainWindow::on_pushButton_servis_ekle_clicked()
{
    servisDialog = new ServisDialog(this);
    servisDialog->show();
}


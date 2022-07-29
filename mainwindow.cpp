#include "mainwindow.h"
#include <QMessageBox>
#include "ui_mainwindow.h"
#include <QMessageBox>
#include "lineeditpopupform.h"
#include "musteri.h"
#include "secdialog.h"
#include "servisdialog.h"
#include "informationdialog.h"
#include "servisgetdialog.h"
#include <QTableView>
#include <QScrollArea>
#include <QDebug>
#include "toolbardialog.h"



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
    hideColumns();

    this->setWindowTitle("ANA MENÜ");   
    ui->toolBar->addWidget(ui->pushButton);
    ui->toolBar->addWidget(ui->pushButton_modemTipi);
    ui->toolBar->addWidget(ui->pushButton_Model);
    ui->lineEdit->setPlaceholderText("Filtrele");
    ui->lineEdit->setReadOnly(1);


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

void MainWindow::myfunction()
{
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
        ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    }else {
        QMessageBox::information(this, "Not Connected", database.lastError().text());
        cout << "Database not connected!" << endl;
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_lineEdit_textChanged(const QString &arg1)
{
    QSqlQueryModel *model = new QSqlQueryModel();

    if(database.isOpen()) {
        QSqlQuery* qry = new QSqlQuery(database);

        //model = new QSqlQueryModel();

        //setValue("select * from cihazkimlik");
        //ui->tableView->setModel(model);
        qry ->prepare("select * from cihazkimlik where `Cihaz Seri No` LIKE '" + arg1 + "%' OR `Müşteri Adı` LIKE '" + arg1 + "%'");
        qry -> exec();
        model->setQuery(*qry);
        ui->tableView->setModel(model);
        ui->tableView->resizeColumnsToContents();
        //modal->submit();
        foreach(int col, columnsToHide)
            ui->tableView->hideColumn(col);
        //columnsToHide.append(0);
        ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    }else {
        QMessageBox::information(this, "Not Connected", database.lastError().text());
        cout << "Database not connected!" << endl;
    }
}

void MainWindow::hideColumns() {
    columnsToHideService.append(0);
    columnsToHideService.append(1);
    columnsToHideService.append(5);
    columnsToHideService.append(6);
    columnsToHideService.append(7);
    columnsToHideService.append(8);

}
void MainWindow::addColumns() {
    columnsToHide.append(0);
    columnsToHide.append(3);
    columnsToHide.append(5);
    columnsToHide.append(6);
    columnsToHide.append(7);
    columnsToHide.append(9);
    columnsToHide.append(10);
    columnsToHide.append(11);
    columnsToHide.append(12);
    columnsToHide.append(13);
    columnsToHide.append(14);
    columnsToHide.append(15);
    columnsToHide.append(16);
    columnsToHide.append(18);
    columnsToHide.append(19);
}

void MainWindow::on_pushButton_2_clicked()
{
    //SecDialog secdialog;
    //secdialog.setModal(true);
    //secdialog.exec();
    secdialog = new SecDialog(this);
    secdialog->initialize(database);
    secdialog->exec();
    refresh();
    ui->lineEdit->clear();
}

void MainWindow::on_pushButton_servis_ekle_clicked()
{
    servisDialog = new ServisDialog(this);
    servisDialog->initialize(database,mainWindowValue);
    servisDialog->exec();
    refreshServis();
}

void MainWindow::on_tableView_clicked(const QModelIndex &index)
{
    //QString value = ui->tableView->model()->data(index).toString();
    int row = ui->tableView->currentIndex().row();
    QString rowValue = ui->tableView->model()->data(ui->tableView->model()->index(row,2)).toString();

    mainWindowValue = rowValue;
    ui->servisLabel->setText("Teknik Servis (" + mainWindowValue + ")");

    refreshServis();
    refreshLog();

}
void MainWindow::on_tableView_doubleClicked(const QModelIndex &index)
{
    //QString value = ui->tableView->model()->data(index).toString();
    int row = ui->tableView->currentIndex().row();
    QString rowValue = ui->tableView->model()->data(ui->tableView->model()->index(row,2)).toString();

    mainWindowValue = rowValue;

    InformationDialog *inform = new InformationDialog();
    inform->initialize(mainWindowValue,database);
    inform->exec();
    refresh();
    refreshLog();

}
void MainWindow::on_tableView_teknikServis_clicked(const QModelIndex &index)
{
    //QString value = ui->tableView_teknikServis->model()->data(index).toString();
    int row = ui->tableView_teknikServis->currentIndex().row();
    QString rowValue = ui->tableView_teknikServis->model()->data(ui->tableView_teknikServis->model()->index(row,0)).toString();

    rowCount = rowValue;

}
void MainWindow::on_tableView_teknikServis_doubleClicked(const QModelIndex &index)
{
    //QString value = ui->tableView_teknikServis->model()->data(index).toString();
    int row = ui->tableView_teknikServis->currentIndex().row();
    QString rowValue = ui->tableView_teknikServis->model()->data(ui->tableView_teknikServis->model()->index(row,0)).toString();

    //serviceValue = value;
    rowCount = rowValue;

    ServisGetDialog *servisDialog = new ServisGetDialog();
    servisDialog->initialize(rowCount, database);
    servisDialog->exec();
    refreshServis();
}

void MainWindow::on_pushButton_clicked()
{
    Musteri *musteri = new Musteri();
    musteri->initialize(database);
    musteri->show();
}
void MainWindow::refresh() {
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
        ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    }else {
        QMessageBox::information(this, "Not Connected", database.lastError().text());
        cout << "Database not connected!" << endl;
    }
}

void MainWindow::refreshLog() {
    QSqlQuery* qry = new QSqlQuery(database);
    QSqlQueryModel * modalLog = new QSqlQueryModel();

    qry ->prepare("select * from loglar where `Cihaz Seri No` = " + mainWindowValue);
    qry -> exec();
    modalLog->setQuery(*qry);
    ui->tableView_log->setModel(modalLog);
    ui->tableView_log->resizeColumnsToContents();
    ui->tableView_log->resizeRowsToContents();
    ui->tableView_log->hideColumn(0);
    ui->tableView_log->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}
void MainWindow::resizeEvent(QResizeEvent* event) {

    QMainWindow::resizeEvent(event);
        ui->tableView_teknikServis->setColumnWidth(2,150);
        ui->tableView_teknikServis->setColumnWidth(3,80);
        ui->tableView_teknikServis->setColumnWidth(4,ui->tableView_teknikServis->width()-230);

}
void MainWindow::refreshServis() {
    QSqlQueryModel * modal = new QSqlQueryModel();

    if(database.open()) {

        QSqlQuery* qry = new QSqlQuery(database);

        qry ->prepare("select * from teknikservis where `Cihaz Seri No` = " + mainWindowValue + " ORDER BY Tarih DESC;");
        qry -> exec();
        modal->setQuery(*qry);
        ui->tableView_teknikServis->setModel(modal);
        ui->tableView_teknikServis->resizeColumnsToContents();
        ui->tableView_teknikServis->resizeRowsToContents();
        foreach(int col, columnsToHideService)
            ui->tableView_teknikServis->hideColumn(col);
        //ui->tableView_teknikServis->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        ui->tableView_teknikServis->setColumnWidth(2,150);
        ui->tableView_teknikServis->setColumnWidth(3,80);
        ui->tableView_teknikServis->setColumnWidth(4,ui->tableView_teknikServis->width()-230);
    }
}

void MainWindow::on_pushButton_modemTipi_clicked()
{
    ToolBarDialog *toolbar = new ToolBarDialog();
    toolbar->initialize(database, ui->pushButton_modemTipi->text(), "modemtipi");
    toolbar->show();
}


void MainWindow::on_pushButton_Model_clicked()
{
    ToolBarDialog *toolbar = new ToolBarDialog();
    toolbar->initialize(database, ui->pushButton_Model->text(), "model");
    toolbar->show();
}


void MainWindow::on_lineEdit_selectionChanged()
{
    ui->lineEdit->setText("");
    ui->lineEdit->setReadOnly(0);
}


void MainWindow::on_splitter_splitterMoved(int pos, int index)
{
    ui->tableView_teknikServis->setColumnWidth(2,150);
    ui->tableView_teknikServis->setColumnWidth(3,80);
    ui->tableView_teknikServis->setColumnWidth(4,ui->tableView_teknikServis->width()-230);
}


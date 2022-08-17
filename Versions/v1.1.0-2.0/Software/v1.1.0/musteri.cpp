#include "musteri.h"
#include "ui_musteri.h"
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QMessageBox>
#include <QSqlError>
#include "informationmusteridialog.h"
#include <QTime>
#include "musteriekle.h"

#include <iostream>
using namespace std;

Musteri::Musteri(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Musteri)
{
    ui->setupUi(this);
    ui->lineEditSort->setPlaceholderText("Filtrele");
    ui->lineEditSort->setReadOnly(1);
}
void Musteri::setLog(QString content) {

    QSqlQuery qry;
    QString date = QDateTime::currentDateTime().toString("dd.MM.yyyy hh:mm:ss");
    qry.prepare("INSERT INTO processlogs(`tarih`,`username`,`process`) VALUES (:tarih,:username,:process)");
    qry.bindValue(":tarih",date);
    qry.bindValue(":username",username);
    qry.bindValue(":process",content);
    qry.exec();
}
void Musteri::initialize(QSqlDatabase d, QString user) {
    database = d;
    username = user;

    QSqlQueryModel * modal = new QSqlQueryModel();
    if(database.isOpen()) {

        QSqlQuery* qry = new QSqlQuery(database);

        qry ->prepare("select * from `müsteri`");
        if(qry -> exec()){
            setLog("[NOTE] musteri.cpp : musteri tablosu yükleniyor");
        }else {
            setLog("[ERROR] musteri.cpp : " + qry->lastError().text());
        }
        modal->setQuery(*qry);
        ui->tableView->setModel(modal);
        ui->tableView->hideColumn(0);
        ui->tableView->resizeRowsToContents();
        ui->tableView->resizeColumnsToContents();
        ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        ui->tableView->horizontalHeader()->setStyleSheet("QHeaderView { font-size: 18pt; color:#002B5B; font-weight: bold; }");
    }else {
        QMessageBox::information(this, "Not Connected", "Database Is Not Connected");
        setLog("[ERROR] musteri.cpp : " + database.lastError().text());
        cout << "Database not connected!" << endl;
    }
}

Musteri::~Musteri()
{
    delete ui;
}

void Musteri::on_lineEditSort_selectionChanged()
{
    ui->lineEditSort->setText("");
    ui->lineEditSort->setReadOnly(0);
}
void Musteri::on_lineEditSort_textChanged(const QString &arg1)
{
    QSqlQueryModel *model = new QSqlQueryModel();

    if(database.isOpen()) {
        QSqlQuery* qry = new QSqlQuery(database);

        qry ->prepare("select * from müsteri where `İsim` LIKE '" + arg1 + "%' OR LOWER(`İsim`) LIKE '" + arg1.toLower() + "%';");
        qry -> exec();
        model->setQuery(*qry);
        ui->tableView->setModel(model);
        ui->tableView->resizeColumnsToContents();
        ui->tableView->resizeRowsToContents();
        ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    }else {
        QMessageBox::information(this, "Not Connected", database.lastError().text());
        setLog("[ERROR] musteri.cpp : " + database.lastError().text());
        cout << "Database not connected!" << endl;
    }
}
void Musteri::on_pushButton_clicked()
{
    MusteriEkle *musteriEkle = new MusteriEkle();
    musteriEkle->initialize(database, username);
    musteriEkle->exec();
    refresh();
}
void Musteri::refresh() {
    QSqlQueryModel *model = new QSqlQueryModel();

    if(database.isOpen()) {
        QSqlQuery* qry = new QSqlQuery(database);

        qry ->prepare("select * from müsteri");
        qry -> exec();
        model->setQuery(*qry);
        ui->tableView->setModel(model);
        ui->tableView->resizeColumnsToContents();
        ui->tableView->resizeRowsToContents();
        ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    }else {
        QMessageBox::information(this, "Not Connected", database.lastError().text());
        setLog("[ERROR] musteri.cpp : " + database.lastError().text());
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

        qry ->prepare("select * from müsteri");
        if(qry->exec()) {
            setLog("[NOTE] musteri.cpp musteri silindi!!");
        }else {
            setLog("[ERROR] musteri.cpp : " + qry->lastError().text());
        }
        model->setQuery(*qry);
        ui->tableView->setModel(model);
        ui->tableView->resizeColumnsToContents();
        ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    }else {
        QMessageBox::information(this, "Not Connected", database.lastError().text());
        setLog("[ERROR] musteri.cpp : " + database.lastError().text());
        cout << "Database not connected!" << endl;
    }
}


void Musteri::on_tableView_doubleClicked(const QModelIndex &index)
{
    int row = ui->tableView->currentIndex().row();
    QString rowValue = ui->tableView->model()->data(ui->tableView->model()->index(row,0)).toString();


    seriNo = rowValue;

    InformationMusteriDialog *musteriDialog = new InformationMusteriDialog();
    musteriDialog->initialize(database, seriNo, username);
    musteriDialog->exec();
    refresh();
}


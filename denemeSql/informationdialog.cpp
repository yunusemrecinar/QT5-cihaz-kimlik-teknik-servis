#include "informationdialog.h"
#include "ui_informationdialog.h"
#include "mainwindow.h"
#include <iostream>
using namespace std;

InformationDialog::InformationDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::InformationDialog)
{
    ui->setupUi(this);

    MainWindow w;
    //ui->inf->setText("21");

    //ui->inf->setText(w.getLabel());
/*
    database = QSqlDatabase::addDatabase("QMYSQL");
    database.setHostName("localhost");
    database.setUserName("root");
    database.setPassword("");
    database.setDatabaseName("modeo");


    if(database.open()) {

        QSqlQuery* qry = new QSqlQuery(database);

        qry ->prepare("select * from cihazkimlik where Model = '" +ui->inf->text() +"'");
        QMessageBox::information(this, "Not Connected", ui->inf->text());
        if(qry->exec()) {
            while(qry->next()) {
                ui->model_->setText(qry->value(0).toString());

            }
        }else {
            QMessageBox::critical(this, tr("error::"), qry->lastError().text());
        }
        //qDebug() << (modal->rowCount());


    }else {
        QMessageBox::information(this, "Not Connected", "Database Is Not Connected");
        cout << "Database not connected!" << endl;
    }
    database.close();*/



}



InformationDialog::~InformationDialog()
{
    delete ui;
}
void InformationDialog::initialize(QString s) {
    //ui->inf->setText(s);
    database = QSqlDatabase::addDatabase("QMYSQL");
    database.setHostName("localhost");
    database.setUserName("root");
    database.setPassword("");
    database.setDatabaseName("modeo");


    if(database.open()) {

        QSqlQuery* qry = new QSqlQuery(database);

        qry ->prepare("select * from cihazkimlik where `Cihaz Seri No` = '" + s + "'");

        if(qry->exec()) {
            while(qry->next()) {
                ui->model_->setText(qry->value(0).toString());
                ui->cihaz_seri_no->setText(qry->value(1).toString());
                ui->anakart_->setText(qry->value(2).toString());
                ui->modem_karti_->setText(qry->value(3).toString());
                ui->lcd_karti_->setText(qry->value(4).toString());
                ui->sarj_karti_->setText(qry->value(5).toString());
                ui->durum_->setText(qry->value(6).toString());
                ui->modemSeri1_->setText(qry->value(7).toString());
                ui->modemSeri2_->setText(qry->value(8).toString());
                ui->modemSeri3_->setText(qry->value(9).toString());
                ui->modemSeri5_->setText(qry->value(10).toString());
                ui->modemSeri6_->setText(qry->value(11).toString());
                ui->date_->setText(qry->value(12).toString());
                ui->test_durum_->setText(qry->value(13).toString());
                ui->degisenParcalar_->setText(qry->value(14).toString());
                ui->notlar_->setText(qry->value(15).toString());
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
/*
void InformationDialog::onMessageSent(const QString & message) {
    cout << "Data sent!" << endl;
    ui->inf->setText(message);
}*/


/*
void InformationDialog::on_btnLauncher_clicked() {
    if(_mainWindow) {
        _mainWindow = new MainWindow(this);


        connect(_mainWindow,&MainWindow::notifyMessageSent,
                this,&InformationDialog::onMessageSent);
    }
    _mainWindow->show();
}
*/

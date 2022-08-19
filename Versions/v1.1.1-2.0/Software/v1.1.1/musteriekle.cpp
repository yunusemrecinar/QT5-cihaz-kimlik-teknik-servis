#include "musteriekle.h"
#include "ui_musteriekle.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QTime>
#include <QMessageBox>
#include <QSqlError>

MusteriEkle::MusteriEkle(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MusteriEkle)
{
    ui->setupUi(this);
}

MusteriEkle::~MusteriEkle()
{
    delete ui;
}

void MusteriEkle::initialize(QSqlDatabase d, QString user)
{
    database = d;
    username = user;
}

void MusteriEkle::on_pushButton_clicked()
{
    if(database.isOpen()) {
        QString isim = ui->isim_->text();
        QString adres = ui->adres_->toPlainText();

        QSqlQuery qry;

        qry.prepare("INSERT INTO müsteri(`İsim`,`Adres`) VALUES(:isim,:adres);");
        qry.bindValue(":isim",isim);
        qry.bindValue(":adres",adres);

        if(qry.exec()) {
            setLog("[NOTE] musteriekle.cpp : " + isim + " adlı müşteri eklendi.");
            this->close();
        }else {
            QMessageBox::information(this,"Error", qry.lastError().text());
            setLog("[ERROR] musteriekle.cpp : " + qry.lastError().text());
        }
    }else {
        QMessageBox::information(this,"Error", database.lastError().text());
        setLog("[ERROR] musteriekle.cpp : " + database.lastError().text());
    }
}

void MusteriEkle::setLog(QString content)
{
    QSqlQuery qry;
    QString date = QDateTime::currentDateTime().toString("dd.MM.yyyy hh:mm:ss");
    qry.prepare("INSERT INTO processlogs(`tarih`,`username`,`process`) VALUES (:tarih,:username,:process)");
    qry.bindValue(":tarih",date);
    qry.bindValue(":username",username);
    qry.bindValue(":process",content);
    qry.exec();
}


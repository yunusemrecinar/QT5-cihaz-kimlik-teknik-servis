#include "servergetdialog.h"
#include "ui_servergetdialog.h"
#include <QDate>
#include <QSqlQuery>
#include <QSqlDatabase>
#include <QSqlError>
#include <QMessageBox>

#include <iostream>
using namespace std;

ServerGetDialog::ServerGetDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ServerGetDialog)
{
    ui->setupUi(this);
    changes();
}

ServerGetDialog::~ServerGetDialog()
{
    delete ui;
}

void ServerGetDialog::initialize(QString index, QSqlDatabase d, QString user)
{
    indexValue = index;
    database = d;
    username = user;

    if(database.open()) {

        QSqlQuery* qry = new QSqlQuery(database);

        qry ->prepare("select * from teknikservis where `Sıra` = '" + indexValue +"'");

        if(qry->exec()) {
            while(qry->next()) {
                seriNo = qry->value(1).toString();
                ui->teknikServis->setText("Teknik Servis (" + seriNo + ")");

                if(qry->value(2).toString().contains(" ")) {
                    QList<QString> dateTime = qry->value(2).toString().split(" ");

                    QList<QString> date = dateTime.at(0).split(".");
                    ui->gelisTarihiDay_->setValue(date.at(0).toInt());
                    ui->gelisTarihiMonth_->setValue(date.at(1).toInt());
                    ui->gelisTarihiYear_->setValue(date.at(2).toInt());

                    QList<QString> time = dateTime.at(1).split(":");
                    ui->tarih_saat->setValue(time.at(0).toInt());
                    ui->tarih_dakika->setValue(time.at(1).toInt());

                }
                ui->olay_->setCurrentText(qry->value(3).toString());
                ui->yapilanIslem_->setText(qry->value(4).toString());
                QList<QString> list = qry->value(5).toString().split(",");
                int length = 0;
                for(int i = 0; i < list.size(); i++) {
                    length = list.at(i).length();
                    if(list.at(i).left(length-1).contains(ui->donanim_1->text())) {
                        ui->donanim_1->setChecked(true);
                        ui->donanim_1Num->setVisible(true);
                        ui->donanim_1Num->setValue(list.at(i).right(1).toInt());
                    }else if(list.at(i).left(length-1).contains(ui->donanim_2->text())) {
                        ui->donanim_2->setChecked(true);
                        ui->donanim_2Num->setVisible(true);
                        ui->donanim_2Num->setValue(list.at(i).right(1).toInt());
                    }else if(list.at(i).left(length-1).contains(ui->donanim_3->text())) {
                        ui->donanim_3->setChecked(true);
                        ui->donanim_3Num->setVisible(true);
                        ui->donanim_3Num->setValue(list.at(i).right(1).toInt());
                    }
                }


                QList<QString> degisenParcalarList = qry->value(6).toString().split(",");

                ui->testSuresi_->setValue(qry->value(7).toInt());

                ui->notlar_->setText(qry->value(8).toString());
            }
        }else {
            setLog("[ERROR] servergetdialog.cpp : " + qry->lastError().text());
        }


    }else {
        QMessageBox::information(this, "Not Connected", "Database Is Not Connected servisget");
        setLog("[ERROR] servergetdialog.cpp : " + database.lastError().text());
        cout << "Database not connected!" << endl;
    }
}
void ServerGetDialog::setLog(QString content) {

    QSqlQuery qry;
    QString date = QDateTime::currentDateTime().toString("dd.MM.yyyy hh:mm:ss");
    qry.prepare("INSERT INTO processlogs(`tarih`,`username`,`process`) VALUES (:tarih,:username,:process)");
    qry.bindValue(":tarih",date);
    qry.bindValue(":username",username);
    qry.bindValue(":process",content);
    qry.exec();
}
void ServerGetDialog::commandChangedOlay(const QString& command_text) {
    olay = command_text;
}

void ServerGetDialog::changes() {
    ui->gelisTarihiDay_->setMaximum(31);
    ui->gelisTarihiDay_->setMinimum(1);
    ui->gelisTarihiDay_->setButtonSymbols(QAbstractSpinBox::NoButtons);
    ui->gelisTarihiMonth_->setButtonSymbols(QAbstractSpinBox::NoButtons);
    ui->gelisTarihiMonth_->setMaximum(12);
    ui->gelisTarihiMonth_->setMinimum(1);
    ui->gelisTarihiYear_->setButtonSymbols(QAbstractSpinBox::NoButtons);
    ui->gelisTarihiYear_->setMaximum(QDate::currentDate().year());
    ui->gelisTarihiYear_->setMinimum(1);
    ui->gelisTarihiDay_->clear();
    ui->gelisTarihiMonth_->clear();
    ui->gelisTarihiYear_->clear();

    ui->tarih_dakika->setMaximum(59);
    ui->tarih_dakika->setMinimum(0);
    ui->tarih_dakika->setButtonSymbols(QAbstractSpinBox::NoButtons);
    ui->tarih_saat->setMaximum(23);
    ui->tarih_saat->setMinimum(0);
    ui->tarih_saat->setButtonSymbols(QAbstractSpinBox::NoButtons);

    QStringList commandsOlay = {"Geldi","Test","Gitti","Onarıldı"};
    ui->olay_->addItems(commandsOlay);
    connect(ui->olay_, &QComboBox::currentTextChanged, this, &ServerGetDialog::commandChangedOlay);

    ui->donanim_1Num->setButtonSymbols(QAbstractSpinBox::NoButtons);
    ui->donanim_2Num->setButtonSymbols(QAbstractSpinBox::NoButtons);
    ui->donanim_3Num->setButtonSymbols(QAbstractSpinBox::NoButtons);
    ui->donanim_1Num->clear();
    ui->donanim_2Num->clear();
    ui->donanim_3Num->clear();
    ui->donanim_1Num->setVisible(false);
    ui->donanim_2Num->setVisible(false);
    ui->donanim_3Num->setVisible(false);
    ui->donanim_1Num->setMaximum(9);
    ui->donanim_2Num->setMaximum(9);
    ui->donanim_3Num->setMaximum(9);

    ui->testSuresi_->setButtonSymbols(QAbstractSpinBox::NoButtons);
}

void ServerGetDialog::donanimlar() {
    if(ui->donanim_1->isChecked()) {
        donanim += ui->donanim_1->text() + ui->donanim_1Num->text() + ",";
    }if(ui->donanim_2->isChecked()) {
        donanim += ui->donanim_2->text() + ui->donanim_2Num->text() + ",";
    }if(ui->donanim_3->isChecked()) {
        donanim += ui->donanim_3->text() + ui->donanim_3Num->text() + ",";
    }
}

void ServerGetDialog::on_pushButton_clicked()
{
    if(database.isOpen()) {

        QSqlQuery qry;
        QString tarih;

        QString saat;
        saat = ui->tarih_saat->text() + ":" + ui->tarih_dakika->text();
        tarih = ui->gelisTarihiDay_->text() + "." + ui->gelisTarihiMonth_->text() + "." + ui->gelisTarihiYear_->text() + " " + saat;
        olay = ui->olay_->currentText();
        QString yapilanIslem = ui->yapilanIslem_->toPlainText();
        donanimlar();
        QString testSure = ui->testSuresi_->text();
        QString notlar = ui->notlar_->toPlainText();


        qry.prepare("UPDATE teknikservis SET `Tarih` = '" + tarih + "' WHERE `Cihaz Seri No` = '" + seriNo + "' AND `Sıra` = '" + indexValue +"';");
        qry.exec();
        qry.clear();
        qry.prepare("UPDATE teknikservis SET `Olay` = '" + olay + "' WHERE `Cihaz Seri No` = '" + seriNo + "' AND `Sıra` = '" + indexValue +"';");
        qry.exec();
        qry.clear();
        qry.prepare("UPDATE teknikservis SET `Yapılan İşlem` = '" + yapilanIslem + "' WHERE `Cihaz Seri No` = '" + seriNo + "' AND `Sıra` = '" + indexValue +"';");
        qry.exec();
        qry.clear();
        qry.prepare("UPDATE teknikservis SET `Cihazla Gelen Malzemeler` = '" + donanim + "' WHERE `Cihaz Seri No` = '" + seriNo + "' AND `Sıra` = '" + indexValue +"';");
        qry.exec();
        qry.clear();
        qry.prepare("UPDATE teknikservis SET `Degisen Parcalar` = '" + degisenParcalar + "' WHERE `Cihaz Seri No` = '" + seriNo + "' AND `Sıra` = '" + indexValue +"';");
        qry.exec();
        qry.clear();
        qry.prepare("UPDATE teknikservis SET `Test Süresi` = '" + testSure + "' WHERE `Cihaz Seri No` = '" + seriNo + "' AND `Sıra` = '" + indexValue +"';");
        qry.exec();
        qry.clear();
        qry.prepare("UPDATE teknikservis SET `Notlar` = '" + notlar + "' WHERE `Cihaz Seri No` = '" + seriNo + "' AND `Sıra` = '" + indexValue +"';");


        if(qry.exec()) {
            QMessageBox::information(this,"Inserted","Data Updated Succesfully");
            setLog("[NOTE] servergetdialog.cpp :" + seriNo + " numaralı Server cihazı güncellendi");
        }else {
            QMessageBox::critical(this, tr("error::"), qry.lastError().text());
            setLog("[NOTE] servergetdialog.cpp : " + qry.lastError().text());
        }



    }else {
        QMessageBox::information(this, "Not Connected", "Database Is Not Connected");
        setLog("[ERROR] servergetdialog.cpp : " + database.lastError().text());
        cout << "Database not connected!" << endl;
    }
    this->close();
}


void ServerGetDialog::on_donanim_1_clicked()
{
    if(ui->donanim_1->isChecked()) {
        ui->donanim_1Num->setVisible(true);
    }else {
        ui->donanim_1Num->setVisible(false);
    }
}


void ServerGetDialog::on_donanim_2_clicked()
{
    if(ui->donanim_2->isChecked()) {
        ui->donanim_2Num->setVisible(true);
    }else {
        ui->donanim_2Num->setVisible(false);
    }
}


void ServerGetDialog::on_donanim_3_clicked()
{
    if(ui->donanim_3->isChecked()) {
        ui->donanim_3Num->setVisible(true);
    }else {
        ui->donanim_3Num->setVisible(false);
    }
}


#include "servisgetdialog.h"
#include "ui_servisgetdialog.h"
#include <QSqlQuery>
#include <QMessageBox>
#include <QSqlError>
#include "mainwindow.h"

#include <iostream>
using namespace std;

ServisGetDialog::ServisGetDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ServisGetDialog)
{
    ui->setupUi(this);
    this->setWindowTitle(" ");
    changes();
}

ServisGetDialog::~ServisGetDialog()
{
    delete ui;
}
void ServisGetDialog::changes() {
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
    connect(ui->olay_, &QComboBox::currentTextChanged, this, &ServisGetDialog::commandChangedOlay);

    ui->donanim_1Num->setButtonSymbols(QAbstractSpinBox::NoButtons);
    ui->donanim_2Num->setButtonSymbols(QAbstractSpinBox::NoButtons);
    ui->donanim_3Num->setButtonSymbols(QAbstractSpinBox::NoButtons);
    ui->donanim_4Num->setButtonSymbols(QAbstractSpinBox::NoButtons);
    ui->donanim_5Num->setButtonSymbols(QAbstractSpinBox::NoButtons);
    ui->donanim_6Num->setButtonSymbols(QAbstractSpinBox::NoButtons);
    ui->donanim_7Num->setButtonSymbols(QAbstractSpinBox::NoButtons);
    ui->donanim_8Num->setButtonSymbols(QAbstractSpinBox::NoButtons);
    ui->donanim_9Num->setButtonSymbols(QAbstractSpinBox::NoButtons);
    ui->donanim_10Num->setButtonSymbols(QAbstractSpinBox::NoButtons);
    ui->donanim_11Num->setButtonSymbols(QAbstractSpinBox::NoButtons);
    ui->donanim_1Num->clear();
    ui->donanim_2Num->clear();
    ui->donanim_3Num->clear();
    ui->donanim_4Num->clear();
    ui->donanim_5Num->clear();
    ui->donanim_6Num->clear();
    ui->donanim_7Num->clear();
    ui->donanim_8Num->clear();
    ui->donanim_9Num->clear();
    ui->donanim_10Num->clear();
    ui->donanim_11Num->clear();
    ui->donanim_1Num->setVisible(false);
    ui->donanim_2Num->setVisible(false);
    ui->donanim_3Num->setVisible(false);
    ui->donanim_4Num->setVisible(false);
    ui->donanim_5Num->setVisible(false);
    ui->donanim_6Num->setVisible(false);
    ui->donanim_7Num->setVisible(false);
    ui->donanim_8Num->setVisible(false);
    ui->donanim_9Num->setVisible(false);
    ui->donanim_10Num->setVisible(false);
    ui->donanim_11Num->setVisible(false);
    ui->donanim_1Num->setMaximum(9);
    ui->donanim_2Num->setMaximum(9);
    ui->donanim_3Num->setMaximum(9);
    ui->donanim_4Num->setMaximum(9);
    ui->donanim_5Num->setMaximum(9);
    ui->donanim_6Num->setMaximum(9);
    ui->donanim_7Num->setMaximum(9);
    ui->donanim_8Num->setMaximum(9);
    ui->donanim_9Num->setMaximum(9);
    ui->donanim_10Num->setMaximum(9);
    ui->donanim_11Num->setMaximum(9);


    ui->testSuresi_->setButtonSymbols(QAbstractSpinBox::NoButtons);

}
void ServisGetDialog::setLog(QString content) {

    QSqlQuery qry;
    QString date = QDateTime::currentDateTime().toString("dd.MM.yyyy hh:mm:ss");
    qry.prepare("INSERT INTO processlogs(`tarih`,`username`,`process`) VALUES (:tarih,:username,:process)");
    qry.bindValue(":tarih",date);
    qry.bindValue(":username",username);
    qry.bindValue(":process",content);
    qry.exec();
}

void ServisGetDialog::commandChangedOlay(const QString& command_text) {
    olay = command_text;
}
void ServisGetDialog::initialize(QString index, QSqlDatabase d, QString user) {

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
                    }else if(list.at(i).left(length-1).contains(ui->donanim_4->text())) {
                        ui->donanim_4->setChecked(true);
                        ui->donanim_4Num->setVisible(true);
                        ui->donanim_4Num->setValue(list.at(i).right(1).toInt());
                    }else if(list.at(i).left(length-1).contains(ui->donanim_5->text())) {
                        ui->donanim_5->setChecked(true);
                        ui->donanim_5Num->setVisible(true);
                        ui->donanim_5Num->setValue(list.at(i).right(1).toInt());
                    }else if(list.at(i).left(length-1).contains(ui->donanim_6->text())) {
                        ui->donanim_6->setChecked(true);
                        ui->donanim_6Num->setVisible(true);
                        ui->donanim_6Num->setValue(list.at(i).right(1).toInt());
                    }else if(list.at(i).left(length-1).contains(ui->donanim_7->text())) {
                        ui->donanim_7->setChecked(true);
                        ui->donanim_7Num->setVisible(true);
                        ui->donanim_7Num->setValue(list.at(i).right(1).toInt());
                    }else if(list.at(i).left(length-1).contains(ui->donanim_8->text())) {
                        ui->donanim_8->setChecked(true);
                        ui->donanim_8Num->setVisible(true);
                        ui->donanim_8Num->setValue(list.at(i).right(1).toInt());
                    }else if(list.at(i).left(length-1).contains(ui->donanim_9->text())) {
                        ui->donanim_9->setChecked(true);
                        ui->donanim_9Num->setVisible(true);
                        ui->donanim_9Num->setValue(list.at(i).right(1).toInt());
                    }else if(list.at(i).left(length-1).contains(ui->donanim_10->text())) {
                        ui->donanim_10->setChecked(true);
                        ui->donanim_10Num->setVisible(true);
                        ui->donanim_10Num->setValue(list.at(i).right(1).toInt());
                    }else if(list.at(i).left(length-1).contains(ui->donanim_11->text())) {
                        ui->donanim_11->setChecked(true);
                        ui->donanim_11Num->setVisible(true);
                        ui->donanim_11Num->setValue(list.at(i).right(1).toInt());
                    }
                }


                QList<QString> degisenParcalarList = qry->value(6).toString().split(",");

                if(degisenParcalarList.contains(ui->degisenParca_1->text())) {
                    ui->degisenParca_1->setChecked(true);
                }
                if(degisenParcalarList.contains(ui->degisenParca_2->text())) {
                    ui->degisenParca_2->setChecked(true);
                }
                if(degisenParcalarList.contains(ui->degisenParca_3->text())) {
                    ui->degisenParca_3->setChecked(true);
                }
                if(degisenParcalarList.contains(ui->degisenParca_4->text())) {
                    ui->degisenParca_4->setChecked(true);
                }
                if(degisenParcalarList.contains(ui->degisenParca_5->text())) {
                    ui->degisenParca_5->setChecked(true);
                }
                if(degisenParcalarList.contains(ui->degisenParca_6->text())) {
                    ui->degisenParca_6->setChecked(true);
                }
                if(degisenParcalarList.contains(ui->degisenParca_7->text())) {
                    ui->degisenParca_7->setChecked(true);
                }
                if(degisenParcalarList.contains(ui->degisenParca_8->text())) {
                    ui->degisenParca_8->setChecked(true);
                }
                if(degisenParcalarList.contains(ui->degisenParca_9->text())) {
                    ui->degisenParca_9->setChecked(true);
                }
                if(degisenParcalarList.contains(ui->degisenParca_10->text())) {
                    ui->degisenParca_10->setChecked(true);
                }
                if(degisenParcalarList.contains(ui->degisenParca_11->text())) {
                    ui->degisenParca_11->setChecked(true);
                }
                if(degisenParcalarList.contains(ui->degisenParca_12->text())) {
                    ui->degisenParca_12->setChecked(true);
                }

                ui->testSuresi_->setValue(qry->value(7).toInt());

                ui->notlar_->setText(qry->value(8).toString());
            }
        }else {
            setLog("[ERROR] servisgetdialog.cpp : " + qry->lastError().text());
        }


    }else {
        QMessageBox::information(this, "Not Connected", "Database Is Not Connected servisget");
        setLog("[ERROR] servisgetdialog.cpp : " + database.lastError().text());
        cout << "Database not connected!" << endl;
    }

}

void ServisGetDialog::donanimlar() {
    if(ui->donanim_1->isChecked()) {
        donanim += ui->donanim_1->text() + ui->donanim_1Num->text() + ",";
    }if(ui->donanim_2->isChecked()) {
        donanim += ui->donanim_2->text() + ui->donanim_2Num->text() + ",";
    }if(ui->donanim_3->isChecked()) {
        donanim += ui->donanim_3->text() + ui->donanim_3Num->text() + ",";
    }if(ui->donanim_4->isChecked()) {
        donanim += ui->donanim_4->text() + ui->donanim_4Num->text() + ",";
    }if(ui->donanim_5->isChecked()) {
        donanim += ui->donanim_5->text() + ui->donanim_5Num->text() + ",";
    }if(ui->donanim_6->isChecked()) {
        donanim += ui->donanim_6->text() + ui->donanim_6Num->text() + ",";
    }if(ui->donanim_7->isChecked()) {
        donanim += ui->donanim_7->text() + ui->donanim_7Num->text() + ",";
    }if(ui->donanim_8->isChecked()) {
        donanim += ui->donanim_8->text() + ui->donanim_8Num->text() + ",";
    }if(ui->donanim_9->isChecked()) {
        donanim += ui->donanim_9->text() + ui->donanim_9Num->text() + ",";
    }if(ui->donanim_10->isChecked()) {
        donanim += ui->donanim_10->text() + ui->donanim_10Num->text() + ",";
    }if(ui->donanim_11->isChecked()) {
        donanim += ui->donanim_11->text() + ui->donanim_11Num->text();
    }
}
void ServisGetDialog::degisenParca() {
    if(ui->degisenParca_1->isChecked())
        degisenParcalar += ui->degisenParca_1->text() +  ",";
    if(ui->degisenParca_2->isChecked())
        degisenParcalar += ui->degisenParca_2->text() + ",";
    if(ui->degisenParca_3->isChecked())
        degisenParcalar += ui->degisenParca_3->text() + ",";
    if(ui->degisenParca_4->isChecked())
        degisenParcalar += ui->degisenParca_4->text() + ",";
    if(ui->degisenParca_5->isChecked())
        degisenParcalar += ui->degisenParca_5->text() + ",";
    if(ui->degisenParca_6->isChecked())
        degisenParcalar += ui->degisenParca_6->text() + ",";
    if(ui->degisenParca_7->isChecked())
        degisenParcalar += ui->degisenParca_7->text() + ",";
    if(ui->degisenParca_8->isChecked())
        degisenParcalar += ui->degisenParca_8->text() + ",";
    if(ui->degisenParca_9->isChecked())
        degisenParcalar += ui->degisenParca_9->text() + ",";
    if(ui->degisenParca_10->isChecked())
        degisenParcalar += ui->degisenParca_10->text() + ",";
    if(ui->degisenParca_11->isChecked())
        degisenParcalar += ui->degisenParca_11->text() + ",";
    if(ui->degisenParca_12->isChecked())
        degisenParcalar += ui->degisenParca_12->text() + ",";
}
void ServisGetDialog::on_pushButton_clicked()
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
        degisenParca();
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
            setLog("[NOTE] servisgetdialog.cpp :" + seriNo + "numaralı cihazın servisi güncellendi");
        }else {
            QMessageBox::critical(this, tr("error::"), qry.lastError().text());
            setLog("[ERROR] servisgetdialog.cpp : " + qry.lastError().text());
        }

    }else {
        QMessageBox::information(this, "Not Connected", "Database Is Not Connected");
        setLog("[ERROR] servisgetdialog.cpp : " + database.lastError().text());
        cout << "Database not connected!" << endl;
    }
    this->close();

}

void ServisGetDialog::on_donanim_1_clicked()
{
    if(ui->donanim_1->isChecked()) {
        ui->donanim_1Num->setVisible(true);
    }else {
        ui->donanim_1Num->setVisible(false);
    }
}


void ServisGetDialog::on_donanim_2_clicked()
{
    if(ui->donanim_2->isChecked()) {
        ui->donanim_2Num->setVisible(true);
    }else {
        ui->donanim_2Num->setVisible(false);
    }
}


void ServisGetDialog::on_donanim_3_clicked()
{
    if(ui->donanim_3->isChecked()) {
        ui->donanim_3Num->setVisible(true);
    }else {
        ui->donanim_3Num->setVisible(false);
    }
}


void ServisGetDialog::on_donanim_4_clicked()
{
    if(ui->donanim_4->isChecked()) {
        ui->donanim_4Num->setVisible(true);
    }else {
        ui->donanim_4Num->setVisible(false);
    }
}


void ServisGetDialog::on_donanim_8_clicked()
{
    if(ui->donanim_8->isChecked()) {
        ui->donanim_8Num->setVisible(true);
    }else {
        ui->donanim_8Num->setVisible(false);
    }
}


void ServisGetDialog::on_donanim_7_clicked()
{
    if(ui->donanim_7->isChecked()) {
        ui->donanim_7Num->setVisible(true);
    }else {
        ui->donanim_7Num->setVisible(false);
    }
}


void ServisGetDialog::on_donanim_9_clicked()
{
    if(ui->donanim_9->isChecked()) {
        ui->donanim_9Num->setVisible(true);
    }else {
        ui->donanim_9Num->setVisible(false);
    }
}


void ServisGetDialog::on_donanim_5_clicked()
{
    if(ui->donanim_5->isChecked()) {
        ui->donanim_5Num->setVisible(true);
    }else {
        ui->donanim_5Num->setVisible(false);
    }
}


void ServisGetDialog::on_donanim_6_clicked()
{
    if(ui->donanim_6->isChecked()) {
        ui->donanim_6Num->setVisible(true);
    }else {
        ui->donanim_6Num->setVisible(false);
    }
}


void ServisGetDialog::on_donanim_11_clicked()
{
    if(ui->donanim_11->isChecked()) {
        ui->donanim_11Num->setVisible(true);
    }else {
        ui->donanim_11Num->setVisible(false);
    }
}


void ServisGetDialog::on_donanim_10_clicked()
{
    if(ui->donanim_10->isChecked()) {
        ui->donanim_10Num->setVisible(true);
    }else {
        ui->donanim_10Num->setVisible(false);
    }
}


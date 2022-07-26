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
}

void ServisGetDialog::commandChangedOlay(const QString& command_text) {
    olay = command_text;
}
void ServisGetDialog::initialize(QString index, QSqlDatabase d) {
    //key = s;
    indexValue = index;
    database = d;

    if(database.open()) {

        QSqlQuery* qry = new QSqlQuery(database);

        qry ->prepare("select * from teknikservis where `Sıra` = '" + indexValue +"'");

        if(qry->exec()) {
            while(qry->next()) {
                ui->servisNo_->setText(qry->value(1).toString());

                if(qry->value(2).toString().contains(".")) {
                    QList<QString> date = qry->value(2).toString().split(".");
                    ui->gelisTarihiDay_->setValue(date.at(0).toInt());
                    ui->gelisTarihiMonth_->setValue(date.at(1).toInt());
                    ui->gelisTarihiYear_->setValue(date.at(2).toInt());
                }
                if(qry->value(3).toString().contains(":")) {
                    QList<QString> time = qry->value(3).toString().split(":");
                    ui->tarih_saat->setValue(time.at(0).toInt());
                    ui->tarih_dakika->setValue(time.at(1).toInt());
                }
                ui->musteriAdi_->setText(qry->value(4).toString());
                ui->olay_->setCurrentText(qry->value(5).toString());
                ui->arizaTanimi_->setText(qry->value(6).toString());
                ui->yapilanIslem_->setText(qry->value(7).toString());
                QList<QString> list = qry->value(8).toString().split(",");
                if(list.contains(ui->donanim_1->text())) {
                    ui->donanim_1->setChecked(true);
                }
                if(list.contains(ui->donanim_2->text())) {
                    ui->donanim_2->setChecked(true);
                }
                if(list.contains(ui->donanim_3->text())) {
                    ui->donanim_3->setChecked(true);
                }
                if(list.contains(ui->donanim_4->text())) {
                    ui->donanim_4->setChecked(true);
                }
                if(list.contains(ui->donanim_5->text())) {
                    ui->donanim_5->setChecked(true);
                }
                if(list.contains(ui->donanim_6->text())) {
                    ui->donanim_6->setChecked(true);
                }
                if(list.contains(ui->donanim_7->text())) {
                    ui->donanim_7->setChecked(true);
                }
                if(list.contains(ui->donanim_8->text())) {
                    ui->donanim_8->setChecked(true);
                }
                if(list.contains(ui->donanim_9->text())) {
                    ui->donanim_9->setChecked(true);
                }
                if(list.contains(ui->donanim_10->text())) {
                    ui->donanim_10->setChecked(true);
                }
                if(list.contains(ui->donanim_11->text())) {
                    ui->donanim_11->setChecked(true);
                }

                QList<QString> degisenParcalarList = qry->value(9).toString().split(",");

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

                ui->testSuresi_->setValue(qry->value(10).toInt());

                ui->notlar_->setText(qry->value(11).toString());
            }
        }else {
            QMessageBox::critical(this, tr("error::"), qry->lastError().text());
        }

    }else {
        QMessageBox::information(this, "Not Connected", "Database Is Not Connected servisget");
        cout << "Database not connected!" << endl;
    }

}

void ServisGetDialog::donanimlar() {
    if(ui->donanim_1->isChecked()) {
        donanim += ui->donanim_1->text() + ",";
    }if(ui->donanim_2->isChecked()) {
        donanim += ui->donanim_2->text() + ",";
    }if(ui->donanim_3->isChecked()) {
        donanim += ui->donanim_3->text() + ",";
    }if(ui->donanim_4->isChecked()) {
        donanim += ui->donanim_4->text() + ",";
    }if(ui->donanim_5->isChecked()) {
        donanim += ui->donanim_5->text() + ",";
    }if(ui->donanim_6->isChecked()) {
        donanim += ui->donanim_6->text() + ",";
    }if(ui->donanim_7->isChecked()) {
        donanim += ui->donanim_7->text() + ",";
    }if(ui->donanim_8->isChecked()) {
        donanim += ui->donanim_8->text() + ",";
    }if(ui->donanim_9->isChecked()) {
        donanim += ui->donanim_9->text() + ",";
    }if(ui->donanim_10->isChecked()) {
        donanim += ui->donanim_10->text() + ",";
    }if(ui->donanim_11->isChecked()) {
        donanim += ui->donanim_11->text();
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
        tarih = ui->gelisTarihiDay_->text() + "." + ui->gelisTarihiMonth_->text() + "." + ui->gelisTarihiYear_->text();
        QString saat;
        saat = ui->tarih_saat->text() + ":" + ui->tarih_dakika->text();
        QString musteriAdi = ui->musteriAdi_->text();
        olay = ui->olay_->currentText();
        QString arizaTarif = ui->arizaTanimi_->toPlainText();
        QString yapilanIslem = ui->yapilanIslem_->toPlainText();
        donanimlar();
        degisenParca();
        QString testSure = ui->testSuresi_->text();
        QString notlar = ui->notlar_->toPlainText();


        qry.prepare("UPDATE teknikservis SET `Tarih` = '" + tarih + "' WHERE `Cihaz Seri No` = '" + ui->servisNo_->text() + "' AND `Sıra` = '" + indexValue +"';");
        qry.exec();
        qry.clear();
        qry.prepare("UPDATE teknikservis SET `Saat` = '" + saat + "' WHERE `Cihaz Seri No` = '" + ui->servisNo_->text() + "' AND `Sıra` = '" + indexValue +"';");
        qry.exec();
        qry.clear();
        qry.prepare("UPDATE teknikservis SET `Müşteri Adı` = '" + musteriAdi + "' WHERE `Cihaz Seri No` = '" + ui->servisNo_->text() + "' AND `Sıra` = '" + indexValue +"';");
        qry.exec();
        qry.clear();
        qry.prepare("UPDATE teknikservis SET `Olay` = '" + olay + "' WHERE `Cihaz Seri No` = '" + ui->servisNo_->text() + "' AND `Sıra` = '" + indexValue +"';");
        qry.exec();
        qry.clear();
        qry.prepare("UPDATE teknikservis SET `Arıza Tarifi` = '" + arizaTarif + "' WHERE `Cihaz Seri No` = '" + ui->servisNo_->text() + "' AND `Sıra` = '" + indexValue +"';");
        qry.exec();
        qry.clear();
        qry.prepare("UPDATE teknikservis SET `Yapılan İşlem` = '" + yapilanIslem + "' WHERE `Cihaz Seri No` = '" + ui->servisNo_->text() + "' AND `Sıra` = '" + indexValue +"';");
        qry.exec();
        qry.clear();
        qry.prepare("UPDATE teknikservis SET `Cihazla Gelen Malzemeler` = '" + donanim + "' WHERE `Cihaz Seri No` = '" + ui->servisNo_->text() + "' AND `Sıra` = '" + indexValue +"';");
        qry.exec();
        qry.clear();
        qry.prepare("UPDATE teknikservis SET `Degisen Parcalar` = '" + degisenParcalar + "' WHERE `Cihaz Seri No` = '" + ui->servisNo_->text() + "' AND `Sıra` = '" + indexValue +"';");
        qry.exec();
        qry.clear();
        qry.prepare("UPDATE teknikservis SET `Test Süresi` = '" + testSure + "' WHERE `Cihaz Seri No` = '" + ui->servisNo_->text() + "' AND `Sıra` = '" + indexValue +"';");
        qry.exec();
        qry.clear();
        qry.prepare("UPDATE teknikservis SET `Notlar` = '" + notlar + "' WHERE `Cihaz Seri No` = '" + ui->servisNo_->text() + "' AND `Sıra` = '" + indexValue +"';");


        if(qry.exec()) {
            QMessageBox::information(this,"Inserted","Data Updated Succesfully");
        }else {
            QMessageBox::critical(this, tr("error::"), qry.lastError().text());
        }



    }else {
        QMessageBox::information(this, "Not Connected", "Database Is Not Connected");
        cout << "Database not connected!" << endl;
    }
    //database.close();
    this->close();

}


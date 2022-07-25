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
}

ServisGetDialog::~ServisGetDialog()
{
    delete ui;
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
                ui->servisNo_1->setText(qry->value(1).toString()); 
                ui->gelisTarihi_1->setText(qry->value(2).toString());
                ui->musteriAdi_1->setText(qry->value(3).toString());
                ui->arizaTanimi_1->setText(qry->value(4).toString());
                ui->yapilanIslem_1->setText(qry->value(5).toString());
                QList<QString> list = qry->value(6).toString().split(",");
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

                ui->bitisTarihi1->setText(qry->value(7).toString());
                ui->testSuresi_1->setText(qry->value(8).toString());
                ui->sevkTarihi_1->setText(qry->value(9).toString());
                ui->notlar_->setText(qry->value(10).toString());
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
void ServisGetDialog::on_pushButton_2_clicked()
{

    if(database.isOpen()) {

        QSqlQuery qry;
        QString gelis = ui->gelisTarihi_1->text();
        QString musteriAdi = ui->musteriAdi_1->text();
        QString arizaTarif = ui->arizaTanimi_1->text();
        QString yapilanIslem = ui->yapilanIslem_1->text();
        QString bitis = ui->bitisTarihi1->text();
        QString sevk = ui->sevkTarihi_1->text();
        QString testSure = ui->testSuresi_1->text();
        donanimlar();
        QString notlar = ui->notlar_->toPlainText();


        qry.prepare("UPDATE teknikservis SET `Geliş Tarihi` = '" + gelis + "' WHERE `Cihaz Seri No` = '" + ui->servisNo_1->text() + "' AND `Sıra` = '" + indexValue +"';");
        qry.exec();
        qry.clear();
        qry.prepare("UPDATE teknikservis SET `Müşteri Adı` = '" + musteriAdi + "' WHERE `Cihaz Seri No` = '" + ui->servisNo_1->text() + "' AND `Sıra` = '" + indexValue +"';");
        qry.exec();
        qry.clear();
        qry.prepare("UPDATE teknikservis SET `Arıza Tarifi` = '" + arizaTarif + "' WHERE `Cihaz Seri No` = '" + ui->servisNo_1->text() + "' AND `Sıra` = '" + indexValue +"';");
        qry.exec();
        qry.clear();
        qry.prepare("UPDATE teknikservis SET `Yapılan İşlem` = '" + yapilanIslem + "' WHERE `Cihaz Seri No` = '" + ui->servisNo_1->text() + "' AND `Sıra` = '" + indexValue +"';");
        qry.exec();
        qry.clear();
        qry.prepare("UPDATE teknikservis SET `Cihazla Gelen Malzemeler` = '" + donanim + "' WHERE `Cihaz Seri No` = '" + ui->servisNo_1->text() + "' AND `Sıra` = '" + indexValue +"';");
        qry.exec();
        qry.clear();
        qry.prepare("UPDATE teknikservis SET `Tamir Bitiş Tarihi` = '" + bitis + "' WHERE `Cihaz Seri No` = '" + ui->servisNo_1->text() + "' AND `Sıra` = '" + indexValue +"';");
        qry.exec();
        qry.clear();
        qry.prepare("UPDATE teknikservis SET `Test Süresi` = '" + testSure + "' WHERE `Cihaz Seri No` = '" + ui->servisNo_1->text() + "' AND `Sıra` = '" + indexValue +"';");
        qry.exec();
        qry.clear();
        qry.prepare("UPDATE teknikservis SET `Sevk Tarihi` = '" + sevk + "' WHERE `Cihaz Seri No` = '" + ui->servisNo_1->text() + "' AND `Sıra` = '" + indexValue +"';");
        qry.exec();
        qry.clear();
        qry.prepare("UPDATE teknikservis SET `Notlar` = '" + notlar + "' WHERE `Cihaz Seri No` = '" + ui->servisNo_1->text() + "' AND `Sıra` = '" + indexValue +"';");


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


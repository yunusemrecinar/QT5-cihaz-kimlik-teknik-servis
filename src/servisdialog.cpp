#include "servisdialog.h"
#include "ui_servisdialog.h"
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlError>
#include <QVBoxLayout>
#include "notekledialog.h"
#include <QMenu>
#include "mainwindow.h"

ServisDialog::ServisDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ServisDialog)
{
    ui->setupUi(this);
    this->setWindowTitle(" ");
    changes();



}
void ServisDialog::changes() {
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
    ui->gelisTarihiDay_->setValue(QDate::currentDate().day());
    ui->gelisTarihiMonth_->setValue(QDate::currentDate().month());
    ui->gelisTarihiYear_->setValue(QDate::currentDate().year());

    ui->tarih_saat->setMaximum(23);
    ui->tarih_saat->setMinimum(0);
    ui->tarih_saat->setButtonSymbols(QAbstractSpinBox::NoButtons);
    ui->tarih_dakika->setMaximum(59);
    ui->tarih_dakika->setMinimum(0);
    ui->tarih_dakika->setButtonSymbols(QAbstractSpinBox::NoButtons);
    ui->tarih_dakika->setValue(QTime::currentTime().minute());
    ui->tarih_saat->setValue(QTime::currentTime().hour());

    ui->testSuresi_->setButtonSymbols(QAbstractSpinBox::NoButtons);
    ui->testSuresi_->setMaximum(99);
    ui->testSuresi_->setMinimum(1);
    ui->testSuresi_->clear();

    QStringList commandsOlay = {"Geldi","Test","Gitti","Onarıldı"};
    ui->olay_->addItems(commandsOlay);
    connect(ui->olay_, &QComboBox::currentTextChanged, this, &ServisDialog::commandChangedOlay);

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

}


ServisDialog::~ServisDialog()
{
    delete ui;
}
void ServisDialog::commandChangedOlay(const QString& command_text) {
    olay = command_text;
}

void ServisDialog::addMusteri() {
    commandsMusteri.append("LAB");
    if(database.isOpen()) {
        QSqlQuery* qry = new QSqlQuery(database);
        qry ->prepare("select * from müsteri");
        if(qry -> exec()) {
            while(qry->next()) {
                commandsMusteri.append(qry->value(1).toString());
            }
        }
        ui->musteriAdi_1->addItems(commandsMusteri);
        connect(ui->musteriAdi_1, &QComboBox::currentTextChanged, this, &ServisDialog::commandChangedMusteriAdi);

        qry->clear();
        qry->prepare("SELECT İsim FROM müsteri WHERE `Cihaz Seri No` LIKE '%" + servisNo + "%';");
        if(qry->exec()) {
            while(qry->next()) {
                ui->musteriAdi_1->setCurrentText(qry->value(0).toString());
            }
        }
    }else {
        QMessageBox::information(this,"Error", database.lastError().text());
    }

}

void ServisDialog::commandChangedMusteriAdi(const QString &command_text)
{
    //musteriAdi = command_text;
    QMessageBox::information(this,"Değişiklik","Müşteri Adını Değiştirdiniz. Yapılan İşleme Eklendi!");
    QString temp = ui->yapilanIslem_->toPlainText() + "\nMüşteri değiştirildi. Eksi Müşteri: "+ musteriAdi + ", Yeni Müşteri: " + command_text;
    musteriCheck = true;
    ui->yapilanIslem_->setPlainText(temp);
    musteriAdi = command_text;
}
void ServisDialog::initialize(QSqlDatabase d,QString sNo, QString username) {
    ui->teknikServis->setText("Teknik Servis (" + sNo + ")");
    servisNo = sNo;
    database = d;
    name = username;

    addMusteri();
}
void ServisDialog::on_pushButton_clicked()
{

    if(database.open()) {

        QString dakikaTemp = "";
        QString saatTemp = "";
        if(ui->tarih_dakika->text().length() == 1) {
            dakikaTemp = "0" + ui->tarih_dakika->text();
        }else {
            dakikaTemp = ui->tarih_dakika->text();
        }
        if(ui->tarih_saat->text().length() == 1) {
            saatTemp = "0" + ui->tarih_saat->text();
        }else {
            saatTemp = ui->tarih_saat->text();
        }
        saat = saatTemp + ":" + dakikaTemp;
        tarih = ui->gelisTarihiDay_->text() + "." + ui->gelisTarihiMonth_->text() + "." + ui->gelisTarihiYear_->text() + " " + saat;
        olay = ui->olay_->currentText();
        if(ui->yapilanIslem_->toPlainText().length() != 0)
            yapilanIslem = name + ": "  + ui->yapilanIslem_->toPlainText();
        else
            ui->yapilanIslem_->toPlainText();

        if(ui->donanim_1->isChecked()) {
            malzemeler += ui->donanim_1->text() + ui->donanim_1Num->text() + ",";
        }if(ui->donanim_2->isChecked()) {
            malzemeler += ui->donanim_2->text() + ui->donanim_2Num->text() + ",";
        }if(ui->donanim_3->isChecked()) {
            malzemeler += ui->donanim_3->text() + ui->donanim_3Num->text() + ",";
        }if(ui->donanim_4->isChecked()) {
            malzemeler += ui->donanim_4->text() + ui->donanim_4Num->text() + ",";
        }if(ui->donanim_5->isChecked()) {
            malzemeler += ui->donanim_5->text() + ui->donanim_5Num->text() + ",";
        }if(ui->donanim_6->isChecked()) {
            malzemeler += ui->donanim_6->text() + ui->donanim_6Num->text() + ",";
        }if(ui->donanim_7->isChecked()) {
            malzemeler += ui->donanim_7->text() + ui->donanim_7Num->text() + ",";
        }if(ui->donanim_8->isChecked()) {
            malzemeler += ui->donanim_8->text() + ui->donanim_8Num->text() + ",";
        }if(ui->donanim_9->isChecked()) {
            malzemeler += ui->donanim_9->text() + ui->donanim_9Num->text() + ",";
        }if(ui->donanim_10->isChecked()) {
            malzemeler += ui->donanim_10->text() + ui->donanim_10Num->text() + ",";
        }if(ui->donanim_11->isChecked()) {
            malzemeler += ui->donanim_11->text() + ui->donanim_11Num->text();
        }

        if(ui->degisenParca_1->isChecked()) {
            degisenParcalar += ui->degisenParca_1->text() + ",";
        }if(ui->degisenParca_2->isChecked()) {
            degisenParcalar += ui->degisenParca_2->text() + ",";
        }if(ui->degisenParca_3->isChecked()) {
            degisenParcalar += ui->degisenParca_3->text() + ",";
        }if(ui->degisenParca_4->isChecked()) {
            degisenParcalar += ui->degisenParca_4->text() + ",";
        }if(ui->degisenParca_5->isChecked()) {
            degisenParcalar += ui->degisenParca_5->text() + ",";
        }if(ui->degisenParca_6->isChecked()) {
            degisenParcalar += ui->degisenParca_6->text() + ",";
        }if(ui->degisenParca_7->isChecked()) {
            degisenParcalar += ui->degisenParca_7->text() + ",";
        }if(ui->degisenParca_8->isChecked()) {
            degisenParcalar += ui->degisenParca_8->text() + ",";
        }if(ui->degisenParca_9->isChecked()) {
            degisenParcalar += ui->degisenParca_9->text() + ",";
        }if(ui->degisenParca_10->isChecked()) {
            degisenParcalar += ui->degisenParca_10->text() + ",";
        }if(ui->degisenParca_11->isChecked()) {
            degisenParcalar += ui->degisenParca_11->text();
        }if(ui->degisenParca_12->isChecked()) {
            degisenParcalar += ui->degisenParca_12->text();
        }

        testSuresi = ui->testSuresi_->text();
        if(ui->notlar_->toPlainText().length() != 0)
            notlar = name + ": "  + ui->notlar_->toPlainText();
        else
            ui->notlar_->toPlainText();

        QSqlQuery qry;

        qry.prepare("INSERT INTO teknikservis(`Cihaz Seri No`,`Tarih`,"
                    "`Olay`,`Yapılan İşlem`,"
                    "`Cihazla Gelen Malzemeler`,`Degisen Parcalar`,`Test Süresi`,`Notlar`)"
                    "VALUES(:servisNo,:tarih,"
                    ":olay,:yapilanIslem,"
                    ":malzemeler,:degisenParcalar,:testSuresi,:notlar)");
        qry.bindValue(":servisNo",servisNo);
        qry.bindValue(":tarih",tarih);
        qry.bindValue(":olay",olay);
        qry.bindValue(":yapilanIslem",yapilanIslem);
        qry.bindValue(":malzemeler",malzemeler);
        qry.bindValue(":degisenParcalar",degisenParcalar);
        qry.bindValue(":testSuresi",testSuresi);
        qry.bindValue(":notlar",notlar);

        if(qry.exec()) {
            QMessageBox::information(this,"Inserted", "Data Inserted Succesfully");
        }else {
            QMessageBox::information(this,"Not Inserted",qry.lastError().text());
        }

        qry.clear();
        if(musteriCheck) {
            qry.prepare("UPDATE `cihazkimlik` SET `Müşteri Adı` = '" + musteriAdi + "' WHERE `Cihaz Seri No` = '" + servisNo + "';");
            if(qry.exec()){
                QMessageBox::information(this,"Updated", "Müşteri Adı Güncellendi!");
            }else {
                QMessageBox::information(this,"Error", qry.lastError().text());
            }
        }


        this->close();
    }else {
        QMessageBox::information(this, "Not Connected", "Database Is Not Connected");
    }

}

void ServisDialog::on_donanim_1_clicked()
{
    if(ui->donanim_1->isChecked()) {
        ui->donanim_1Num->setVisible(true);
        ui->donanim_1Num->setValue(1);
    }else {
        ui->donanim_1Num->setVisible(false);
        ui->donanim_1Num->setValue(0);
    }
}


void ServisDialog::on_donanim_2_clicked()
{
    if(ui->donanim_2->isChecked()) {
        ui->donanim_2Num->setVisible(true);
        ui->donanim_2Num->setValue(1);
    }else {
        ui->donanim_2Num->setVisible(false);
        ui->donanim_2Num->setValue(1);
    }
}


void ServisDialog::on_donanim_3_clicked()
{
    if(ui->donanim_3->isChecked()) {
        ui->donanim_3Num->setVisible(true);
        ui->donanim_3Num->setValue(1);
    }else {
        ui->donanim_3Num->setVisible(false);
        ui->donanim_3Num->setValue(0);
    }
}


void ServisDialog::on_donanim_4_clicked()
{
    if(ui->donanim_4->isChecked()) {
        ui->donanim_4Num->setVisible(true);
        ui->donanim_4Num->setValue(1);
    }else {
        ui->donanim_4Num->setVisible(false);
        ui->donanim_4Num->setValue(0);
    }
}


void ServisDialog::on_donanim_8_clicked()
{
    if(ui->donanim_8->isChecked()) {
        ui->donanim_8Num->setVisible(true);
        ui->donanim_8Num->setValue(1);
    }else {
        ui->donanim_8Num->setVisible(false);
        ui->donanim_8Num->setValue(0);
    }
}


void ServisDialog::on_donanim_7_clicked()
{
    if(ui->donanim_7->isChecked()) {
        ui->donanim_7Num->setVisible(true);
        ui->donanim_7Num->setValue(1);
    }else {
        ui->donanim_7Num->setVisible(false);
        ui->donanim_7Num->setValue(0);
    }
}


void ServisDialog::on_donanim_9_clicked()
{
    if(ui->donanim_9->isChecked()) {
        ui->donanim_9Num->setVisible(true);
        ui->donanim_9Num->setValue(1);
    }else {
        ui->donanim_9Num->setVisible(false);
        ui->donanim_9Num->setValue(0);
    }
}


void ServisDialog::on_donanim_5_clicked()
{
    if(ui->donanim_5->isChecked()) {
        ui->donanim_5Num->setVisible(true);
        ui->donanim_5Num->setValue(1);
    }else {
        ui->donanim_5Num->setVisible(false);
        ui->donanim_5Num->setValue(0);
    }
}


void ServisDialog::on_donanim_6_clicked()
{
    if(ui->donanim_6->isChecked()) {
        ui->donanim_6Num->setVisible(true);
        ui->donanim_6Num->setValue(1);
    }else {
        ui->donanim_6Num->setVisible(false);
        ui->donanim_6Num->setValue(0);
    }
}


void ServisDialog::on_donanim_11_clicked()
{
    if(ui->donanim_11->isChecked()) {
        ui->donanim_11Num->setVisible(true);
        ui->donanim_11Num->setValue(1);
    }else {
        ui->donanim_11Num->setVisible(false);
        ui->donanim_11Num->setValue(0);
    }
}


void ServisDialog::on_donanim_10_clicked()
{
    if(ui->donanim_10->isChecked()) {
        ui->donanim_10Num->setVisible(true);
        ui->donanim_10Num->setValue(1);
    }else {
        ui->donanim_10Num->setVisible(false);
        ui->donanim_10Num->setValue(0);
    }
}


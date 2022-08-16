#include "serverservisdialog.h"
#include "ui_serverservisdialog.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QTime>
#include <QMessageBox>

ServerServisDialog::ServerServisDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ServerServisDialog)
{
    ui->setupUi(this);
    changes();

}

ServerServisDialog::~ServerServisDialog()
{
    delete ui;
}

void ServerServisDialog::changes() {
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

    QStringList commandsOlay = {"Geldi","Test","Demo verildi","Müşteriye verildi","Gitti","Onarıldı"};
    ui->olay_->addItems(commandsOlay);
    connect(ui->olay_, &QComboBox::currentTextChanged, this, &ServerServisDialog::commandChangedOlay);

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



}
void ServerServisDialog::setLog(QString content) {

    QSqlQuery qry;
    QString date = QDateTime::currentDateTime().toString("dd.MM.yyyy hh:mm:ss");
    qry.prepare("INSERT INTO processlogs(`tarih`,`username`,`process`) VALUES (:tarih,:username,:process)");
    qry.bindValue(":tarih",date);
    qry.bindValue(":username",name);
    qry.bindValue(":process",content);
    qry.exec();
}
void ServerServisDialog::addMusteri() {
    commandsMusteri.append("LAB");
    if(database.isOpen()) {
        QSqlQuery* qry = new QSqlQuery(database);
        qry ->prepare("select * from müsteri");
        if(qry -> exec()) {
            while(qry->next()) {
                commandsMusteri.append(qry->value(1).toString());
            }
        }else {
            QMessageBox::information(this,"Error",qry->lastError().text());
            setLog("[ERROR] serverservisdialog.cpp : " + qry->lastError().text());
        }
        ui->musteriAdi_1->addItems(commandsMusteri);
        connect(ui->musteriAdi_1, &QComboBox::currentTextChanged, this, &ServerServisDialog::commandChangedMusteriAdi);

    }else {
        QMessageBox::information(this,"Error",database.lastError().text());
        setLog("[ERROR] serverservisdialog.cpp : " + database.lastError().text());
    }

}


void ServerServisDialog::setOrginalMusteri() {
    if(database.isOpen()) {
        QSqlQuery* qry = new QSqlQuery(database);

        qry->prepare("SELECT İsim FROM cihazisim WHERE `Cihaz Seri No` = '" + servisNo + "';");
        if(qry->exec()) {
                while(qry->next()) {
                    ui->musteriAdi_1->setCurrentText(qry->value(0).toString());
                    musteriAdi = qry->value(0).toString();
                    checkMusteriChange = true;
                }
        }else {
            QMessageBox::information(this,"Error",qry->lastError().text());
            setLog("[ERROR] serverservisdialog.cpp : " + qry->lastError().text());
        }
    }else {
        QMessageBox::information(this,"Error",database.lastError().text());
        setLog("[ERROR] serverservisdialog.cpp : " + database.lastError().text());
    }

}
void ServerServisDialog::commandChangedMusteriAdi(const QString &command_text)
{
    if(QString::compare(musteriAdi, command_text, Qt::CaseInsensitive) && checkMusteriChange) {
        QMessageBox::information(this,"Değişiklik","Müşteri Adını Değiştirdiniz. Yapılan İşleme Eklendi!");
        QString temp = ui->yapilanIslem_->toPlainText() + "\nMüşteri değiştirildi. Eksi Müşteri: "+ musteriAdi + ", Yeni Müşteri: " + command_text;
        musteriCheck = true;
        ui->yapilanIslem_->setPlainText(temp);
        musteriAdi = command_text;
    }
    musteriAdi = command_text;
}
void ServerServisDialog::commandChangedOlay(const QString& command_text) {
    olay = command_text;
}

void ServerServisDialog::initialize(QSqlDatabase d, QString sNo, QString username) {
    ui->teknikServis->setText("Teknik Servis (" + sNo + ")");
    servisNo = sNo;
    database = d;
    name = username;

    addMusteri();
    setOrginalMusteri();
}
void ServerServisDialog::on_pushButton_clicked()
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
            setLog("[NOTE] serverservisdialog.cpp : server cihazı eklendi");
        }else {
            QMessageBox::information(this,"Not Inserted",qry.lastError().text());
            setLog("[ERROR] serverservisdialog.cpp : " + qry.lastError().text());
        }

        qry.clear();
        if(musteriCheck) {
            qry.prepare("UPDATE `cihazkimlik` SET `Müşteri Adı` = '" + musteriAdi + "' WHERE `Cihaz Seri No` = '" + servisNo + "';");
            if(qry.exec()){
                QMessageBox::information(this,"Updated", "Müşteri Adı Güncellendi!");
                setLog("[ERROR] serverservisdialog.cpp : müşteri adı güncellendi");
            }else {
                QMessageBox::information(this,"Error", qry.lastError().text());
                setLog("[ERROR] serverservisdialog.cpp : " + qry.lastError().text());
            }
        }

        this->close();
    }else {
        QMessageBox::information(this, "Not Connected", "Database Is Not Connected");
        setLog("[ERROR] serverservisdialog.cpp : " + database.lastError().text());
    }
}

void ServerServisDialog::on_donanim_1_clicked()
{
    if(ui->donanim_1->isChecked()) {
        ui->donanim_1Num->setVisible(true);
        ui->donanim_1Num->setValue(1);
    }else {
        ui->donanim_1Num->setVisible(false);
        ui->donanim_1Num->setValue(0);
    }
}


void ServerServisDialog::on_donanim_2_clicked()
{
    if(ui->donanim_2->isChecked()) {
        ui->donanim_2Num->setVisible(true);
        ui->donanim_2Num->setValue(1);
    }else {
        ui->donanim_2Num->setVisible(false);
        ui->donanim_2Num->setValue(1);
    }
}


void ServerServisDialog::on_donanim_3_clicked()
{
    if(ui->donanim_3->isChecked()) {
        ui->donanim_3Num->setVisible(true);
        ui->donanim_3Num->setValue(1);
    }else {
        ui->donanim_3Num->setVisible(false);
        ui->donanim_3Num->setValue(0);
    }
}

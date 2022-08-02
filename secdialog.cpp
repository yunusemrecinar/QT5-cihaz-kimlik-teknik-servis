#include "secdialog.h"
#include "ui_secdialog.h"
#include <QMessageBox>
#include <QSqlQuery>
#include "mainwindow.h"
#include "lineeditpopupform.h"
#include <QVBoxLayout>
#include <QMenu>
#include <QComboBox>
#include "musteri.h"
#include "mobiotdialog.h"
#include "serverdialog.h"

#include <iostream>
using namespace std;



SecDialog::SecDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SecDialog)
{
    ui->setupUi(this);
    this->setWindowTitle(" ");
    changes();
}

SecDialog::~SecDialog()
{
    delete ui;
}
void SecDialog::changes() {
    ui->cihaz_seri_no->setMaxLength(9);
    ui->cihaz_seri_no->setValidator(new QRegularExpressionValidator(QRegularExpression("\\d*")));
    ui->UIDNo_1->setMaxLength(12);
    ui->modemSeri1_->setMaxLength(15);
    ui->modemSeri2_->setMaxLength(15);
    ui->modemSeri3_->setMaxLength(15);
    ui->modemSeri4_->setMaxLength(15);
    ui->modemSeri5_->setMaxLength(15);
    ui->modemSeri6_->setMaxLength(15);
    ui->modemSeri1_->setValidator(new QRegularExpressionValidator(QRegularExpression("\\d*")));
    ui->modemSeri2_->setValidator(new QRegularExpressionValidator(QRegularExpression("\\d*")));
    ui->modemSeri3_->setValidator(new QRegularExpressionValidator(QRegularExpression("\\d*")));
    ui->modemSeri4_->setValidator(new QRegularExpressionValidator(QRegularExpression("\\d*")));
    ui->modemSeri5_->setValidator(new QRegularExpressionValidator(QRegularExpression("\\d*")));
    ui->modemSeri6_->setValidator(new QRegularExpressionValidator(QRegularExpression("\\d*")));
    ui->date_day->setMaximum(31);
    ui->date_day->setMinimum(1);
    ui->date_day->setButtonSymbols(QAbstractSpinBox::NoButtons);
    ui->date_month->setButtonSymbols(QAbstractSpinBox::NoButtons);
    ui->date_month->setMaximum(12);
    ui->date_month->setMinimum(1);
    ui->date_year->setButtonSymbols(QAbstractSpinBox::NoButtons);
    ui->date_year->setMaximum(QDate::currentDate().year());
    ui->date_year->setMinimum(1);
    ui->date_day->clear();
    ui->date_month->clear();
    ui->date_year->clear();

    QStringList commandsDurum = {"SATIŞ","DEMO","STOK"};
    ui->durum_->addItems(commandsDurum);
    connect(ui->durum_, &QComboBox::currentTextChanged, this, &SecDialog::commandChangedDurum);

    QStringList testDurum = {"Test Edilecek","Lab Testi Yapıldı","Saha Testi Yapıldı"};
    ui->test_durum_->addItems(testDurum);
    connect(ui->test_durum_, &QComboBox::currentTextChanged, this, &SecDialog::commandChangedTestDurum);

}
void SecDialog::addModels() {
    if(database.isOpen()) {
        QSqlQuery* qry = new QSqlQuery(database);
        qry ->prepare("select * from model");
        if(qry -> exec()) {
            while(qry->next()) {commandsModel.append(qry->value(0).toString());}
        }
    }
    ui->model_->addItems(commandsModel);
    connect(ui->model_, &QComboBox::currentTextChanged, this, &SecDialog::commandChangedModel);
}
void SecDialog::addModemTipi() {
    if(database.isOpen()) {
        QSqlQuery* qry = new QSqlQuery(database);
        qry ->prepare("select * from modemtipi");
        if(qry -> exec()) {
            while(qry->next()) {commandsModemTipi.append(qry->value(0).toString());}
        }
    }
    ui->modemTipi_->addItems(commandsModemTipi);
    connect(ui->modemTipi_, &QComboBox::currentTextChanged, this, &SecDialog::commandChangedModemTipi);
}
void SecDialog::addMusteri() {
    commandsMusteri.append("LAB");
    if(database.isOpen()) {
        QSqlQuery* qry = new QSqlQuery(database);
        qry ->prepare("select * from müsteri");
        if(qry -> exec()) {
            while(qry->next()) {commandsMusteri.append(qry->value(1).toString());}
        }
    }
    ui->musteriAdi_1->addItems(commandsMusteri);
    connect(ui->musteriAdi_1, &QComboBox::currentTextChanged, this, &SecDialog::commandChangedMusteriAdi);
}
void SecDialog::commandChangedModemTipi(const QString& command_text) {
    modemTipi = command_text;
}
void SecDialog::commandChangedMusteriAdi(const QString& command_text) {
    musteriAdi = command_text;
}
void SecDialog::commandChangedModel(const QString& command_text) {

    if(QString::compare("Server",command_text,Qt::CaseInsensitive) == 0) {
        serverDialog = new ServerDialog();
        serverDialog->initialize(database);
        this->close();
        serverDialog->exec();
    }else if(QString::compare("Mobiot",command_text,Qt::CaseInsensitive) == 0) {
        mobiotDialog = new MobiotDialog();
        mobiotDialog->initialize(database);
        this->close();
        mobiotDialog->exec();
    }else {
        model = command_text;
    }

}
void SecDialog::commandChangedDurum(const QString& command_text) {
    durum = command_text;
}
void SecDialog::commandChangedTestDurum(const QString& command_text) {
    testDurumu = command_text;
}
void SecDialog::initialize(QSqlDatabase d) {
    database = d;

    addModels();
    addModemTipi();
    addMusteri();
}

void SecDialog::on_pushButton_clicked()
{

    if(database.isOpen()) {

        model = ui->model_->currentText();
        QString cihazSeriNo = ui->cihaz_seri_no->text();
        anakartNo = ui->anakart_->text();
        QString uidNo = ui->UIDNo_1->text();
        modemKarti = ui->modem_karti_->text();
        lcdKarti = ui->lcd_karti_->text();
        sarjKarti = ui->sarj_karti_->text();
        durum = ui->durum_->currentText();
        modemTipi = ui->modemTipi_->currentText();
        testDurumu = ui->test_durum_->currentText();
        QString uretimTarihi = ui->date_day->text() + "." + ui->date_month->text() + "." + ui->date_year->text();
        QString modemSeri1 = ui->modemSeri1_->text();
        QString modemSeri2 = ui->modemSeri2_->text();
        QString modemSeri3 = ui->modemSeri3_->text();
        QString modemSeri4 = ui->modemSeri4_->text();
        QString modemSeri5 = ui->modemSeri5_->text();
        QString modemSeri6 = ui->modemSeri6_->text();
        musteriAdi = ui->musteriAdi_1->currentText();
        QString notlar = ui->notlar_->toPlainText();

        if(ui->cihaz_seri_no->text().length() == 9) {
            checkSeriNo = true;
        }

        QSqlQuery qry;

        qry.prepare("INSERT INTO cihazkimlik(`Model`,`Cihaz Seri No`,`Anakart No`,"
                    "`UID No`,`Modem Kartı`,`Lcd Kartı`,`Şarj Kartı`,`Durumu`,`Modem Tipi`,`Müşteri Adı`,`Modem Seri Num 1`,"
                    "`Modem Seri Num 2`,`Modem Seri Num 3`,`Modem Seri Num 4`,`Modem Seri Num 5`,"
                    "`Modem Seri Num 6`,`Uretim Tarihi`,`Test Durumu`,`Notlar`) "
                    "VALUES(:model,:cihazSeriNo,:anakartNo,:uidNo,"
                    ":modemKarti,:lcdKarti,:sarjKarti,:durumu,:modemTipi,:musteriAdi,:modemSeriNum1,"
                    ":modemSeriNum2,:modemSeriNum3,:modemSeriNum4,:modemSeriNum5,"
                    ":modemSeriNum6,:uretimTarihi,:testDurumu,:notlar)");
        qry.bindValue(":model",model);
        qry.bindValue(":cihazSeriNo",cihazSeriNo);
        qry.bindValue(":anakartNo",anakartNo);
        qry.bindValue(":uidNo",uidNo);
        qry.bindValue(":modemKarti",modemKarti);
        qry.bindValue(":lcdKarti",lcdKarti);
        qry.bindValue(":sarjKarti",sarjKarti);
        qry.bindValue(":durumu",durum);
        qry.bindValue(":modemTipi",modemTipi);
        qry.bindValue(":musteriAdi",musteriAdi);
        qry.bindValue(":modemSeriNum1",modemSeri1);
        qry.bindValue(":modemSeriNum2",modemSeri2);
        qry.bindValue(":modemSeriNum3",modemSeri3);
        qry.bindValue(":modemSeriNum4",modemSeri4);
        qry.bindValue(":modemSeriNum5",modemSeri5);
        qry.bindValue(":modemSeriNum6",modemSeri6);
        qry.bindValue(":uretimTarihi",uretimTarihi);
        qry.bindValue(":testDurumu",testDurumu);
        qry.bindValue(":notlar",notlar);
        if(checkSeriNo) {
            if(qry.exec()) {
                QMessageBox::information(this,"Inserted","Data Inserted Succesfully");
                this->close();
            }else {
                QMessageBox::information(this,"Not Inserted",qry.lastError().text());
            }
        }else {
            QMessageBox::information(this,"Error","Cihaz Seri No bilgisi eksik!!");
        }

    }else {
        QMessageBox::information(this, "Not Connected", "Database Is Not Connected");
        cout << "Database not connected!" << endl;
    }

}



void SecDialog::on_model__currentTextChanged()
{
    //Musteri *musteri = new Musteri();
    //this->close();
    //musteri->exec();
}


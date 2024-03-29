#include "mobiotdialog.h"
#include "ui_mobiotdialog.h"
#include <QDate>
#include <QSqlQuery>
#include <QMessageBox>
#include <QSqlError>
#include "secdialog.h"
#include "serverdialog.h"

#include <iostream>
using namespace std;

MobiotDialog::MobiotDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MobiotDialog)
{
    ui->setupUi(this);
    changes();

}

MobiotDialog::~MobiotDialog()
{
    delete ui;
}

void MobiotDialog::initialize(QSqlDatabase d, QString user)
{
    database = d;

    addMusteri();
    addModemTipi();
    addModels();
    username = user;
}

void MobiotDialog::addModels() {
    if(database.isOpen()) {
        QSqlQuery* qry = new QSqlQuery(database);
        qry ->prepare("select * from model");
        if(qry -> exec()) {
            while(qry->next()) {commandsModel.append(qry->value(0).toString());}
        }else{
            setLog("[ERROR] mobiotdialog.cpp : " + qry->lastError().text());
        }
    }else{
        setLog("[ERROR] mobiotdialog.cpp : " + database.lastError().text());
    }
    ui->model_->addItems(commandsModel);
    connect(ui->model_, &QComboBox::currentTextChanged, this, &MobiotDialog::commandChangedModel);
}

void MobiotDialog::setLog(QString content) {

    QSqlQuery qry;
    QString date = QDateTime::currentDateTime().toString("dd.MM.yyyy hh:mm:ss");
    qry.prepare("INSERT INTO processlogs(`tarih`,`username`,`process`) VALUES (:tarih,:username,:process)");
    qry.bindValue(":tarih",date);
    qry.bindValue(":username",username);
    qry.bindValue(":process",content);
    qry.exec();
}

void MobiotDialog::commandChangedModel(const QString& command_text) {


        if(QString::compare("Server",command_text,Qt::CaseInsensitive) == 0) {
            ServerDialog *serverDialog = new ServerDialog();
            serverDialog->initialize(database, username);
            serverDialog->commandChangedModel(command_text);
            this->close();
            serverDialog->exec();
        }else if(QString::compare("Mobiot",command_text,Qt::CaseInsensitive) == 0) {
            ui->model_->setCurrentText(command_text);
        }else {
            model = command_text;
            SecDialog *secDialog = new SecDialog();
            secDialog->initialize(database, username);
            secDialog->count = 1;
            secDialog->commandChangedModel(command_text);
            this->close();
            secDialog->exec();

        }

}
void MobiotDialog::on_pushButton_clicked()
{

    if(database.isOpen()) {

        cihazSeriNo = ui->cihaz_seri_no->text();
        anakartNo = ui->anakart_->text();
        uidNo = ui->UIDNo_1->text();
        durum = ui->durum_->currentText();
        modemTipi = ui->modemTipi_->currentText();
        testDurumu = ui->test_durum_->currentText();
        tarih = ui->date_day->text() + "." + ui->date_month->text() + "." + ui->date_year->text();
        imei1 = ui->modemSeri1_->text();
        imei2 = ui->modemSeri2_->text();
        imei3 = ui->modemSeri3_->text();
        QString faturaKesim = ui->fatura_date_day_->text() + "." + ui->fatura_date_month_->text() + "." + ui->fatura_date_year_->text();
        QString garantiBaslangic = ui->garanti_start_day_->text() + "." + ui->garanti_start_month_->text() + "." + ui->garanti_start_year_->text();
        QString garantiBitis = ui->garanti_bitis_day_->text() + "." + ui->garanti_bitis_month_->text() + "." + ui->garanti_bitis_year_->text();
        musteriAdi = ui->musteriAdi_1->currentText();
        notlar = ui->notlar_->toPlainText();

        if(ui->cihaz_seri_no->text().length() == 9) {
            checkSeriNo = true;
        }

        QSqlQuery qry;

        qry.prepare("INSERT INTO cihazkimlikmobiot(`Model`,`Cihaz Seri No`,`Anakart No`,"
                    "`UID No`,`Test Durumu`,`Müşteri`,`Durum`,`Üretim Tarihi`,`Modem Tipi`,"
                    "`IMEI 1`,`IMEI 2`,`IMEI 3`,`Fatura Kesim`,`Garanti Baslangic`,`Garanti Bitis`,`Notlar`) "
                    "VALUES(:model,:cihazSeriNo,:anakartNo,:uidNo,"
                    ":testDurumu,:musteri,:durum,:uretimTarih,:modemTipi,:imei1,:imei2,"
                    ":imei3,:faturaKesim,:garantiBaslangic,:garantiBitis,:notlar)");
        qry.bindValue(":model",model);
        qry.bindValue(":cihazSeriNo",cihazSeriNo);
        qry.bindValue(":anakartNo",anakartNo);
        qry.bindValue(":uidNo",uidNo);
        qry.bindValue(":testDurumu",testDurumu);
        qry.bindValue(":musteri",musteriAdi);
        qry.bindValue(":durum",durum);
        qry.bindValue(":uretimTarih",tarih);
        qry.bindValue(":modemTipi",modemTipi);
        qry.bindValue(":imei1",imei1);
        qry.bindValue(":imei2",imei2);
        qry.bindValue(":imei3",imei3);
        qry.bindValue(":faturaKesim",faturaKesim);
        qry.bindValue(":garantiBaslangic",garantiBaslangic);
        qry.bindValue(":garantiBitis",garantiBitis);
        qry.bindValue(":notlar",notlar);

        if(checkSeriNo) {
            if(qry.exec()) {
                QMessageBox::information(this,"Inserted","Data Inserted Succesfully");
                setLog("[NOTE] mobiotdialog.cpp : Cihaz Eklendi");
                qry.clear();
                qry.prepare("INSERT INTO cihazisim VALUES('"+ cihazSeriNo + "','" + musteriAdi + "');");
                if(qry.exec()) {
                    setLog("[NOTE] mobiotdialog.cpp : Yeni cihaz cihazisim tablosuna eklendi!");
                }else {
                    setLog("[ERROR] mobiotdialog.cpp : " + qry.lastError().text());
                }
                this->close();
            }else {
                QMessageBox::information(this,"Not Inserted",qry.lastError().text());
                setLog("[ERROR] mobiotdialog.cpp : " + qry.lastError().text());
            }
        }else {
            QMessageBox::information(this,"Error","Cihaz Seri No bilgisi eksik!!");
        }

    }else {
        QMessageBox::information(this, "Not Connected", "Database Is Not Connected");
        setLog("[ERROR] mobiotdialog.cpp : " + database.lastError().text());
        cout << "Database not connected!" << endl;
    }

}

void MobiotDialog::changes()
{
    ui->cihaz_seri_no->setMaxLength(9);
    ui->cihaz_seri_no->setValidator(new QRegularExpressionValidator(QRegularExpression("\\d*")));
    ui->UIDNo_1->setMaxLength(12);
    ui->modemSeri1_->setMaxLength(15);
    ui->modemSeri2_->setMaxLength(15);
    ui->modemSeri3_->setMaxLength(15);
    ui->modemSeri1_->setValidator(new QRegularExpressionValidator(QRegularExpression("\\d*")));
    ui->modemSeri2_->setValidator(new QRegularExpressionValidator(QRegularExpression("\\d*")));
    ui->modemSeri3_->setValidator(new QRegularExpressionValidator(QRegularExpression("\\d*")));
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

    ui->fatura_date_day_->setMaximum(31);
    ui->fatura_date_day_->setMinimum(1);
    ui->fatura_date_day_->setButtonSymbols(QAbstractSpinBox::NoButtons);
    ui->fatura_date_month_->setButtonSymbols(QAbstractSpinBox::NoButtons);
    ui->fatura_date_month_->setMaximum(12);
    ui->fatura_date_month_->setMinimum(1);
    ui->fatura_date_year_->setButtonSymbols(QAbstractSpinBox::NoButtons);
    ui->fatura_date_year_->setMaximum(QDate::currentDate().year());
    ui->fatura_date_year_->setMinimum(1);
    ui->fatura_date_day_->clear();
    ui->fatura_date_month_->clear();
    ui->fatura_date_year_->clear();

    ui->garanti_start_day_->setMaximum(31);
    ui->garanti_start_day_->setMinimum(1);
    ui->garanti_start_day_->setButtonSymbols(QAbstractSpinBox::NoButtons);
    ui->garanti_start_month_->setButtonSymbols(QAbstractSpinBox::NoButtons);
    ui->garanti_start_month_->setMaximum(12);
    ui->garanti_start_month_->setMinimum(1);
    ui->garanti_start_year_->setButtonSymbols(QAbstractSpinBox::NoButtons);
    ui->garanti_start_year_->setMaximum(QDate::currentDate().year());
    ui->garanti_start_year_->setMinimum(1);
    ui->garanti_start_day_->clear();
    ui->garanti_start_month_->clear();
    ui->garanti_start_year_->clear();

    ui->garanti_bitis_day_->setMaximum(31);
    ui->garanti_bitis_day_->setMinimum(1);
    ui->garanti_bitis_day_->setButtonSymbols(QAbstractSpinBox::NoButtons);
    ui->garanti_bitis_month_->setButtonSymbols(QAbstractSpinBox::NoButtons);
    ui->garanti_bitis_month_->setMaximum(12);
    ui->garanti_bitis_month_->setMinimum(1);
    ui->garanti_bitis_year_->setButtonSymbols(QAbstractSpinBox::NoButtons);
    ui->garanti_bitis_year_->setMaximum(QDate::currentDate().year());
    ui->garanti_bitis_year_->setMinimum(1);
    ui->garanti_bitis_day_->clear();
    ui->garanti_bitis_month_->clear();
    ui->garanti_bitis_year_->clear();

    QStringList commandsDurum = {"SATIŞ","DEMO","STOK"};
    ui->durum_->addItems(commandsDurum);
    connect(ui->durum_, &QComboBox::currentTextChanged, this, &MobiotDialog::commandChangedDurum);

    QStringList testDurum = {"Test Edilecek","Lab Testi Yapıldı","Saha Testi Yapıldı"};
    ui->test_durum_->addItems(testDurum);
    connect(ui->test_durum_, &QComboBox::currentTextChanged, this, &MobiotDialog::commandChangedTestDurum);
}

void MobiotDialog::commandChangedDurum(const QString& command_text) {
    durum = command_text;
}
void MobiotDialog::commandChangedTestDurum(const QString& command_text) {
    testDurumu = command_text;
}

void MobiotDialog::addModemTipi() {
    if(database.isOpen()) {
        QSqlQuery* qry = new QSqlQuery(database);
        qry ->prepare("select * from modemtipi");
        if(qry -> exec()) {
            while(qry->next()) {commandsModemTipi.append(qry->value(0).toString());}
        }else {
            setLog("[ERROR] mobiotdialog.cpp : " + qry->lastError().text());
        }
    }else {
        setLog("[ERROR] mobiotdialog.cpp : " + database.lastError().text());
    }
    ui->modemTipi_->addItems(commandsModemTipi);
    connect(ui->modemTipi_, &QComboBox::currentTextChanged, this, &MobiotDialog::commandChangedModemTipi);
}
void MobiotDialog::addMusteri() {
    commandsMusteri.append("LAB");
    if(database.isOpen()) {
        QSqlQuery* qry = new QSqlQuery(database);
        qry ->prepare("select * from müsteri");
        if(qry -> exec()) {
            while(qry->next()) {
                commandsMusteri.append(qry->value(1).toString());
            }
        }else {
            setLog("[ERROR] mobiotdialog.cpp : " + qry->lastError().text());
        }
    }else {
        setLog("[ERROR] mobiotdialog.cpp : " + database.lastError().text());
    }
    ui->musteriAdi_1->addItems(commandsMusteri);
    connect(ui->musteriAdi_1, &QComboBox::currentTextChanged, this, &MobiotDialog::commandChangedMusteriAdi);
}
void MobiotDialog::commandChangedModemTipi(const QString& command_text) {
    modemTipi = command_text;
}
void MobiotDialog::commandChangedMusteriAdi(const QString& command_text) {
    musteriAdi = command_text;
}

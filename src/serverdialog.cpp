#include "serverdialog.h"
#include "ui_serverdialog.h"
#include <QDate>
#include <QSqlQuery>
#include <QMessageBox>
#include <QSqlError>
#include "mobiotdialog.h"
#include "secdialog.h"

#include <iostream>
using namespace std;

ServerDialog::ServerDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ServerDialog)
{
    ui->setupUi(this);
    changes();


}

ServerDialog::~ServerDialog()
{
    delete ui;
}

void ServerDialog::initialize(QSqlDatabase d)
{
    database = d;

    addMusteri();
    addModels();
}

void ServerDialog::commandChangedModel(const QString &command_text)
{

    if(QString::compare("Server",command_text,Qt::CaseInsensitive) == 0) {
        ui->model_->setCurrentText(command_text);
    }else if(QString::compare("Mobiot",command_text,Qt::CaseInsensitive) == 0) {
        MobiotDialog *mobiotDialog = new MobiotDialog();
        mobiotDialog->initialize(database);
        mobiotDialog->commandChangedModel(command_text);
        this->close();
        mobiotDialog->exec();
    }else {
        model = command_text;
        SecDialog *secDialog = new SecDialog();
        secDialog->initialize(database);
        secDialog->count = 1;
        secDialog->commandChangedModel(command_text);
        this->close();
        secDialog->exec();

    }

}

void ServerDialog::changes() {
    ui->cihaz_seri_no->setMaxLength(9);
    ui->cihaz_seri_no->setValidator(new QRegularExpressionValidator(QRegularExpression("\\d*")));
    ui->UIDNo_1->setMaxLength(12);
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
    connect(ui->durum_, &QComboBox::currentTextChanged, this, &ServerDialog::commandChangedDurum);

    QStringList testDurum = {"Test Edilecek","Lab Testi Yapıldı","Saha Testi Yapıldı"};
    ui->test_durum_->addItems(testDurum);
    connect(ui->test_durum_, &QComboBox::currentTextChanged, this, &ServerDialog::commandChangedTestDurum);

    QStringList commandsKasaTipi = {"1U","1U","Tower"};
    ui->kasaTipi_->addItems(commandsKasaTipi);
    connect(ui->kasaTipi_, &QComboBox::currentTextChanged, this, &ServerDialog::commandChangedKasaTipi);

    QStringList commandsDecklink = {"Quad","Studio 2","Studio 4K"};
    ui->decklink_->addItems(commandsDecklink);
    connect(ui->decklink_,&QComboBox::currentTextChanged, this, &ServerDialog::commandChangedDecklink);
}
void ServerDialog::addModels() {
    if(database.isOpen()) {
        QSqlQuery* qry = new QSqlQuery(database);
        qry ->prepare("select * from model");
        if(qry -> exec()) {
            while(qry->next()) {commandsModel.append(qry->value(0).toString());}
        }
    }
    ui->model_->addItems(commandsModel);
    connect(ui->model_, &QComboBox::currentTextChanged, this, &ServerDialog::commandChangedModel);
}

void ServerDialog::addMusteri() {
    commandsMusteri.append("LAB");
    if(database.isOpen()) {
        QSqlQuery* qry = new QSqlQuery(database);
        qry ->prepare("select * from müsteri");
        if(qry -> exec()) {
            while(qry->next()) {commandsMusteri.append(qry->value(1).toString());}
        }
    }
    ui->musteriAdi_1->addItems(commandsMusteri);
    connect(ui->musteriAdi_1, &QComboBox::currentTextChanged, this, &ServerDialog::commandChangedMusteriAdi);
}
void ServerDialog::commandChangedDurum(const QString &command_text)
{
    durum = command_text;
}

void ServerDialog::commandChangedTestDurum(const QString &command_text)
{
    testDurumu = command_text;
}

void ServerDialog::commandChangedMusteriAdi(const QString &command_text)
{
    musteriAdi = command_text;
}

void ServerDialog::commandChangedKasaTipi(const QString &command_text)
{
    kasaTipi = command_text;
}

void ServerDialog::commandChangedDecklink(const QString &command_text)
{
    decklink = command_text;
}

void ServerDialog::on_pushButton_clicked()
{

    if(database.isOpen()) {

        model = ui->model_->currentText();
        anakartNo = ui->anakart_->text();
        cihazSeriNo = ui->cihaz_seri_no->text();
        durum = ui->durum_->currentText();
        kasaTipi = ui->kasaTipi_->currentText();
        uidNo = ui->UIDNo_1->text();
        decklink = ui->decklink_->currentText();
        ram = ui->ram_->text() + "GB";
        testDurumu = ui->test_durum_->currentText();
        musteriAdi = ui->musteriAdi_1->currentText();
        islemci = ui->islemci_->text();
        tarih = ui->date_day->text() + "." + ui->date_month->text() + "." + ui->date_year->text();
        QString faturaKesim = ui->fatura_date_day_->text() + "." + ui->fatura_date_month_->text() + "." + ui->fatura_date_year_->text();
        QString garantiBaslangic = ui->garanti_start_day_->text() + "." + ui->garanti_start_month_->text() + "." + ui->garanti_start_year_->text();
        QString garantiBitis = ui->garanti_bitis_day_->text() + "." + ui->garanti_bitis_month_->text() + "." + ui->garanti_bitis_year_->text();

        hdd = ui->hdd_->text();
        notlar = ui->notlar_->toPlainText();

        if(ui->cihaz_seri_no->text().length() == 9) {
            checkSeriNo = true;
        }
        QMessageBox::information(this,"fdfs","asdsa" + QString::number(12) + "fdsfs");

        QSqlQuery qry;

        qry.prepare("INSERT INTO cihazkimlikserver(`Model`,`Cihaz Seri No`,`Anakart No`,"
                    "`UID No`,`İşlemci`,`Ram`,`Decklink`,`Kasa Tipi`,`Test Durumu`,"
                    "`Müşteri`,`Durum`,`Üretim Tarihi`,`Fatura Kesim`,`Garanti Baslangic`,`Garanti Bitis`,`HDD`,`Notlar`) "
                    "VALUES(:model,:cihazSeriNo,:anakartNo,:uidNo,"
                    ":islemci,:ram,:decklink,:kasaTipi,:testDurumu,:musteri,:durum,"
                    ":tarih,:faturaKesim,:garantiBaslangic,:garantiBitis,:hdd,:notlar)");
        qry.bindValue(":model",model);
        qry.bindValue(":cihazSeriNo",cihazSeriNo);
        qry.bindValue(":anakartNo",anakartNo);
        qry.bindValue(":uidNo",uidNo);
        qry.bindValue(":islemci",islemci);
        qry.bindValue(":ram",ram);
        qry.bindValue(":decklink",decklink);
        qry.bindValue(":kasaTipi",kasaTipi);
        qry.bindValue(":testDurumu",testDurumu);
        qry.bindValue(":musteri",musteriAdi);
        qry.bindValue(":durum",durum);
        qry.bindValue(":tarih",tarih);
        qry.bindValue(":faturaKesim",faturaKesim);
        qry.bindValue(":garantiBaslangic",garantiBaslangic);
        qry.bindValue(":garantiBitis",garantiBitis);
        qry.bindValue(":hdd",hdd);
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


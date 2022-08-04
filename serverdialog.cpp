#include "serverdialog.h"
#include "ui_serverdialog.h"
#include <QDate>
#include <QSqlQuery>
#include <QMessageBox>
#include <QSqlError>

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

        model = ui->model_->text();
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
        hdd = ui->hdd_->text();
        notlar = ui->notlar_->toPlainText();

        if(ui->cihaz_seri_no->text().length() == 9) {
            checkSeriNo = true;
        }

        QSqlQuery qry;

        qry.prepare("INSERT INTO cihazkimlikserver(`Model`,`Cihaz Seri No`,`Anakart No`,"
                    "`UID No`,`İşlemci`,`Ram`,`Decklink`,`Kasa Tipi`,`Test Durumu`,"
                    "`Müşteri`,`Durum`,`Üretim Tarihi`,`HDD`,`Notlar`) "
                    "VALUES(:model,:cihazSeriNo,:anakartNo,:uidNo,"
                    ":islemci,:ram,:decklink,:kasaTipi,:testDurumu,:musteri,:durum,"
                    ":tarih,:hdd,:notlar)");
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


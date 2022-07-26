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
    ui->testSuresi_->setMaximum(12);
    ui->testSuresi_->setMinimum(1);
    ui->testSuresi_->clear();

    QStringList commandsOlay = {"Geldi","Test","Gitti","Onarıldı"};
    ui->olay_->addItems(commandsOlay);
    connect(ui->olay_, &QComboBox::currentTextChanged, this, &ServisDialog::commandChangedOlay);
}
ServisDialog::~ServisDialog()
{
    delete ui;
}
void ServisDialog::commandChangedOlay(const QString& command_text) {
    olay = command_text;
}
void ServisDialog::initialize(QSqlDatabase d,QString sNo) {
    ui->servisNo_->setText(sNo);
    database = d;
}
void ServisDialog::on_pushButton_clicked()
{

    if(database.open()) {

        servisNo = ui->servisNo_->text();
        tarih = ui->gelisTarihiDay_->text() + "." + ui->gelisTarihiMonth_->text() + "." + ui->gelisTarihiYear_->text();
        saat = ui->tarih_saat->text() + ":" + ui->tarih_dakika->text();
        musteriAdi = ui->musteriAdi_->text();
        olay = ui->olay_->currentText();
        arizaTarifi = ui->arizaTanimi_->toPlainText();
        yapilanIslem = ui->yapilanIslem_->toPlainText();

        if(ui->donanim_1->isChecked()) {
            malzemeler += ui->donanim_1->text() + ",";
        }if(ui->donanim_2->isChecked()) {
            malzemeler += ui->donanim_2->text() + ",";
        }if(ui->donanim_3->isChecked()) {
            malzemeler += ui->donanim_3->text() + ",";
        }if(ui->donanim_4->isChecked()) {
            malzemeler += ui->donanim_4->text() + ",";
        }if(ui->donanim_5->isChecked()) {
            malzemeler += ui->donanim_5->text() + ",";
        }if(ui->donanim_6->isChecked()) {
            malzemeler += ui->donanim_6->text() + ",";
        }if(ui->donanim_7->isChecked()) {
            malzemeler += ui->donanim_7->text() + ",";
        }if(ui->donanim_8->isChecked()) {
            malzemeler += ui->donanim_8->text() + ",";
        }if(ui->donanim_9->isChecked()) {
            malzemeler += ui->donanim_9->text() + ",";
        }if(ui->donanim_10->isChecked()) {
            malzemeler += ui->donanim_10->text() + ",";
        }if(ui->donanim_11->isChecked()) {
            malzemeler += ui->donanim_11->text();
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
        notlar = ui->notlar_->toPlainText();

        QSqlQuery qry;

        qry.prepare("INSERT INTO teknikservis(`Cihaz Seri No`,`Tarih`,"
                    "`Saat`,`Müşteri Adı`,`Olay`,`Arıza Tarifi`,`Yapılan İşlem`,"
                    "`Cihazla Gelen Malzemeler`,`Degisen Parcalar`,`Test Süresi`,`Notlar`)"
                    "VALUES(:servisNo,:tarih,"
                    ":saat,:musteriAdi,:olay,:arizaTarifi,:yapilanIslem,"
                    ":malzemeler,:degisenParcalar,:testSuresi,:notlar)");
        qry.bindValue(":servisNo",servisNo);
        qry.bindValue(":tarih",tarih);
        qry.bindValue(":saat",saat);
        qry.bindValue(":musteriAdi",musteriAdi);
        qry.bindValue(":olay",olay);
        qry.bindValue(":arizaTarifi",arizaTarifi);
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

        this->close();
    }else {
        QMessageBox::information(this, "Not Connected", "Database Is Not Connected");
    }



}


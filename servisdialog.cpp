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

    ui->sevkTarihiDay_->setMaximum(31);
    ui->sevkTarihiDay_->setMinimum(1);
    ui->sevkTarihiDay_->setButtonSymbols(QAbstractSpinBox::NoButtons);
    ui->sevkTarihiMonth_->setButtonSymbols(QAbstractSpinBox::NoButtons);
    ui->sevkTarihiMonth_->setMaximum(12);
    ui->sevkTarihiMonth_->setMinimum(1);
    ui->sevkTarihiYear_->setButtonSymbols(QAbstractSpinBox::NoButtons);
    ui->sevkTarihiYear_->setMaximum(QDate::currentDate().year());
    ui->sevkTarihiYear_->setMinimum(1);
    ui->sevkTarihiDay_->clear();
    ui->sevkTarihiMonth_->clear();
    ui->sevkTarihiYear_->clear();

    ui->bitisTarihiDay_->setMaximum(31);
    ui->bitisTarihiDay_->setMinimum(1);
    ui->bitisTarihiDay_->setButtonSymbols(QAbstractSpinBox::NoButtons);
    ui->bitisTarihiMonth_->setButtonSymbols(QAbstractSpinBox::NoButtons);
    ui->bitisTarihiMonth_->setMaximum(12);
    ui->bitisTarihiMonth_->setMinimum(1);
    ui->bitisTarihiYear_->setButtonSymbols(QAbstractSpinBox::NoButtons);
    ui->bitisTarihiYear_->setMaximum(QDate::currentDate().year());
    ui->bitisTarihiYear_->setMinimum(1);
    ui->bitisTarihiDay_->clear();
    ui->bitisTarihiMonth_->clear();
    ui->bitisTarihiYear_->clear();

}
ServisDialog::~ServisDialog()
{
    delete ui;
}
void ServisDialog::initialize(QSqlDatabase d,QString sNo) {
    ui->servisNo_->setText(sNo);
    database = d;
}
void ServisDialog::on_pushButton_clicked()
{

    if(database.open()) {

        servisNo = ui->servisNo_->text();
        gelisTarihi = ui->gelisTarihiYear_->text() + "-" + ui->gelisTarihiMonth_->text() + "-" + ui->gelisTarihiDay_->text();
        musteriAdi = ui->musteriAdi_->text();
        arizaTarifi = ui->arizaTanimi_->text();
        yapilanIslem = ui->yapilanIslem_->text();
        malzemeler = "";

        if(ui->donanim_1->isChecked()) {
            malzemeler += ui->donanim_1->text() + ", ";
        }if(ui->donanim_2->isChecked()) {
            malzemeler += ui->donanim_2->text() + ", ";
        }if(ui->donanim_3->isChecked()) {
            malzemeler += ui->donanim_3->text() + ", ";
        }if(ui->donanim_4->isChecked()) {
            malzemeler += ui->donanim_4->text() + ", ";
        }if(ui->donanim_5->isChecked()) {
            malzemeler += ui->donanim_5->text() + ", ";
        }if(ui->donanim_6->isChecked()) {
            malzemeler += ui->donanim_6->text() + ", ";
        }if(ui->donanim_7->isChecked()) {
            malzemeler += ui->donanim_7->text() + ", ";
        }if(ui->donanim_8->isChecked()) {
            malzemeler += ui->donanim_8->text() + ", ";
        }if(ui->donanim_9->isChecked()) {
            malzemeler += ui->donanim_9->text() + ", ";
        }if(ui->donanim_10->isChecked()) {
            malzemeler += ui->donanim_10->text() + ", ";
        }if(ui->donanim_11->isChecked()) {
            malzemeler += ui->donanim_11->text();
        }
        tamirBitisTarihi = ui->bitisTarihiDay_->text(); + "." + ui->bitisTarihiMonth_->text() + "." + ui->bitisTarihiYear_->text();
        testSuresi = ui->testSuresi_->text();
        sevkTarihi = ui->sevkTarihiDay_->text() + "." + ui->sevkTarihiMonth_->text() + "." + ui->sevkTarihiYear_->text();
        notlar = ui->notlar_->toPlainText();

        QSqlQuery qry;

        qry.prepare("INSERT INTO teknikservis(`Cihaz Seri No`,`Geliş Tarihi`,"
                    "`Müşteri Adı`,`Arıza Tarifi`,`Yapılan İşlem`,`Cihazla Gelen Malzemeler`,"
                    "`Tamir Bitiş Tarihi`,`Test Süresi`,`Sevk Tarihi`,`Notlar`)"
                    "VALUES(:servisNo,:uidNo,:gelisTarihi,"
                    ":musteriAdi,:arizaTarifi,:yapilanIslem,:malzemeler,"
                    ":tamirBitisTarih,:testSuresi,:sevkTarihi,:notlar)");
        qry.bindValue(":servisNo",servisNo);
        qry.bindValue(":gelisTarihi",gelisTarihi);
        qry.bindValue(":musteriAdi",musteriAdi);
        qry.bindValue(":arizaTarifi",arizaTarifi);
        qry.bindValue(":yapilanIslem",yapilanIslem);
        qry.bindValue(":malzemeler",malzemeler);
        qry.bindValue(":tamirBitisTarih",tamirBitisTarihi);
        qry.bindValue(":testSuresi",testSuresi);
        qry.bindValue(":sevkTarihi",sevkTarihi);
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


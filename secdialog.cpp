#include "secdialog.h"
#include "ui_secdialog.h"
#include <QMessageBox>
#include <QSqlQuery>
#include "mainwindow.h"
#include "lineeditpopupform.h"
#include <QVBoxLayout>
#include <QMenu>
#include <QComboBox>

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
    QStringList commandsAnakartNo = {"MDO-01-v02-6-b/2013","MHD-b1-v0.1/2014","MHD-b1-v02015sp0004/"};
    ui->anakart_->addItems(commandsAnakartNo);
    connect(ui->anakart_, &QComboBox::currentTextChanged, this, &SecDialog::commandChanged);
    QStringList commandsModemKart = {"MD10-02-v04/2012","MHD-B2-v0.1/2014","MHD-B2-v0.1/000"};
    ui->modem_karti_->addItems(commandsModemKart);
    connect(ui->modem_karti_, &QComboBox::currentTextChanged, this, &SecDialog::commandChangedModemKart);
    QStringList commandsDurum = {"SATIŞ","DEMO","STOK"};
    ui->durum_->addItems(commandsDurum);
    connect(ui->durum_, &QComboBox::currentTextChanged, this, &SecDialog::commandChangedDurum);
    QStringList commandsSarjKarti = {"MHD-B7-v.0.0","MHD-B7-v2"};
    ui->sarj_karti_->addItems(commandsSarjKarti);
    connect(ui->sarj_karti_, &QComboBox::currentTextChanged, this, &SecDialog::commandChangedSarjKarti);
    QStringList commandsLcdKarti = {"MHD-B5-v0.0/811/2014","MHD-B5-v0.0"};
    ui->lcd_karti_->addItems(commandsLcdKarti);
    connect(ui->lcd_karti_, &QComboBox::currentTextChanged, this, &SecDialog::commandChangedLcdKarti);
    QStringList commandsModel = {"ML33+ Modeo Cihazı","Mobiot Cihazı","Server Cihazı","ML33 Modeo Cihazı","ML22 Modeo Cihazı","ML21 Modeo Cihazı","ML11 Modeo Cihazı"};
    ui->model_->addItems(commandsModel);
    connect(ui->model_, &QComboBox::currentTextChanged, this, &SecDialog::commandChangedModel);
    QStringList testDurum = {"Test Edilecek","Lab Testi Yapıldı","Saha Testi Yapıldı"};
    ui->test_durum_->addItems(testDurum);
    connect(ui->test_durum_, &QComboBox::currentTextChanged, this, &SecDialog::commandChangedTestDurum);
}
void SecDialog::commandChangedModel(const QString& command_text) {
    model = command_text;
}
void SecDialog::commandChangedLcdKarti(const QString& command_text) {
    lcdKarti = command_text;
}
void SecDialog::commandChangedSarjKarti(const QString& command_text) {
    sarjKarti = command_text;
}
void SecDialog::commandChangedDurum(const QString& command_text) {
    durum = command_text;
}
void SecDialog::commandChanged(const QString& command_text) {
    anakartNo = command_text;
}
void SecDialog::commandChangedModemKart(const QString& command_text) {
    modemKarti = command_text;
}
void SecDialog::initialize(QSqlDatabase d) {
    database = d;
}
void SecDialog::commandChangedTestDurum(const QString& command_text) {
    testDurumu = command_text;
}

void SecDialog::on_pushButton_clicked()
{

    if(database.isOpen()) {

        QString cihazSeriNo = ui->cihaz_seri_no->text();
        QString uidNo = ui->UIDNo_1->text();       
        QString uretimTarihi = ui->date_day->text() + "." + ui->date_month->text() + "." + ui->date_year->text();
        QString modemSeri1 = ui->modemSeri1_->text();
        QString modemSeri2 = ui->modemSeri2_->text();
        QString modemSeri3 = ui->modemSeri3_->text();
        QString modemSeri4 = ui->modemSeri4_->text();
        QString modemSeri5 = ui->modemSeri5_->text();
        QString modemSeri6 = ui->modemSeri6_->text();
        QString notlar = ui->notlar_->toPlainText();

        if(ui->modemSeri1_->text().length() == 15 && ui->modemSeri2_->text().length() == 15 && ui->modemSeri3_->text().length() == 15 &&
                ui->modemSeri4_->text().length() == 15 && ui->modemSeri5_->text().length() == 15 && ui->modemSeri6_->text().length() == 15) {
            checkIMEI = true;
        }if(ui->cihaz_seri_no->text().length() == 9) {
            checkSeriNo = true;
        }if(ui->UIDNo_1->text().length() == 12) {
            checkUIDNo = true;
        }

        QSqlQuery qry;

        qry.prepare("INSERT INTO cihazkimlik(`Model`,`Cihaz Seri No`,`Anakart No`,"
                    "`UID No`,`Modem Kartı`,`Lcd Kartı`,`Şarj Kartı`,`Durumu`,`Modem Seri Num 1`,"
                    "`Modem Seri Num 2`,`Modem Seri Num 3`,`Modem Seri Num 4`,`Modem Seri Num 5`,"
                    "`Modem Seri Num 6`,`Uretim Tarihi`,`Test Durumu`,`Notlar`) "
                    "VALUES(:model,:cihazSeriNo,:anakartNo,:uidNo,"
                    ":modemKarti,:lcdKarti,:sarjKarti,:durumu,:modemSeriNum1,"
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
        qry.bindValue(":modemSeriNum1",modemSeri1);
        qry.bindValue(":modemSeriNum2",modemSeri2);
        qry.bindValue(":modemSeriNum3",modemSeri3);
        qry.bindValue(":modemSeriNum4",modemSeri4);
        qry.bindValue(":modemSeriNum5",modemSeri5);
        qry.bindValue(":modemSeriNum6",modemSeri6);
        qry.bindValue(":uretimTarihi",uretimTarihi);
        qry.bindValue(":testDurumu",testDurumu);
        qry.bindValue(":notlar",notlar);
        if(checkIMEI && checkSeriNo && checkUIDNo) {
            if(qry.exec()) {
                QMessageBox::information(this,"Inserted","Data Inserted Succesfully");
                this->close();
            }else {
                QMessageBox::information(this,"Not Inserted",qry.lastError().text());
            }
        }else {
            QMessageBox::information(this,"Error","IMEI, UIDNo, Cihaz Seri No bilgileri eksik!!");
        }

    }else {
        QMessageBox::information(this, "Not Connected", "Database Is Not Connected");
        cout << "Database not connected!" << endl;
    }

}



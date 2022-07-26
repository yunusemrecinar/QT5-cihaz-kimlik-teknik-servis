#include "informationdialog.h"
#include "ui_informationdialog.h"
#include "mainwindow.h"
#include <iostream>
using namespace std;

InformationDialog::InformationDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::InformationDialog)
{
    ui->setupUi(this);
    changes();
    this->setWindowTitle(" ");

}



InformationDialog::~InformationDialog()
{
    delete ui;
}
void InformationDialog::initialize(QString s,QSqlDatabase d) {
    database = d;
    seriNo = s;

    if(database.isOpen()) {

        QSqlQuery* qry = new QSqlQuery(database);

        qry ->prepare("select * from cihazkimlik where `Cihaz Seri No` = '" + seriNo + "'");

        if(qry->exec()) {
            while(qry->next()) {
                ui->model_1->setCurrentText(qry->value(0).toString());
                ui->cihaz_seri_no_2->setText(qry->value(1).toString());
                ui->anakart_1->setCurrentText(qry->value(2).toString());
                ui->UIDNo_1->setText(qry->value(3).toString());
                ui->modem_karti_1->setCurrentText(qry->value(4).toString());
                ui->lcd_karti_1->setCurrentText(qry->value(5).toString());
                ui->sarj_karti_1->setCurrentText(qry->value(6).toString());
                ui->durum_1->setCurrentText(qry->value(7).toString());
                ui->modemSeri1_1->setText(qry->value(8).toString());
                ui->modemSeri2_1->setText(qry->value(9).toString());
                ui->modemSeri3_1->setText(qry->value(10).toString());
                ui->modemSeri4_1->setText(qry->value(11).toString());
                ui->modemSeri5_1->setText(qry->value(12).toString());
                ui->modemSeri6_1->setText(qry->value(13).toString());

                if(qry->value(14).toString().contains(".")) {
                    QList<QString> date = qry->value(14).toString().split(".");
                    ui->date_day->setValue(date.at(0).toInt());
                    ui->date_month->setValue(date.at(1).toInt());
                    ui->date_year->setValue(date.at(2).toInt());
                }
                ui->test_durum_->setCurrentText(qry->value(15).toString());
                ui->notlar_1->setText(qry->value(16).toString());
                oldModel = ui->model_1->currentText();
                oldLcdKart = ui->lcd_karti_1->currentText();
                oldSarjKart = ui->sarj_karti_1->currentText();
                oldDurum = ui->durum_1->currentText();
                oldAnakartNo = ui->anakart_1->currentText();
                oldModemKart = ui->modem_karti_1->currentText();
                oldTestDurum = ui->test_durum_->currentText();
                oldUidNo = ui->UIDNo_1->text();
            }
        }else {
            QMessageBox::critical(this, tr("error::"), qry->lastError().text());
        }

    }else {
        QMessageBox::information(this, "Not Connected", "Database Is Not Connected1");
        cout << "Database not connected!" << endl;
    }
    //database.close();
}
void InformationDialog::changes() {
    ui->cihaz_seri_no_2->setMaxLength(9);
    ui->cihaz_seri_no_2->setValidator(new QRegularExpressionValidator(QRegularExpression("\\d*")));
    ui->UIDNo_1->setMaxLength(12);
    ui->modemSeri1_1->setMaxLength(15);
    ui->modemSeri2_1->setMaxLength(15);
    ui->modemSeri3_1->setMaxLength(15);
    ui->modemSeri4_1->setMaxLength(15);
    ui->modemSeri5_1->setMaxLength(15);
    ui->modemSeri6_1->setMaxLength(15);
    ui->modemSeri1_1->setValidator(new QRegularExpressionValidator(QRegularExpression("\\d*")));
    ui->modemSeri2_1->setValidator(new QRegularExpressionValidator(QRegularExpression("\\d*")));
    ui->modemSeri3_1->setValidator(new QRegularExpressionValidator(QRegularExpression("\\d*")));
    ui->modemSeri4_1->setValidator(new QRegularExpressionValidator(QRegularExpression("\\d*")));
    ui->modemSeri5_1->setValidator(new QRegularExpressionValidator(QRegularExpression("\\d*")));
    ui->modemSeri6_1->setValidator(new QRegularExpressionValidator(QRegularExpression("\\d*")));
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
    ui->anakart_1->addItems(commandsAnakartNo);
    connect(ui->anakart_1, &QComboBox::currentTextChanged, this, &InformationDialog::commandChanged);
    QStringList commandsModemKart = {"MD10-02-v04/2012","MHD-B2-v0.1/2014","MHD-B2-v0.1/000"};
    ui->modem_karti_1->addItems(commandsModemKart);
    connect(ui->modem_karti_1, &QComboBox::currentTextChanged, this, &InformationDialog::commandChangedModemKart);
    QStringList commandsDurum = {"SATIŞ","DEMO","STOK"};
    ui->durum_1->addItems(commandsDurum);
    connect(ui->anakart_1, &QComboBox::currentTextChanged, this, &InformationDialog::commandChangedDurum);
    QStringList commandsSarjKarti = {"MHD-B7-v.0.0","MHD-B7-v2"};
    ui->sarj_karti_1->addItems(commandsSarjKarti);
    connect(ui->sarj_karti_1, &QComboBox::currentTextChanged, this, &InformationDialog::commandChangedSarjKarti);
    QStringList commandsLcdKarti = {"MHD-B5-v0.0/811/2014","MHD-B5-v0.0"};
    ui->lcd_karti_1->addItems(commandsLcdKarti);
    connect(ui->lcd_karti_1, &QComboBox::currentTextChanged, this, &InformationDialog::commandChangedLcdKarti);
    QStringList commandsModel = {"Mobiot Cihazı","Server Cihazı","ML33+ Modeo Cihazı","ML33 Modeo Cihazı","ML22 Modeo Cihazı","ML21 Modeo Cihazı","ML11 Modeo Cihazı"};
    ui->model_1->addItems(commandsModel);
    connect(ui->model_1, &QComboBox::currentTextChanged, this, &InformationDialog::commandChangedModel);
    QStringList commandTestDurum = {"Test Edilecek","Lab Testi Yapıldı","Saha Testi Yapıldı"};
    ui->test_durum_->addItems(commandTestDurum);
    connect(ui->test_durum_, &QComboBox::currentTextChanged, this, &InformationDialog::commandChangedTestDurum);
}
void InformationDialog::commandChangedTestDurum(const QString& command_text) {
    durum = command_text;
}
void InformationDialog::commandChangedModel(const QString& command_text) {
    model = command_text;
}
void InformationDialog::commandChangedLcdKarti(const QString& command_text) {
    lcdKart = command_text;
}
void InformationDialog::commandChangedSarjKarti(const QString& command_text) {
    sarjKart = command_text;
}
void InformationDialog::commandChangedDurum(const QString& command_text) {
    durum = command_text;
}
void InformationDialog::commandChanged(const QString& command_text) {
    anakartNo = command_text;
}
void InformationDialog::commandChangedModemKart(const QString& command_text) {
    modemKart = command_text;
}

void InformationDialog::on_pushButton_clicked()
{


    if(database.isOpen()) {

        QSqlQuery qry;
        QString model = ui->model_1->currentText();
        QString anakartNo = ui->anakart_1->currentText();
        QString modemKart = ui->modem_karti_1->currentText();
        QString lcdKart = ui->lcd_karti_1->currentText();
        QString sarjKart = ui->sarj_karti_1->currentText();
        QString modemSeri1 = ui->modemSeri1_1->text();
        QString modemSeri2 = ui->modemSeri2_1->text();
        QString modemSeri3 = ui->modemSeri3_1->text();
        QString modemSeri4 = ui->modemSeri4_1->text();
        QString modemSeri5 = ui->modemSeri5_1->text();
        QString modemSeri6 = ui->modemSeri6_1->text();
        QString durum = ui->durum_1->currentText();
        QString uidNo = ui->UIDNo_1->text();
        QString uretimTarih;
        QString uretimTarihDay = ui->date_day->text();
        QString uretimTarihMonth = ui->date_month->text();
        QString uretimTarihYear = ui->date_year->text();
        uretimTarih = uretimTarihDay + "." + uretimTarihMonth + "." + uretimTarihYear;
        QString test = ui->test_durum_->currentText();
        QString notlar = ui->notlar_1->toPlainText();

        qry.prepare("UPDATE cihazkimlik SET `Model` = '" + model + "' WHERE `Cihaz Seri No` = '" + ui->cihaz_seri_no_2->text() + "';");
        qry.exec();
        qry.clear();
        qry.prepare("UPDATE cihazkimlik SET `Anakart No` = '" + anakartNo + "' WHERE `Cihaz Seri No` = '" + ui->cihaz_seri_no_2->text() + "';");
        qry.exec();
        qry.clear();
        qry.prepare("UPDATE cihazkimlik SET `Modem Kartı` = '" + modemKart + "' WHERE `Cihaz Seri No` = '" + ui->cihaz_seri_no_2->text() + "';");
        qry.exec();
        qry.clear();
        qry.prepare("UPDATE cihazkimlik SET `Lcd Kartı` = '" + lcdKart + "' WHERE `Cihaz Seri No` = '" + ui->cihaz_seri_no_2->text() + "';");
        qry.exec();
        qry.clear();
        qry.prepare("UPDATE cihazkimlik SET `Şarj Kartı` = '" + sarjKart + "' WHERE `Cihaz Seri No` = '" + ui->cihaz_seri_no_2->text() + "';");
        qry.exec();
        qry.clear();
        qry.prepare("UPDATE cihazkimlik SET `Durumu` = '" + durum + "' WHERE `Cihaz Seri No` = '" + ui->cihaz_seri_no_2->text() + "';");
        qry.exec();
        qry.clear();
        qry.prepare("UPDATE cihazkimlik SET `UID No` = '" + uidNo + "' WHERE `Cihaz Seri No` = '" + ui->cihaz_seri_no_2->text() + "';");
        qry.exec();
        qry.clear();
        qry.prepare("UPDATE cihazkimlik SET `Modem Seri Num 1` = '" + modemSeri1 + "' WHERE `Cihaz Seri No` = '" + ui->cihaz_seri_no_2->text() + "';");
        qry.exec();
        qry.clear();
        qry.prepare("UPDATE cihazkimlik SET `Modem Seri Num 2` = '" + modemSeri2 + "' WHERE `Cihaz Seri No` = '" + ui->cihaz_seri_no_2->text() + "';");
        qry.exec();
        qry.clear();
        qry.prepare("UPDATE cihazkimlik SET `Modem Seri Num 3` = '" + modemSeri3 + "' WHERE `Cihaz Seri No` = '" + ui->cihaz_seri_no_2->text() + "';");
        qry.exec();
        qry.clear();
        qry.prepare("UPDATE cihazkimlik SET `Modem Seri Num 4` = '" + modemSeri4 + "' WHERE `Cihaz Seri No` = '" + ui->cihaz_seri_no_2->text() + "';");
        qry.exec();
        qry.clear();
        qry.prepare("UPDATE cihazkimlik SET `Modem Seri Num 5` = '" + modemSeri5 + "' WHERE `Cihaz Seri No` = '" + ui->cihaz_seri_no_2->text() + "';");
        qry.exec();
        qry.clear();
        qry.prepare("UPDATE cihazkimlik SET `Modem Seri Num 6` = '" + modemSeri6 + "' WHERE `Cihaz Seri No` = '" + ui->cihaz_seri_no_2->text() + "';");
        qry.exec();
        qry.clear();
        qry.prepare("UPDATE cihazkimlik SET `Uretim Tarihi` = '" + uretimTarih + "' WHERE `Cihaz Seri No` = '" + ui->cihaz_seri_no_2->text() + "';");
        qry.exec();
        qry.clear();
        qry.prepare("UPDATE cihazkimlik SET `Test Durumu` = '" + test + "' WHERE `Cihaz Seri No` = '" + ui->cihaz_seri_no_2->text() + "';");
        qry.exec();
        qry.clear();        
        qry.prepare("UPDATE cihazkimlik SET `Notlar` = '" + notlar + "' WHERE `Cihaz Seri No` = '" + ui->cihaz_seri_no_2->text() + "';");

        //if(qry.exec()) {
        //    QMessageBox::information(this,"Inserted","Data Updated Succesfully");
        //}else {
        //    QMessageBox::critical(this, tr("error::"), qry.lastError().text());
        //}
        qry.clear();
        if(QString::compare(oldUidNo, ui->UIDNo_1->text(), Qt::CaseInsensitive)) {
            tarihLog = QString::number(QDate::currentDate().day()) + "." + QString::number(QDate::currentDate().month()) + "." + QString::number(QDate::currentDate().day()) ;
            qry.prepare("INSERT INTO `loglar` (`Cihaz Seri No`,`Tarih`,`Eski Deger`,`Yeni Deger`,`Değişen`)"
                        "VALUES(:seriNo,:tarih,:eskiDeger,:yeniDeger,:degisen)");
            qry.bindValue(":seriNo",ui->cihaz_seri_no_2->text());
            qry.bindValue(":tarih",tarihLog);
            qry.bindValue(":eskiDeger",oldUidNo);
            qry.bindValue(":yeniDeger",ui->UIDNo_1->text());
            qry.bindValue(":degisen","UIDNo Değişti");
            ui->Model_2->setText(QString::number(countUidNo));
            qry.exec();
            qry.clear();

        }if(QString::compare(oldDurum, ui->durum_1->currentText(), Qt::CaseInsensitive)) {
            qry.prepare("INSERT INTO loglar(`Cihaz Seri No`,`Tarih`,`Eski Deger`,`Yeni Deger`,`Değişen`)"
                        "VALUES(:seriNo,:tarih,:eskiDeger,:yeniDeger,:degisen)");
            tarihLog = QString::number(QDate::currentDate().day()) + "." + QString::number(QDate::currentDate().month()) + "." + QString::number(QDate::currentDate().day()) ;
            qry.bindValue(":seriNo",ui->cihaz_seri_no_2->text());
            qry.bindValue(":tarih",tarihLog);
            qry.bindValue(":eskiDeger",oldDurum);
            qry.bindValue(":yeniDeger",ui->durum_1->currentText());
            qry.bindValue(":degisen","Durum Değişti");
            qry.exec();
            qry.clear();
        }if(QString::compare(oldTestDurum, ui->test_durum_->currentText(), Qt::CaseInsensitive)) {
            qry.prepare("INSERT INTO loglar(`Cihaz Seri No`,`Tarih`,`Eski Deger`,`Yeni Deger`,`Değişen`)"
                        "VALUES(:seriNo,:tarih,:eskiDeger,:yeniDeger,:degisen)");
            tarihLog = QString::number(QDate::currentDate().day()) + "." + QString::number(QDate::currentDate().month()) + "." + QString::number(QDate::currentDate().day()) ;
            qry.bindValue(":seriNo",ui->cihaz_seri_no_2->text());
            qry.bindValue(":tarih",tarihLog);
            qry.bindValue(":eskiDeger",oldTestDurum);
            qry.bindValue(":yeniDeger",ui->test_durum_->currentText());
            qry.bindValue(":degisen","Test Durum Değişti");
            qry.exec();
            qry.clear();

        }if(QString::compare(oldModemKart, ui->modem_karti_1->currentText(), Qt::CaseInsensitive)) {
            qry.prepare("INSERT INTO loglar(`Cihaz Seri No`,`Tarih`,`Eski Deger`,`Yeni Deger`,`Değişen`)"
                        "VALUES(:seriNo,:tarih,:eskiDeger,:yeniDeger,:degisen)");
            tarihLog = QString::number(QDate::currentDate().day()) + "." + QString::number(QDate::currentDate().month()) + "." + QString::number(QDate::currentDate().day()) ;
            qry.bindValue(":seriNo",ui->cihaz_seri_no_2->text());
            qry.bindValue(":tarih",tarihLog);
            qry.bindValue(":eskiDeger",oldModemKart);
            qry.bindValue(":yeniDeger",ui->modem_karti_1->currentText());
            qry.bindValue(":degisen","Modem Kartı Değişti");
            qry.exec();
            qry.clear();

        }if(QString::compare(oldModel, ui->model_1->currentText(), Qt::CaseInsensitive)) {
            qry.prepare("INSERT INTO loglar(`Cihaz Seri No`,`Tarih`,`Eski Deger`,`Yeni Deger`,`Değişen`)"
                        "VALUES(:seriNo,:tarih,:eskiDeger,:yeniDeger,:degisen)");
            tarihLog = QString::number(QDate::currentDate().day()) + "." + QString::number(QDate::currentDate().month()) + "." + QString::number(QDate::currentDate().day()) ;
            qry.bindValue(":seriNo",ui->cihaz_seri_no_2->text());
            qry.bindValue(":tarih",tarihLog);
            qry.bindValue(":eskiDeger",oldModel);
            qry.bindValue(":yeniDeger",ui->model_1->currentText());
            qry.bindValue(":degisen","Model Değişti");
            qry.exec();
            qry.clear();

        }if(QString::compare(oldAnakartNo, ui->anakart_1->currentText(),Qt::CaseInsensitive)) {
            qry.prepare("INSERT INTO loglar(`Cihaz Seri No`,`Tarih`,`Eski Deger`,`Yeni Deger`,`Değişen`)"
                        "VALUES(:seriNo,:tarih,:eskiDeger,:yeniDeger,:degisen)");
            tarihLog = QString::number(QDate::currentDate().day()) + "." + QString::number(QDate::currentDate().month()) + "." + QString::number(QDate::currentDate().day()) ;
            qry.bindValue(":seriNo",ui->cihaz_seri_no_2->text());
            qry.bindValue(":tarih",tarihLog);
            qry.bindValue(":eskiDeger",oldAnakartNo);
            qry.bindValue(":yeniDeger",ui->anakart_1->currentText());
            qry.bindValue(":degisen","Anakart Değişti");
            qry.exec();
            qry.clear();

        }if(QString::compare(oldLcdKart, ui->lcd_karti_1->currentText(), Qt::CaseInsensitive)) {
            qry.prepare("INSERT INTO loglar(`Cihaz Seri No`,`Tarih`,`Eski Deger`,`Yeni Deger`,`Değişen`)"
                        "VALUES(:seriNo,:tarih,:eskiDeger,:yeniDeger,:degisen)");
            tarihLog = QString::number(QDate::currentDate().day()) + "." + QString::number(QDate::currentDate().month()) + "." + QString::number(QDate::currentDate().day()) ;
            qry.bindValue(":seriNo",ui->cihaz_seri_no_2->text());
            qry.bindValue(":tarih",tarihLog);
            qry.bindValue(":eskiDeger",oldLcdKart);
            qry.bindValue(":yeniDeger",ui->lcd_karti_1->currentText());
            qry.bindValue(":degisen","Lcd Kartı Değişti");
            qry.exec();
            qry.clear();

        }if(QString::compare(oldSarjKart, ui->sarj_karti_1->currentText(), Qt::CaseInsensitive)) {
            qry.prepare("INSERT INTO loglar(`Cihaz Seri No`,`Tarih`,`Eski Deger`,`Yeni Deger`,`Değişen`)"
                        "VALUES(:seriNo,:tarih,:eskiDeger,:yeniDeger,:degisen)");
            tarihLog = QString::number(QDate::currentDate().day()) + "." + QString::number(QDate::currentDate().month()) + "." + QString::number(QDate::currentDate().day()) ;
            qry.bindValue(":seriNo",ui->cihaz_seri_no_2->text());
            qry.bindValue(":tarih",tarihLog);
            qry.bindValue(":eskiDeger",oldSarjKart);
            qry.bindValue(":yeniDeger",ui->sarj_karti_1->currentText());
            qry.bindValue(":degisen","Şarj Kartı Değişti");
            qry.exec();
            qry.clear();

        }



    }else {
        QMessageBox::information(this, "Not Connected", "Database Is Not Connected");
        cout << "Database not connected!" << endl;
    }

    this->close();

}


void InformationDialog::on_anakart_1_currentTextChanged(const QString &arg1)
{
    countAnakart++;
}
void InformationDialog::on_model_1_currentTextChanged(const QString &arg1)
{
    countModel++;
}
void InformationDialog::on_modem_karti_1_currentTextChanged(const QString &arg1)
{
    countModemKarti++;
}
void InformationDialog::on_durum_1_currentTextChanged(const QString &arg1)
{
    countDurum++;
}
void InformationDialog::on_test_durum__currentTextChanged(const QString &arg1)
{
    countTestDurum++;
}
void InformationDialog::on_sarj_karti_1_currentTextChanged(const QString &arg1)
{
    countSarjKarti++;
}
void InformationDialog::on_lcd_karti_1_currentTextChanged(const QString &arg1)
{
    countLcdKarti++;
}
void InformationDialog::on_UIDNo_1_textChanged(const QString &arg1)
{
    countUidNo++;
}


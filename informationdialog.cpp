#include "informationdialog.h"
#include "ui_informationdialog.h"
#include "mainwindow.h"
#include <iostream>
#include <QTime>

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

        QList<QString> commandsMusteri;
        commandsMusteri.append("LAB");
        qry ->prepare("select * from müsteri");
        if(qry -> exec()) {
            while(qry->next()) {commandsMusteri.append(qry->value(1).toString());}
        }
        ui->musteriAdi_->addItems(commandsMusteri);
        connect(ui->musteriAdi_, &QComboBox::currentTextChanged, this, &InformationDialog::commandChangedMusteriAdi);

        qry->clear();

        qry ->prepare("select * from cihazkimlik where `Cihaz Seri No` = '" + seriNo + "'");

        if(qry->exec()) {
            while(qry->next()) {
                ui->model_1->setCurrentText(qry->value(1).toString());
                ui->cihaz_seri_no_2->setText(qry->value(2).toString());
                ui->anakart_1->setText(qry->value(3).toString());
                ui->UIDNo_1->setText(qry->value(4).toString());
                ui->modem_karti_1->setText(qry->value(5).toString());
                ui->lcd_karti_1->setText(qry->value(6).toString());
                ui->sarj_karti_1->setText(qry->value(7).toString());
                ui->durum_1->setCurrentText(qry->value(8).toString());
                ui->modemTipi_->setCurrentText(qry->value(9).toString());
                ui->musteriAdi_->setCurrentText(qry->value(10).toString());
                ui->modemSeri1_1->setText(qry->value(11).toString());
                ui->modemSeri2_1->setText(qry->value(12).toString());
                ui->modemSeri3_1->setText(qry->value(13).toString());
                ui->modemSeri4_1->setText(qry->value(14).toString());
                ui->modemSeri5_1->setText(qry->value(15).toString());
                ui->modemSeri6_1->setText(qry->value(16).toString());

                if(qry->value(17).toString().contains(".")) {
                    QList<QString> date = qry->value(17).toString().split(".");
                    ui->date_day->setValue(date.at(0).toInt());
                    ui->date_month->setValue(date.at(1).toInt());
                    ui->date_year->setValue(date.at(2).toInt());
                }
                ui->test_durum_->setCurrentText(qry->value(18).toString());
                ui->notlar_1->setText(qry->value(19).toString());
                oldModel = ui->model_1->currentText();
                oldLcdKart = ui->lcd_karti_1->text();
                oldSarjKart = ui->sarj_karti_1->text();
                oldModemTipi = ui->modemTipi_->currentText();
                oldDurum = ui->durum_1->currentText();
                oldAnakartNo = ui->anakart_1->text();
                oldModemKart = ui->modem_karti_1->text();
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

    QStringList commandsDurum = {"SATIŞ","DEMO","STOK"};
    ui->durum_1->addItems(commandsDurum);
    connect(ui->durum_1, &QComboBox::currentTextChanged, this, &InformationDialog::commandChangedDurum);

    QStringList commandsModel = {"Mobiot Cihazı","Server Cihazı","ML33+ Modeo Cihazı","ML33 Modeo Cihazı","ML22 Modeo Cihazı","ML21 Modeo Cihazı","ML11 Modeo Cihazı"};
    ui->model_1->addItems(commandsModel);
    connect(ui->model_1, &QComboBox::currentTextChanged, this, &InformationDialog::commandChangedModel);
    QStringList commandTestDurum = {"Test Edilecek","Lab Testi Yapıldı","Saha Testi Yapıldı"};
    ui->test_durum_->addItems(commandTestDurum);
    connect(ui->test_durum_, &QComboBox::currentTextChanged, this, &InformationDialog::commandChangedTestDurum);
    QStringList commandModemTipi = {"Sierra / MC7304","Quectel / EC25-EC","Simcom / SIM7600G"};
    ui->modemTipi_->addItems(commandModemTipi);
    connect(ui->modemTipi_, &QComboBox::currentTextChanged, this, &InformationDialog::commandChangedModemTipi);
}
void InformationDialog::commandChangedMusteriAdi(const QString& command_text) {
    musteriAdi = command_text;
}
void InformationDialog::commandChangedModemTipi(const QString& command_text) {
    modemTipi = command_text;
}
void InformationDialog::commandChangedTestDurum(const QString& command_text) {
    durum = command_text;
}
void InformationDialog::commandChangedModel(const QString& command_text) {
    model = command_text;
}
void InformationDialog::commandChangedDurum(const QString& command_text) {
    durum = command_text;
}



void InformationDialog::on_pushButton_clicked()
{


    if(database.isOpen()) {

        QSqlQuery qry;
        QString model = ui->model_1->currentText();
        QString anakartNo = ui->anakart_1->text();
        QString modemKart = ui->modem_karti_1->text();
        QString lcdKart = ui->lcd_karti_1->text();
        QString sarjKart = ui->sarj_karti_1->text();
        musteriAdi = ui->musteriAdi_->currentText();
        QString modemSeri1 = ui->modemSeri1_1->text();
        QString modemSeri2 = ui->modemSeri2_1->text();
        QString modemSeri3 = ui->modemSeri3_1->text();
        QString modemSeri4 = ui->modemSeri4_1->text();
        QString modemSeri5 = ui->modemSeri5_1->text();
        QString modemSeri6 = ui->modemSeri6_1->text();
        QString durum = ui->durum_1->currentText();
        modemTipi = ui->modemTipi_->currentText();
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
        qry.prepare("UPDATE cihazkimlik SET `Müşteri Adı` = '" + musteriAdi + "' WHERE `Cihaz Seri No` = '" + ui->cihaz_seri_no_2->text() + "';");
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
        qry.prepare("UPDATE cihazkimlik SET `Modem Tipi` = '" + modemTipi + "' WHERE `Cihaz Seri No` = '" + ui->cihaz_seri_no_2->text() + "';");
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
        qry.exec();

        qry.clear();
        if(QString::compare(oldUidNo, ui->UIDNo_1->text(), Qt::CaseInsensitive)) {
            tarihLog = QString::number(QDate::currentDate().day()) + "." + QString::number(QDate::currentDate().month()) + "." + QString::number(QDate::currentDate().day()) + "  "
                    + QString::number(QTime::currentTime().hour()) + ":" + QString::number(QTime::currentTime().minute());
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
            tarihLog = QString::number(QDate::currentDate().day()) + "." + QString::number(QDate::currentDate().month()) + "." + QString::number(QDate::currentDate().day()) + "  "
                    + QString::number(QTime::currentTime().hour()) + ":" + QString::number(QTime::currentTime().minute());qry.bindValue(":seriNo",ui->cihaz_seri_no_2->text());
            qry.bindValue(":tarih",tarihLog);
            qry.bindValue(":eskiDeger",oldDurum);
            qry.bindValue(":yeniDeger",ui->durum_1->currentText());
            qry.bindValue(":degisen","Durum Değişti");
            qry.exec();
            qry.clear();
        }if(QString::compare(oldModemTipi, ui->modemTipi_->currentText(), Qt::CaseInsensitive)) {
            qry.prepare("INSERT INTO loglar(`Cihaz Seri No`,`Tarih`,`Eski Deger`,`Yeni Deger`,`Değişen`)"
                        "VALUES(:seriNo,:tarih,:eskiDeger,:yeniDeger,:degisen)");
            tarihLog = QString::number(QDate::currentDate().day()) + "." + QString::number(QDate::currentDate().month()) + "." + QString::number(QDate::currentDate().day()) + "  "
                    + QString::number(QTime::currentTime().hour()) + ":" + QString::number(QTime::currentTime().minute());qry.bindValue(":seriNo",ui->cihaz_seri_no_2->text());
            qry.bindValue(":tarih",tarihLog);
            qry.bindValue(":eskiDeger",oldModemTipi);
            qry.bindValue(":yeniDeger",ui->modemTipi_->currentText());
            qry.bindValue(":degisen","Modem Tipi Değişti");
            qry.exec();
            qry.clear();
        }if(QString::compare(oldTestDurum, ui->test_durum_->currentText(), Qt::CaseInsensitive)) {
            qry.prepare("INSERT INTO loglar(`Cihaz Seri No`,`Tarih`,`Eski Deger`,`Yeni Deger`,`Değişen`)"
                        "VALUES(:seriNo,:tarih,:eskiDeger,:yeniDeger,:degisen)");
            tarihLog = QString::number(QDate::currentDate().day()) + "." + QString::number(QDate::currentDate().month()) + "." + QString::number(QDate::currentDate().day()) + "  "
                    + QString::number(QTime::currentTime().hour()) + ":" + QString::number(QTime::currentTime().minute());qry.bindValue(":seriNo",ui->cihaz_seri_no_2->text());
            qry.bindValue(":tarih",tarihLog);
            qry.bindValue(":eskiDeger",oldTestDurum);
            qry.bindValue(":yeniDeger",ui->test_durum_->currentText());
            qry.bindValue(":degisen","Test Durum Değişti");
            qry.exec();
            qry.clear();

        }if(QString::compare(oldModemKart, ui->modem_karti_1->text(), Qt::CaseInsensitive)) {
            qry.prepare("INSERT INTO loglar(`Cihaz Seri No`,`Tarih`,`Eski Deger`,`Yeni Deger`,`Değişen`)"
                        "VALUES(:seriNo,:tarih,:eskiDeger,:yeniDeger,:degisen)");
            tarihLog = QString::number(QDate::currentDate().day()) + "." + QString::number(QDate::currentDate().month()) + "." + QString::number(QDate::currentDate().day()) + "  "
                    + QString::number(QTime::currentTime().hour()) + ":" + QString::number(QTime::currentTime().minute());qry.bindValue(":seriNo",ui->cihaz_seri_no_2->text());
            qry.bindValue(":tarih",tarihLog);
            qry.bindValue(":eskiDeger",oldModemKart);
            qry.bindValue(":yeniDeger",ui->modem_karti_1->text());
            qry.bindValue(":degisen","Modem Kartı Değişti");
            qry.exec();
            qry.clear();

        }if(QString::compare(oldModel, ui->model_1->currentText(), Qt::CaseInsensitive)) {
            qry.prepare("INSERT INTO loglar(`Cihaz Seri No`,`Tarih`,`Eski Deger`,`Yeni Deger`,`Değişen`)"
                        "VALUES(:seriNo,:tarih,:eskiDeger,:yeniDeger,:degisen)");
            tarihLog = QString::number(QDate::currentDate().day()) + "." + QString::number(QDate::currentDate().month()) + "." + QString::number(QDate::currentDate().day()) + "  "
                    + QString::number(QTime::currentTime().hour()) + ":" + QString::number(QTime::currentTime().minute());qry.bindValue(":seriNo",ui->cihaz_seri_no_2->text());
            qry.bindValue(":tarih",tarihLog);
            qry.bindValue(":eskiDeger",oldModel);
            qry.bindValue(":yeniDeger",ui->model_1->currentText());
            qry.bindValue(":degisen","Model Değişti");
            qry.exec();
            qry.clear();

        }if(QString::compare(oldAnakartNo, ui->anakart_1->text(),Qt::CaseInsensitive)) {
            qry.prepare("INSERT INTO loglar(`Cihaz Seri No`,`Tarih`,`Eski Deger`,`Yeni Deger`,`Değişen`)"
                        "VALUES(:seriNo,:tarih,:eskiDeger,:yeniDeger,:degisen)");
            tarihLog = QString::number(QDate::currentDate().day()) + "." + QString::number(QDate::currentDate().month()) + "." + QString::number(QDate::currentDate().day()) + "  "
                    + QString::number(QTime::currentTime().hour()) + ":" + QString::number(QTime::currentTime().minute());qry.bindValue(":seriNo",ui->cihaz_seri_no_2->text());
            qry.bindValue(":tarih",tarihLog);
            qry.bindValue(":eskiDeger",oldAnakartNo);
            qry.bindValue(":yeniDeger",ui->anakart_1->text());
            qry.bindValue(":degisen","Anakart Değişti");
            qry.exec();
            qry.clear();

        }if(QString::compare(oldLcdKart, ui->lcd_karti_1->text(), Qt::CaseInsensitive)) {
            qry.prepare("INSERT INTO loglar(`Cihaz Seri No`,`Tarih`,`Eski Deger`,`Yeni Deger`,`Değişen`)"
                        "VALUES(:seriNo,:tarih,:eskiDeger,:yeniDeger,:degisen)");
            tarihLog = QString::number(QDate::currentDate().day()) + "." + QString::number(QDate::currentDate().month()) + "." + QString::number(QDate::currentDate().day()) + "  "
                    + QString::number(QTime::currentTime().hour()) + ":" + QString::number(QTime::currentTime().minute());qry.bindValue(":seriNo",ui->cihaz_seri_no_2->text());
            qry.bindValue(":tarih",tarihLog);
            qry.bindValue(":eskiDeger",oldLcdKart);
            qry.bindValue(":yeniDeger",ui->lcd_karti_1->text());
            qry.bindValue(":degisen","Lcd Kartı Değişti");
            qry.exec();
            qry.clear();

        }if(QString::compare(oldSarjKart, ui->sarj_karti_1->text(), Qt::CaseInsensitive)) {
            qry.prepare("INSERT INTO loglar(`Cihaz Seri No`,`Tarih`,`Eski Deger`,`Yeni Deger`,`Değişen`)"
                        "VALUES(:seriNo,:tarih,:eskiDeger,:yeniDeger,:degisen)");
            tarihLog = QString::number(QDate::currentDate().day()) + "." + QString::number(QDate::currentDate().month()) + "." + QString::number(QDate::currentDate().day()) + "  "
                    + QString::number(QTime::currentTime().hour()) + ":" + QString::number(QTime::currentTime().minute());qry.bindValue(":seriNo",ui->cihaz_seri_no_2->text());
            qry.bindValue(":tarih",tarihLog);
            qry.bindValue(":eskiDeger",oldSarjKart);
            qry.bindValue(":yeniDeger",ui->sarj_karti_1->text());
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



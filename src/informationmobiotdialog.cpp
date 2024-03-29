#include "informationmobiotdialog.h"
#include "ui_informationmobiotdialog.h"
#include <QDate>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QMessageBox>
#include <QSqlError>

#include <iostream>
using namespace std;

InformationMobiotDialog::InformationMobiotDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::InformationMobiotDialog)
{
    ui->setupUi(this);
    changes();
}

InformationMobiotDialog::~InformationMobiotDialog()
{
    delete ui;
}
void InformationMobiotDialog::getMusteri() {

    if(database.isOpen()) {
        QSqlQuery* qry = new QSqlQuery(database);

        qry ->prepare("select İsim from cihazisim where `Cihaz Seri No` = '" + seriNo + "';");
        if(qry -> exec()){

                while(qry->next()) {
                    ui->musteriAdi_1->setText(qry->value(0).toString());
                }

        }else {
            QMessageBox::information(this,"Error", qry->lastError().text());
            setLog("[ERROR] informationdialog.cpp : " + qry->lastError().text());
        }


    }else {
        QMessageBox::information(this, "Not Connected", database.lastError().text());
        setLog("[ERROR] informationdialog.cpp : " + database.lastError().text());
        cout << "Database not connected!" << endl;
    }
}
void InformationMobiotDialog::initialize(QString s, QSqlDatabase d,QString user)
{
    seriNo = s;
    database = d;
    username = user;

    addModemTipi();

    if(database.isOpen()) {

        QSqlQuery* qry = new QSqlQuery(database);

        qry ->prepare("select * from cihazkimlikmobiot where `Cihaz Seri No` = '" + seriNo + "'");

        if(qry->exec()) {
            while(qry->next()) {
                ui->cihaz_seri_no->setText(qry->value(2).toString());
                ui->anakart_->setText(qry->value(3).toString());
                ui->UIDNo_1->setText(qry->value(4).toString());
                ui->test_durum_->setCurrentText(qry->value(5).toString());
                getMusteri();
                ui->durum_->setCurrentText(qry->value(7).toString());
                if(qry->value(8).toString().contains(".")) {
                    QList<QString> date = qry->value(8).toString().split(".");
                    ui->date_day->setValue(date.at(0).toInt());
                    ui->date_month->setValue(date.at(1).toInt());
                    ui->date_year->setValue(date.at(2).toInt());
                }
                ui->modemTipi_->setCurrentText(qry->value(9).toString());
                ui->modemSeri1_->setText(qry->value(10).toString());
                ui->modemSeri2_->setText(qry->value(11).toString());
                ui->modemSeri3_->setText(qry->value(12).toString());
                if(qry->value(13).toString().contains(".")) {
                    if(qry->value(13).toString().length() != 2) {
                        QList<QString> date = qry->value(13).toString().split(".");
                        ui->fatura_date_day_->setValue(date.at(0).toInt());
                        ui->fatura_date_month_->setValue(date.at(1).toInt());
                        ui->fatura_date_year_->setValue(date.at(2).toInt());
                    }else {
                        ui->fatura_date_year_->clear();
                        ui->fatura_date_day_->clear();
                        ui->fatura_date_month_->clear();
                    }

                }
                if(qry->value(14).toString().contains(".")) {
                    if(qry->value(14).toString().length() != 2) {
                        QList<QString> date = qry->value(14).toString().split(".");
                        ui->garanti_start_day_->setValue(date.at(0).toInt());
                        ui->garanti_start_month_->setValue(date.at(1).toInt());
                        ui->garanti_start_year_->setValue(date.at(2).toInt());
                    }else {
                        ui->garanti_start_year_->clear();
                        ui->garanti_start_month_->clear();
                        ui->garanti_start_day_->clear();
                    }
                }
                if(qry->value(15).toString().contains(".")) {
                    if(qry->value(15).toString().length() != 2) {
                        QList<QString> date = qry->value(15).toString().split(".");
                        ui->garanti_bitis_day_->setValue(date.at(0).toInt());
                        ui->garanti_bitis_month_->setValue(date.at(1).toInt());
                        ui->garanti_bitis_year_->setValue(date.at(2).toInt());
                    }else {
                        ui->garanti_bitis_year_->clear();
                        ui->garanti_bitis_day_->clear();
                        ui->garanti_bitis_month_->clear();
                    }
                }
                ui->notlar_->setText(qry->value(16).toString());

                oldModemTipi = ui->modemTipi_->currentText();
                oldDurum = ui->durum_->currentText();
                oldAnakartNo = ui->anakart_->text();
                oldTestDurum = ui->test_durum_->currentText();
                oldUidNo = ui->UIDNo_1->text();
            }
        }else {
            QMessageBox::critical(this, tr("error::"), qry->lastError().text());
            setLog("[ERROR] informationmobiotdialog.cpp : " + qry->lastError().text());
        }

    }else {
        QMessageBox::information(this, "Not Connected", "Database Is Not Connected1");
        setLog("[ERROR] informationmobiotdialog.cpp : " + database.lastError().text());
        cout << "Database not connected!" << endl;
    }
}

void InformationMobiotDialog::setLog(QString content) {

    QSqlQuery qry;
    QString date = QDateTime::currentDateTime().toString("dd.MM.yyyy hh:mm:ss");
    qry.prepare("INSERT INTO processlogs(`tarih`,`username`,`process`) VALUES (:tarih,:username,:process)");
    qry.bindValue(":tarih",date);
    qry.bindValue(":username",username);
    qry.bindValue(":process",content);
    qry.exec();
}
void InformationMobiotDialog::changes() {

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
    connect(ui->durum_, &QComboBox::currentTextChanged, this, &InformationMobiotDialog::commandChangedDurum);

    QStringList testDurum = {"Test Edilecek","Lab Testi Yapıldı","Saha Testi Yapıldı"};
    ui->test_durum_->addItems(testDurum);
    connect(ui->test_durum_, &QComboBox::currentTextChanged, this, &InformationMobiotDialog::commandChangedTestDurum);

}
void InformationMobiotDialog::commandChangedDurum(const QString& command_text) {
    durum = command_text;
}
void InformationMobiotDialog::commandChangedTestDurum(const QString& command_text) {
    testDurumu = command_text;
}

void InformationMobiotDialog::addModemTipi() {
    if(database.isOpen()) {
        QSqlQuery* qry = new QSqlQuery(database);
        qry ->prepare("select * from modemtipi");
        if(qry -> exec()) {
            while(qry->next()) {commandsModemTipi.append(qry->value(0).toString());}
        }else{
            setLog("[ERROR] informationmobiotdialog.cpp : " + qry->lastError().text());
        }
    }else {
        setLog("[ERROR] informationmobiotdialog.cpp : " + database.lastError().text());
    }
    ui->modemTipi_->addItems(commandsModemTipi);
    connect(ui->modemTipi_, &QComboBox::currentTextChanged, this, &InformationMobiotDialog::commandChangedModemTipi);
}

void InformationMobiotDialog::commandChangedModemTipi(const QString& command_text) {
    modemTipi = command_text;
}
void InformationMobiotDialog::commandChangedMusteriAdi(const QString& command_text) {
    musteriAdi = command_text;
}
void InformationMobiotDialog::on_pushButton_clicked()
{

    if(database.isOpen()) {

        QSqlQuery qry;
        QString model = ui->lineEdit->text();
        QString anakartNo = ui->anakart_->text();
        QString uidNo = ui->UIDNo_1->text();
        QString testDrm = ui->test_durum_->currentText();
        musteriAdi = ui->musteriAdi_1->text();
        QString durum = ui->durum_->currentText();
        QString uretimTarih;
        QString uretimTarihDay = ui->date_day->text();
        QString uretimTarihMonth = ui->date_month->text();
        QString uretimTarihYear = ui->date_year->text();
        uretimTarih = uretimTarihDay + "." + uretimTarihMonth + "." + uretimTarihYear;
        modemTipi = ui->modemTipi_->currentText();
        QString modemSeri1 = ui->modemSeri1_->text();
        QString modemSeri2 = ui->modemSeri2_->text();
        QString modemSeri3 = ui->modemSeri3_->text();
        QString faturaKesim = ui->fatura_date_day_->text() + "." + ui->fatura_date_month_->text() + "." + ui->fatura_date_year_->text();
        QString garantiStart = ui->garanti_start_day_->text() + "." + ui->garanti_start_month_->text() + "." + ui->garanti_start_year_->text();
        QString garantiBitis = ui->garanti_bitis_day_->text() + "." + ui->garanti_bitis_month_->text() + "." + ui->garanti_bitis_year_->text();
        QString notlar = ui->notlar_->toPlainText();

        qry.prepare("UPDATE cihazkimlikmobiot SET `Model` = '" + model + "' WHERE `Cihaz Seri No` = '" + seriNo + "';");
        qry.exec();
        qry.clear();
        qry.prepare("UPDATE cihazkimlikmobiot SET `Anakart No` = '" + anakartNo + "' WHERE `Cihaz Seri No` = '" + seriNo + "';");
        qry.exec();
        qry.clear();
        qry.prepare("UPDATE cihazkimlikmobiot SET `UID No` = '" + uidNo + "' WHERE `Cihaz Seri No` = '" + seriNo + "';");
        qry.exec();
        qry.clear();
        qry.prepare("UPDATE cihazkimlikmobiot SET `Test Durumu` = '" + testDrm + "' WHERE `Cihaz Seri No` = '" + seriNo + "';");
        qry.exec();
        qry.clear();
        qry.prepare("UPDATE cihazkimlikmobiot SET `Müşteri` = '" + musteriAdi + "' WHERE `Cihaz Seri No` = '" + seriNo + "';");
        qry.exec();
        qry.clear();
        qry.prepare("UPDATE cihazkimlikmobiot SET `Durum` = '" + durum + "' WHERE `Cihaz Seri No` = '" + seriNo + "';");
        qry.exec();
        qry.clear();
        qry.prepare("UPDATE cihazkimlikmobiot SET `Üretim Tarihi` = '" + uretimTarih + "' WHERE `Cihaz Seri No` = '" + seriNo + "';");
        qry.exec();
        qry.clear();
        qry.prepare("UPDATE cihazkimlikmobiot SET `Fatura Kesim` = '" + faturaKesim + "' WHERE `Cihaz Seri No` = '" + seriNo + "';");
        qry.exec();
        qry.clear();
        qry.prepare("UPDATE cihazkimlikmobiot SET `Garanti Baslangic` = '" + garantiStart + "' WHERE `Cihaz Seri No` = '" + seriNo + "';");
        qry.exec();
        qry.clear();
        qry.prepare("UPDATE cihazkimlikmobiot SET `Garanti Bitis` = '" + garantiBitis + "' WHERE `Cihaz Seri No` = '" + seriNo + "';");
        qry.exec();
        qry.clear();
        qry.prepare("UPDATE cihazkimlikmobiot SET `Modem Tipi` = '" + modemTipi + "' WHERE `Cihaz Seri No` = '" + seriNo + "';");
        qry.exec();
        qry.clear();
        qry.prepare("UPDATE cihazkimlikmobiot SET `IMEI 1` = '" + modemSeri1 + "' WHERE `Cihaz Seri No` = '" + seriNo + "';");
        qry.exec();
        qry.clear();
        qry.prepare("UPDATE cihazkimlikmobiot SET `IMEI 2` = '" + modemSeri2 + "' WHERE `Cihaz Seri No` = '" + seriNo + "';");
        qry.exec();
        qry.clear();
        qry.prepare("UPDATE cihazkimlikmobiot SET `IMEI 3` = '" + modemSeri3 + "' WHERE `Cihaz Seri No` = '" + seriNo + "';");
        qry.exec();
        qry.clear();
        qry.prepare("UPDATE cihazkimlikmobiot SET `Notlar` = '" + notlar + "' WHERE `Cihaz Seri No` = '" + seriNo + "';");
        qry.exec();

        qry.clear();
        if(QString::compare(oldUidNo, ui->UIDNo_1->text(), Qt::CaseInsensitive)) {
            tarihLog = QString::number(QDate::currentDate().day()) + "." + QString::number(QDate::currentDate().month()) + "." + QString::number(QDate::currentDate().year()) + "  "
                    + QString::number(QTime::currentTime().hour()) + ":" + QString::number(QTime::currentTime().minute());
            qry.prepare("INSERT INTO `loglar` (`Cihaz Seri No`,`Tarih`,`Eski Deger`,`Yeni Deger`,`Değişen`)"
                        "VALUES(:seriNo,:tarih,:eskiDeger,:yeniDeger,:degisen)");
            qry.bindValue(":seriNo",ui->cihaz_seri_no->text());
            qry.bindValue(":tarih",tarihLog);
            qry.bindValue(":eskiDeger",oldUidNo);
            qry.bindValue(":yeniDeger",ui->UIDNo_1->text());
            qry.bindValue(":degisen","UIDNo Değişti");
            if(qry.exec()) {
                setLog("[NOTE]" + ui->cihaz_seri_no->text() + " no'lu cihazın uid no'su değiştirildi.");
            }else {
                setLog("[ERROR] informationmobiotdialog.cpp : " + qry.lastError().text());
            }
            qry.clear();

        }if(QString::compare(oldDurum, ui->durum_->currentText(), Qt::CaseInsensitive)) {
            qry.prepare("INSERT INTO loglar(`Cihaz Seri No`,`Tarih`,`Eski Deger`,`Yeni Deger`,`Değişen`)"
                        "VALUES(:seriNo,:tarih,:eskiDeger,:yeniDeger,:degisen)");
            tarihLog = QString::number(QDate::currentDate().day()) + "." + QString::number(QDate::currentDate().month()) + "." + QString::number(QDate::currentDate().year()) + "  "
                    + QString::number(QTime::currentTime().hour()) + ":" + QString::number(QTime::currentTime().minute());
            qry.bindValue(":seriNo",ui->cihaz_seri_no->text());
            qry.bindValue(":tarih",tarihLog);
            qry.bindValue(":eskiDeger",oldDurum);
            qry.bindValue(":yeniDeger",ui->durum_->currentText());
            qry.bindValue(":degisen","Durum Değişti");
            if(qry.exec()) {
                setLog("[NOTE]" + ui->cihaz_seri_no->text() + " no'lu cihazın durumu değiştirildi.");
            }else {
                setLog("[ERROR] informationmobiotdialog.cpp : " + qry.lastError().text());
            }
            qry.clear();
        }if(QString::compare(oldModemTipi, ui->modemTipi_->currentText(), Qt::CaseInsensitive)) {
            qry.prepare("INSERT INTO loglar(`Cihaz Seri No`,`Tarih`,`Eski Deger`,`Yeni Deger`,`Değişen`)"
                        "VALUES(:seriNo,:tarih,:eskiDeger,:yeniDeger,:degisen)");
            tarihLog = QString::number(QDate::currentDate().day()) + "." + QString::number(QDate::currentDate().month()) + "." + QString::number(QDate::currentDate().year()) + "  "
                    + QString::number(QTime::currentTime().hour()) + ":" + QString::number(QTime::currentTime().minute());
            qry.bindValue(":seriNo",ui->cihaz_seri_no->text());
            qry.bindValue(":tarih",tarihLog);
            qry.bindValue(":eskiDeger",oldModemTipi);
            qry.bindValue(":yeniDeger",ui->modemTipi_->currentText());
            qry.bindValue(":degisen","Modem Tipi Değişti");
            if(qry.exec()) {
                setLog("[NOTE]" + ui->cihaz_seri_no->text() + " no'lu cihazın modem tipi değiştirildi.");
            }else {
                setLog("[ERROR] informationmobiotdialog.cpp : " + qry.lastError().text());
            }
            qry.clear();
        }if(QString::compare(oldTestDurum, ui->test_durum_->currentText(), Qt::CaseInsensitive)) {
            qry.prepare("INSERT INTO loglar(`Cihaz Seri No`,`Tarih`,`Eski Deger`,`Yeni Deger`,`Değişen`)"
                        "VALUES(:seriNo,:tarih,:eskiDeger,:yeniDeger,:degisen)");
            tarihLog = QString::number(QDate::currentDate().day()) + "." + QString::number(QDate::currentDate().month()) + "." + QString::number(QDate::currentDate().year()) + "  "
                    + QString::number(QTime::currentTime().hour()) + ":" + QString::number(QTime::currentTime().minute());
            qry.bindValue(":seriNo",ui->cihaz_seri_no->text());
            qry.bindValue(":tarih",tarihLog);
            qry.bindValue(":eskiDeger",oldTestDurum);
            qry.bindValue(":yeniDeger",ui->test_durum_->currentText());
            qry.bindValue(":degisen","Test Durum Değişti");
            if(qry.exec()) {
                setLog("[NOTE]" + ui->cihaz_seri_no->text() + " no'lu cihazın test durumu değiştirildi.");
            }else {
                setLog("[ERROR] informationmobiotdialog.cpp : " + qry.lastError().text());
            }
            qry.clear();

        }if(QString::compare(oldAnakartNo, ui->anakart_->text(),Qt::CaseInsensitive)) {
            qry.prepare("INSERT INTO loglar(`Cihaz Seri No`,`Tarih`,`Eski Deger`,`Yeni Deger`,`Değişen`)"
                        "VALUES(:seriNo,:tarih,:eskiDeger,:yeniDeger,:degisen)");
            tarihLog = QString::number(QDate::currentDate().day()) + "." + QString::number(QDate::currentDate().month()) + "." + QString::number(QDate::currentDate().year()) + "  "
                    + QString::number(QTime::currentTime().hour()) + ":" + QString::number(QTime::currentTime().minute());
            qry.bindValue(":seriNo",ui->cihaz_seri_no->text());
            qry.bindValue(":tarih",tarihLog);
            qry.bindValue(":eskiDeger",oldAnakartNo);
            qry.bindValue(":yeniDeger",ui->anakart_->text());
            qry.bindValue(":degisen","Anakart Değişti");
            if(qry.exec()) {
                setLog("[NOTE]" + ui->cihaz_seri_no->text() + " no'lu cihazın anakart no'su değiştirildi.");
            }else {
                setLog("[ERROR] informationmobiotdialog.cpp : " + qry.lastError().text());
            }
            qry.clear();

        }

    }else {
        QMessageBox::information(this, "Not Connected", "Database Is Not Connected");
        setLog("[ERROR] informationmobiotdialog.cpp : " + database.lastError().text());
        cout << "Database not connected!" << endl;
    }

    this->close();

}


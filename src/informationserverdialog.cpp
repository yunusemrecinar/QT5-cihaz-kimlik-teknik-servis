#include "informationserverdialog.h"
#include "ui_informationserverdialog.h"
#include <QDate>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>

#include <iostream>
using namespace std;

InformationServerDialog::InformationServerDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::InformationServerDialog)
{
    ui->setupUi(this);
    changes();
}

InformationServerDialog::~InformationServerDialog()
{
    delete ui;
}

void InformationServerDialog::initialize(QString s, QSqlDatabase d) {
    seriNo = s;
    database = d;

    addMusteri();

    if(database.isOpen()) {

        QSqlQuery* qry = new QSqlQuery(database);

        qry ->prepare("select * from cihazkimlikserver where `Cihaz Seri No` = '" + seriNo + "'");

        if(qry->exec()) {
            while(qry->next()) {
                ui->cihaz_seri_no->setText(qry->value(2).toString());
                ui->anakart_->setText(qry->value(3).toString());
                ui->UIDNo_1->setText(qry->value(4).toString());
                ui->islemci_->setText(qry->value(5).toString());
                ui->ram_->setText(qry->value(6).toString());
                ui->decklink_->setCurrentText(qry->value(7).toString());
                ui->kasaTipi_->setCurrentText(qry->value(8).toString());
                ui->test_durum_->setCurrentText(qry->value(9).toString());
                ui->musteriAdi_1->setCurrentText(qry->value(10).toString());
                ui->durum_->setCurrentText(qry->value(11).toString());
                if(qry->value(12).toString().contains(".")) {
                    QList<QString> date = qry->value(12).toString().split(".");
                    ui->date_day->setValue(date.at(0).toInt());
                    ui->date_month->setValue(date.at(1).toInt());
                    ui->date_year->setValue(date.at(2).toInt());
                }
                ui->hdd_->setText(qry->value(13).toString());
                ui->notlar_->setText(qry->value(14).toString());

                oldAnakartNo = ui->anakart_->text();
                oldDurum = ui->durum_->currentText();
                oldKasaTipi = ui->kasaTipi_->currentText();
                oldDeckLink = ui->decklink_->currentText();
                oldRam = ui->ram_->text();
                oldTestDurumu = ui->test_durum_->currentText();
                oldIslemci = ui->islemci_->text();
                oldHDD = ui->hdd_->text();
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

void InformationServerDialog::changes() {
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
    connect(ui->durum_, &QComboBox::currentTextChanged, this, &InformationServerDialog::commandChangedDurum);

    QStringList testDurum = {"Test Edilecek","Lab Testi Yapıldı","Saha Testi Yapıldı"};
    ui->test_durum_->addItems(testDurum);
    connect(ui->test_durum_, &QComboBox::currentTextChanged, this, &InformationServerDialog::commandChangedTestDurum);

    QStringList commandsKasaTipi = {"1U","1U","Tower"};
    ui->kasaTipi_->addItems(commandsKasaTipi);
    connect(ui->kasaTipi_, &QComboBox::currentTextChanged, this, &InformationServerDialog::commandChangedKasaTipi);

    QStringList commandsDecklink = {"Quad","Studio 2","Studio 4K"};
    ui->decklink_->addItems(commandsDecklink);
    connect(ui->decklink_,&QComboBox::currentTextChanged, this, &InformationServerDialog::commandChangedDecklink);
}

void InformationServerDialog::addMusteri() {
    commandsMusteri.append("LAB");
    if(database.isOpen()) {
        QSqlQuery* qry = new QSqlQuery(database);
        qry ->prepare("select * from müsteri");
        if(qry -> exec()) {
            while(qry->next()) {commandsMusteri.append(qry->value(1).toString());}
        }
    }
    ui->musteriAdi_1->addItems(commandsMusteri);
    connect(ui->musteriAdi_1, &QComboBox::currentTextChanged, this, &InformationServerDialog::commandChangedMusteriAdi);
}
void InformationServerDialog::commandChangedDurum(const QString &command_text)
{
    durum = command_text;
}

void InformationServerDialog::commandChangedTestDurum(const QString &command_text)
{
    testDurumu = command_text;
}

void InformationServerDialog::commandChangedMusteriAdi(const QString &command_text)
{
    musteriAdi = command_text;
}

void InformationServerDialog::commandChangedKasaTipi(const QString &command_text)
{
    kasaTipi = command_text;
}

void InformationServerDialog::commandChangedDecklink(const QString &command_text)
{
    decklink = command_text;
}

void InformationServerDialog::on_pushButton_clicked()
{
    if(database.isOpen()) {

        QSqlQuery qry;
        QString model = ui->model_->text();
        QString anakartNo = ui->anakart_->text();
        QString uidNo = ui->UIDNo_1->text();
        QString testDrm = ui->test_durum_->currentText();
        QString musteriAdi = ui->musteriAdi_1->currentText();
        QString durum = ui->durum_->currentText();
        QString uretimTarih;
        QString uretimTarihDay = ui->date_day->text();
        QString uretimTarihMonth = ui->date_month->text();
        QString uretimTarihYear = ui->date_year->text();
        uretimTarih = uretimTarihDay + "." + uretimTarihMonth + "." + uretimTarihYear;
        QString kasaTipi = ui->kasaTipi_->currentText();
        QString decklink = ui->decklink_->currentText();
        QString ram = ui->ram_->text();
        QString islemci = ui->islemci_->text();
        QString hdd = ui->hdd_->text();

        qry.prepare("UPDATE cihazkimlikserver SET `Model` = '" + model + "' WHERE `Cihaz Seri No` = '" + seriNo + "';");
        qry.exec();
        qry.clear();
        qry.prepare("UPDATE cihazkimlikserver SET `Anakart No` = '" + anakartNo + "' WHERE `Cihaz Seri No` = '" + seriNo + "';");
        qry.exec();
        qry.clear();
        qry.prepare("UPDATE cihazkimlikserver SET `UID No` = '" + uidNo + "' WHERE `Cihaz Seri No` = '" + seriNo + "';");
        qry.exec();
        qry.clear();
        qry.prepare("UPDATE cihazkimlikserver SET `Test Durumu` = '" + testDrm + "' WHERE `Cihaz Seri No` = '" + seriNo + "';");
        qry.exec();
        qry.clear();
        qry.prepare("UPDATE cihazkimlikserver SET `Müşteri` = '" + musteriAdi + "' WHERE `Cihaz Seri No` = '" + seriNo + "';");
        qry.exec();
        qry.clear();
        qry.prepare("UPDATE cihazkimlikserver SET `Durum` = '" + durum + "' WHERE `Cihaz Seri No` = '" + seriNo + "';");
        qry.exec();
        qry.clear();
        qry.prepare("UPDATE cihazkimlikserver SET `Üretim Tarihi` = '" + uretimTarih + "' WHERE `Cihaz Seri No` = '" + seriNo + "';");
        qry.exec();
        qry.clear();
        qry.prepare("UPDATE cihazkimlikserver SET `Kasa Tipi` = '" + kasaTipi + "' WHERE `Cihaz Seri No` = '" + seriNo + "';");
        qry.exec();
        qry.clear();
        qry.prepare("UPDATE cihazkimlikserver SET `Decklink` = '" + decklink + "' WHERE `Cihaz Seri No` = '" + seriNo + "';");
        qry.exec();
        qry.clear();
        qry.prepare("UPDATE cihazkimlikserver SET `Ram` = '" + ram + "' WHERE `Cihaz Seri No` = '" + seriNo + "';");
        qry.exec();
        qry.clear();
        qry.prepare("UPDATE cihazkimlikserver SET `İşlemci` = '" + islemci + "' WHERE `Cihaz Seri No` = '" + seriNo + "';");
        qry.exec();
        qry.clear();
        qry.prepare("UPDATE cihazkimlikserver SET `HDD` = '" + hdd + "' WHERE `Cihaz Seri No` = '" + seriNo + "';");
        qry.exec();
        qry.clear();
        qry.prepare("UPDATE cihazkimlikserver SET `Notlar` = '" + notlar + "' WHERE `Cihaz Seri No` = '" + seriNo + "';");
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
            qry.exec();
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
            qry.exec();
            qry.clear();
        }if(QString::compare(oldKasaTipi, ui->kasaTipi_->currentText(), Qt::CaseInsensitive)) {
            qry.prepare("INSERT INTO loglar(`Cihaz Seri No`,`Tarih`,`Eski Deger`,`Yeni Deger`,`Değişen`)"
                        "VALUES(:seriNo,:tarih,:eskiDeger,:yeniDeger,:degisen)");
            tarihLog = QString::number(QDate::currentDate().day()) + "." + QString::number(QDate::currentDate().month()) + "." + QString::number(QDate::currentDate().year()) + "  "
                    + QString::number(QTime::currentTime().hour()) + ":" + QString::number(QTime::currentTime().minute());
            qry.bindValue(":seriNo",ui->cihaz_seri_no->text());
            qry.bindValue(":tarih",tarihLog);
            qry.bindValue(":eskiDeger",oldKasaTipi);
            qry.bindValue(":yeniDeger",ui->kasaTipi_->currentText());
            qry.bindValue(":degisen","Kasa Tipi Değişti");
            qry.exec();
            qry.clear();
        }if(QString::compare(oldDeckLink, ui->decklink_->currentText(), Qt::CaseInsensitive)) {
            qry.prepare("INSERT INTO loglar(`Cihaz Seri No`,`Tarih`,`Eski Deger`,`Yeni Deger`,`Değişen`)"
                        "VALUES(:seriNo,:tarih,:eskiDeger,:yeniDeger,:degisen)");
            tarihLog = QString::number(QDate::currentDate().day()) + "." + QString::number(QDate::currentDate().month()) + "." + QString::number(QDate::currentDate().year()) + "  "
                    + QString::number(QTime::currentTime().hour()) + ":" + QString::number(QTime::currentTime().minute());
            qry.bindValue(":seriNo",ui->cihaz_seri_no->text());
            qry.bindValue(":tarih",tarihLog);
            qry.bindValue(":eskiDeger",oldDeckLink);
            qry.bindValue(":yeniDeger",ui->decklink_->currentText());
            qry.bindValue(":degisen","Decklink Değişti");
            qry.exec();
            qry.clear();
        }if(QString::compare(oldRam, ui->ram_->text(), Qt::CaseInsensitive)) {
            qry.prepare("INSERT INTO loglar(`Cihaz Seri No`,`Tarih`,`Eski Deger`,`Yeni Deger`,`Değişen`)"
                        "VALUES(:seriNo,:tarih,:eskiDeger,:yeniDeger,:degisen)");
            tarihLog = QString::number(QDate::currentDate().day()) + "." + QString::number(QDate::currentDate().month()) + "." + QString::number(QDate::currentDate().year()) + "  "
                    + QString::number(QTime::currentTime().hour()) + ":" + QString::number(QTime::currentTime().minute());
            qry.bindValue(":seriNo",ui->cihaz_seri_no->text());
            qry.bindValue(":tarih",tarihLog);
            qry.bindValue(":eskiDeger",oldRam);
            qry.bindValue(":yeniDeger",ui->ram_->text());
            qry.bindValue(":degisen","Ram Değişti");
            qry.exec();
            qry.clear();
        }if(QString::compare(oldIslemci, ui->islemci_->text(), Qt::CaseInsensitive)) {
            qry.prepare("INSERT INTO loglar(`Cihaz Seri No`,`Tarih`,`Eski Deger`,`Yeni Deger`,`Değişen`)"
                        "VALUES(:seriNo,:tarih,:eskiDeger,:yeniDeger,:degisen)");
            tarihLog = QString::number(QDate::currentDate().day()) + "." + QString::number(QDate::currentDate().month()) + "." + QString::number(QDate::currentDate().year()) + "  "
                    + QString::number(QTime::currentTime().hour()) + ":" + QString::number(QTime::currentTime().minute());
            qry.bindValue(":seriNo",ui->cihaz_seri_no->text());
            qry.bindValue(":tarih",tarihLog);
            qry.bindValue(":eskiDeger",oldIslemci);
            qry.bindValue(":yeniDeger",ui->islemci_->text());
            qry.bindValue(":degisen","İşlemci Değişti");
            qry.exec();
            qry.clear();
        }if(QString::compare(oldHDD, ui->hdd_->text(), Qt::CaseInsensitive)) {
            qry.prepare("INSERT INTO loglar(`Cihaz Seri No`,`Tarih`,`Eski Deger`,`Yeni Deger`,`Değişen`)"
                        "VALUES(:seriNo,:tarih,:eskiDeger,:yeniDeger,:degisen)");
            tarihLog = QString::number(QDate::currentDate().day()) + "." + QString::number(QDate::currentDate().month()) + "." + QString::number(QDate::currentDate().year()) + "  "
                    + QString::number(QTime::currentTime().hour()) + ":" + QString::number(QTime::currentTime().minute());
            qry.bindValue(":seriNo",ui->cihaz_seri_no->text());
            qry.bindValue(":tarih",tarihLog);
            qry.bindValue(":eskiDeger",oldHDD);
            qry.bindValue(":yeniDeger",ui->hdd_->text());
            qry.bindValue(":degisen","HDD Değişti");
            qry.exec();
            qry.clear();
        }if(QString::compare(oldTestDurumu, ui->test_durum_->currentText(), Qt::CaseInsensitive)) {
            qry.prepare("INSERT INTO loglar(`Cihaz Seri No`,`Tarih`,`Eski Deger`,`Yeni Deger`,`Değişen`)"
                        "VALUES(:seriNo,:tarih,:eskiDeger,:yeniDeger,:degisen)");
            tarihLog = QString::number(QDate::currentDate().day()) + "." + QString::number(QDate::currentDate().month()) + "." + QString::number(QDate::currentDate().year()) + "  "
                    + QString::number(QTime::currentTime().hour()) + ":" + QString::number(QTime::currentTime().minute());
            qry.bindValue(":seriNo",ui->cihaz_seri_no->text());
            qry.bindValue(":tarih",tarihLog);
            qry.bindValue(":eskiDeger",oldTestDurumu);
            qry.bindValue(":yeniDeger",ui->test_durum_->currentText());
            qry.bindValue(":degisen","Test Durum Değişti");
            qry.exec();
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
            qry.exec();
            qry.clear();
        }

    }else {
        QMessageBox::information(this, "Not Connected", "Database Is Not Connected");
        cout << "Database not connected!" << endl;
    }

    this->close();
}


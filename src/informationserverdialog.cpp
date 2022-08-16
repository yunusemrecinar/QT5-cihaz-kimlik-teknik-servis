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

void InformationServerDialog::setLog(QString content) {

    QSqlQuery qry;
    QString date = QDateTime::currentDateTime().toString("dd.MM.yyyy hh:mm:ss");
    qry.prepare("INSERT INTO processlogs(`tarih`,`username`,`process`) VALUES (:tarih,:username,:process)");
    qry.bindValue(":tarih",date);
    qry.bindValue(":username",username);
    qry.bindValue(":process",content);
    qry.exec();
}

void InformationServerDialog::initialize(QString s, QSqlDatabase d, QString user) {
    seriNo = s;
    database = d;
    username = user;


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
                ui->musteriAdi_1->setText(qry->value(10).toString());
                ui->durum_->setCurrentText(qry->value(11).toString());
                if(qry->value(12).toString().contains(".")) {
                    if(qry->value(12).toString().length() != 2) {
                        QList<QString> date = qry->value(12).toString().split(".");
                        ui->date_day->setValue(date.at(0).toInt());
                        ui->date_month->setValue(date.at(1).toInt());
                        ui->date_year->setValue(date.at(2).toInt());
                    }else {
                        ui->date_year->clear();
                        ui->date_day->clear();
                        ui->date_month->clear();
                    }
                }
                if(qry->value(13).toString().contains(".")) {
                    if(qry->value(13).toString().length() != 2) {
                        QList<QString> faturaKesim = qry->value(13).toString().split(".");
                        ui->fatura_date_day_->setValue(faturaKesim.at(0).toInt());
                        ui->fatura_date_month_->setValue(faturaKesim.at(1).toInt());
                        ui->fatura_date_year_->setValue(faturaKesim.at(2).toInt());
                    }else {
                        ui->fatura_date_year_->clear();
                        ui->fatura_date_day_->clear();
                        ui->fatura_date_month_->clear();
                    }
                }
                if(qry->value(14).toString().contains(".")) {
                    if(qry->value(14).toString().length() != 2) {
                        QList<QString> garantiStart = qry->value(14).toString().split(".");
                        ui->garanti_start_day_->setValue(garantiStart.at(0).toInt());
                        ui->garanti_start_month_->setValue(garantiStart.at(1).toInt());
                        ui->garanti_start_year_->setValue(garantiStart.at(2).toInt());
                    }else {
                        ui->garanti_start_year_->clear();
                        ui->garanti_start_day_->clear();
                        ui->garanti_start_month_->clear();
                    }
                }
                if(qry->value(15).toString().contains(".")) {
                    if(qry->value(15).toString().length() != 2) {
                        QList<QString> garantiBitis = qry->value(15).toString().split(".");
                        ui->garanti_bitis_day_->setValue(garantiBitis.at(0).toInt());
                        ui->garanti_bitis_month_->setValue(garantiBitis.at(1).toInt());
                        ui->garanti_bitis_year_->setValue(garantiBitis.at(2).toInt());
                    }else {
                        ui->garanti_bitis_year_->clear();
                        ui->garanti_bitis_day_->clear();
                        ui->garanti_bitis_month_->clear();
                    }
                }
                ui->hdd_->setText(qry->value(16).toString());
                ui->notlar_->setText(qry->value(17).toString());

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
            setLog("[ERROR] informationserverdialog.cpp : " + qry->lastError().text());
        }

    }else {
        QMessageBox::information(this, "Not Connected", "Database Is Not Connected1");
        setLog("[ERROR] informationserverdialog.cpp : " + database.lastError().text());
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
        QString musteriAdi = ui->musteriAdi_1->text();
        QString durum = ui->durum_->currentText();
        QString uretimTarih;
        QString uretimTarihDay = ui->date_day->text();
        QString uretimTarihMonth = ui->date_month->text();
        QString uretimTarihYear = ui->date_year->text();
        uretimTarih = uretimTarihDay + "." + uretimTarihMonth + "." + uretimTarihYear;
        QString faturaKesim = ui->fatura_date_day_->text() + "." + ui->fatura_date_month_->text() + "." + ui->fatura_date_year_->text();
        QString garantiBaslangic = ui->garanti_start_day_->text() + "." + ui->garanti_start_month_->text() + "." + ui->garanti_start_year_->text();
        QString garantiBitis = ui->garanti_bitis_day_->text() + "." + ui->garanti_bitis_month_->text() + "." + ui->garanti_bitis_year_->text();
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
        qry.prepare("UPDATE cihazkimlikserver SET `Fatura Kesim` = '" + faturaKesim + "' WHERE `Cihaz Seri No` = '" + seriNo + "';");
        qry.exec();
        qry.clear();
        qry.prepare("UPDATE cihazkimlikserver SET `Garanti Baslangic` = '" + garantiBaslangic + "' WHERE `Cihaz Seri No` = '" + seriNo + "';");
        qry.exec();
        qry.clear();
        qry.prepare("UPDATE cihazkimlikserver SET `Garanti Bitis` = '" + garantiBitis + "' WHERE `Cihaz Seri No` = '" + seriNo + "';");
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
            if(qry.exec()) {
                setLog("[NOTE]" + ui->cihaz_seri_no->text() + " no'lu cihazın uid no'su değiştirildi.");
            }else {
                setLog("[ERROR] informationdialog.cpp : " + qry.lastError().text());
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
                setLog("[ERROR] informationdialog.cpp : " + qry.lastError().text());
            }
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
            if(qry.exec()) {
                setLog("[NOTE]" + ui->cihaz_seri_no->text() + " no'lu cihazın kasa tipi değiştirildi.");
            }else {
                setLog("[ERROR] informationdialog.cpp : " + qry.lastError().text());
            }
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
            if(qry.exec()) {
                setLog("[NOTE]" + ui->cihaz_seri_no->text() + " no'lu cihazın decklink i değiştirildi.");
            }else {
                setLog("[ERROR] informationdialog.cpp : " + qry.lastError().text());
            }
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
            if(qry.exec()) {
                setLog("[NOTE]" + ui->cihaz_seri_no->text() + " no'lu cihazın ram i değiştirildi.");
            }else {
                setLog("[ERROR] informationdialog.cpp : " + qry.lastError().text());
            }
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
            if(qry.exec()) {
                setLog("[NOTE]" + ui->cihaz_seri_no->text() + " no'lu cihazın islemcisi değiştirildi.");
            }else {
                setLog("[ERROR] informationdialog.cpp : " + qry.lastError().text());
            }
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
            if(qry.exec()) {
                setLog("[NOTE]" + ui->cihaz_seri_no->text() + " no'lu cihazın hdd si değiştirildi.");
            }else {
                setLog("[ERROR] informationdialog.cpp : " + qry.lastError().text());
            }
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
            if(qry.exec()) {
                setLog("[NOTE]" + ui->cihaz_seri_no->text() + " no'lu cihazın test durumu değiştirildi.");
            }else {
                setLog("[ERROR] informationdialog.cpp : " + qry.lastError().text());
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
                setLog("[ERROR] informationdialog.cpp : " + qry.lastError().text());
            }
            qry.clear();
        }

    }else {
        QMessageBox::information(this, "Not Connected", "Database Is Not Connected");
        setLog("[ERROR] informationserverdialog.cpp : " + database.lastError().text());
        cout << "Database not connected!" << endl;
    }

    this->close();
}


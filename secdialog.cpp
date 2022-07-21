#include "secdialog.h"
#include "ui_secdialog.h"
#include <QMessageBox>
#include <QSqlQuery>
#include "mainwindow.h"
#include "lineeditpopupform.h"
#include <QVBoxLayout>
#include <QMenu>

#include <iostream>
using namespace std;



SecDialog::SecDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SecDialog)
{

    ui->setupUi(this);
    //this->setFixedSize(this->width(),this->height());
    this->setWindowTitle(" ");
    //ui->verticalLayout_7->layout()->
    //ui->test_durum_->setContextMenuPolicy(Qt::CustomContextMenu);
    //m_lineedit_menu = new QMenu(this);
    //m_lineedit_popup_form = new LineEditPopUpForm(this);
    //m_lineedit_popup_form->set_lineedit(ui->test_durum_);
    //QVBoxLayout *lineedit_layout = new QVBoxLayout;
    //lineedit_layout->addWidget(m_lineedit_popup_form);
    //m_lineedit_menu->setLayout(lineedit_layout);
    //connect(ui->test_durum_, &QLineEdit::customContextMenuRequested, [&](const QPoint &p)
    //{
    //    m_lineedit_menu->popup(mapToGlobal(p));
    //    m_lineedit_menu->setGeometry(860,540,145,167);
    //});

}

SecDialog::~SecDialog()
{
    delete ui;
}

void SecDialog::on_pushButton_clicked()
{
    MainWindow w;
    database1 = QSqlDatabase::addDatabase("QMYSQL");
    database1.setHostName(w.hostName);
    database1.setUserName(w.userName);
    database1.setPassword(w.password);
    database1.setDatabaseName(w.dbName);

    if(database1.open()) {
        QString model;
        if(ui->model1_->isChecked()) {
            model = ui->model1_->text();
        }else if(ui->model2_->isChecked()) {
            model = ui->model2_->text();
        }else if(ui->model3_->isChecked()) {
            model = ui->model3_->text();
        }else if(ui->model4_->isChecked()) {
            model = ui->model4_->text();
        }else if(ui->model5_->isChecked()) {
            model = ui->model5_->text();
        }else if(ui->model6_->isChecked()) {
            model = ui->model6_->text();
        }else if(ui->model7_->isChecked()) {
            model = ui->model7_->text();
        }
        QString cihazSeriNo = ui->cihaz_seri_no->text();
        QString anakartNo = ui->anakart_->text();
        QString modemKarti = ui-> modem_karti_->text();
        QString lcdKarti = ui->lcd_karti_->text();
        QString sarjKarti = ui->sarj_karti_->text();
        QString durum = ui->durum_->text();
        QString uretimTarihi = ui->date_day->text() + "." + ui->date_month->text() + "." + ui->date_year->text();

        QString modemSeri1 = ui->modemSeri1_->text();
        QString modemSeri2 = ui->modemSeri2_->text();
        QString modemSeri3 = ui->modemSeri3_->text();
        QString modemSeri4 = ui->modemSeri4_->text();
        QString modemSeri5 = ui->modemSeri5_->text();
        QString modemSeri6 = ui->modemSeri6_->text();
        QString testDurumu = ui->test_durum_->text();
        QString degisenParcalar = ui->degisenParcalar_->text();
        QString notlar = ui->notlar_->text();

        QSqlQuery qry;

        qry.prepare("INSERT INTO cihazkimlik(`Model`,`Cihaz Seri No`,`Anakart No`,"
                    "`Modem Kartı`,`Lcd Kartı`,`Şarj Kartı`,`Durumu`,`Modem Seri Num 1`,"
                    "`Modem Seri Num 2`,`Modem Seri Num 3`,`Modem Seri Num 4`,`Modem Seri Num 5`,"
                    "`Modem Seri Num 6`,`Uretim Tarihi`,`Test Durumu`,`Degisen Parcalar`,`Notlar`) "
                    "VALUES(:model,:cihazSeriNo,:anakartNo,"
                    ":modemKarti,:lcdKarti,:sarjKarti,:durumu,:modemSeriNum1,"
                    ":modemSeriNum2,:modemSeriNum3,:modemSeriNum4,:modemSeriNum5,"
                    ":modemSeriNum6,:uretimTarihi,:testDurumu,:degisenParcalar,:notlar)");
        qry.bindValue(":model",model);
        qry.bindValue(":cihazSeriNo",cihazSeriNo);
        qry.bindValue(":anakartNo",anakartNo);
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
        qry.bindValue(":degisenParcalar",degisenParcalar);
        qry.bindValue(":notlar",notlar);

        if(qry.exec()) {
            QMessageBox::information(this,"Inserted","Data Inserted Succesfully");
        }else {
            QMessageBox::information(this,"Not Inserted",qry.lastError().text());
        }

    }else {
        QMessageBox::information(this, "Not Connected", "Database Is Not Connected");
        cout << "Database not connected!" << endl;
    }


    database1.close();
    this->close();
}


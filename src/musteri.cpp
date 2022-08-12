#include "musteri.h"
#include "ui_musteri.h"
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QMessageBox>
#include <QSqlError>
#include "informationmusteridialog.h"
#include <QTime>

#include <iostream>
using namespace std;

Musteri::Musteri(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Musteri)
{
    ui->setupUi(this);
    ui->cihazSeriNo->setMaxLength(9);
    ui->cihazSeriNo->setValidator(new QRegularExpressionValidator(QRegularExpression("\\d*")));
    ui->lineEditSort->setPlaceholderText("Filtrele");
    ui->lineEditSort->setReadOnly(1);
}
void Musteri::setLog(QString content) {

    QSqlQuery qry;
    QString date = QDateTime::currentDateTime().toString("dd.MM.yyyy hh:mm:ss");
    qry.prepare("INSERT INTO processlogs(`tarih`,`username`,`process`) VALUES (:tarih,:username,:process)");
    qry.bindValue(":tarih",date);
    qry.bindValue(":username",username);
    qry.bindValue(":process",content);
    qry.exec();
}
void Musteri::initialize(QSqlDatabase d, QString user) {
    database = d;
    username = user;

    QSqlQueryModel * modal = new QSqlQueryModel();
    if(database.isOpen()) {

        QSqlQuery* qry = new QSqlQuery(database);

        qry ->prepare("select * from `müsteri`");
        if(qry -> exec()){
            setLog("[NOTE] musteri.cpp : musteri tablosu yükleniyor");
        }else {
            setLog("[ERROR] musteri.cpp : " + qry->lastError().text());
        }
        modal->setQuery(*qry);
        ui->tableView->setModel(modal);
        ui->tableView->hideColumn(0);
        ui->tableView->resizeRowsToContents();
        ui->tableView->resizeColumnsToContents();
        ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        ui->tableView->horizontalHeader()->setStyleSheet("QHeaderView { font-size: 18pt; color:#002B5B; font-weight: bold; }");
    }else {
        QMessageBox::information(this, "Not Connected", "Database Is Not Connected");
        setLog("[ERROR] musteri.cpp : " + database.lastError().text());
        cout << "Database not connected!" << endl;
    }
}

Musteri::~Musteri()
{
    delete ui;
}

void Musteri::on_lineEditSort_selectionChanged()
{
    ui->lineEditSort->setText("");
    ui->lineEditSort->setReadOnly(0);
}
void Musteri::on_lineEditSort_textChanged(const QString &arg1)
{
    QSqlQueryModel *model = new QSqlQueryModel();

    if(database.isOpen()) {
        QSqlQuery* qry = new QSqlQuery(database);

        qry ->prepare("select * from müsteri where `Cihaz Seri No` LIKE '" + arg1 + "%' OR LOWER(`İsim`) LIKE '" + arg1.toLower() + "%';");
        qry -> exec();
        model->setQuery(*qry);
        ui->tableView->setModel(model);
        ui->tableView->resizeColumnsToContents();
        ui->tableView->resizeRowsToContents();
        ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    }else {
        QMessageBox::information(this, "Not Connected", database.lastError().text());
        setLog("[ERROR] musteri.cpp : " + database.lastError().text());
        cout << "Database not connected!" << endl;
    }
}
void Musteri::on_pushButton_clicked()
{
    if(database.isOpen()) {

        QString isim = ui->textEditIsim->toPlainText();
        QString adres = ui->textEditAdres->toPlainText();
        QString cihazSeriNo = ui->cihazSeriNo->text();
        QSqlQuery qry;

        int count;
        QString temp = "";
        if(ui->cihazSeriNo->text().length() == 9) {
                    checkSeriNo = true;
                }
        if(checkSeriNo) {
            qry.prepare("SELECT COUNT(*) FROM `müsteri` WHERE `İsim` = '" + isim + "';");
            if(qry.exec()) {
                setLog("[NOTE] musteri.cpp musteri eklenecek cihaz seri no kontrol!!");
            }else {
                setLog("[ERROR] musteri.cpp : " + qry.lastError().text());
            }
            while(qry.next()) {
                count = qry.value(0).toInt();
            }
            qry.clear();
            if(count == 1) {
                qry.prepare("SELECT `Cihaz Seri No` FROM `müsteri` WHERE İsim = '" + isim + "';");
                if(qry.exec()) {
                    setLog("[NOTE] musteri.cpp musteri o isimdeki cihaz seri numaraları alındı!!");
                }else {
                    setLog("[ERROR] musteri.cpp : " + qry.lastError().text());
                }
                while(qry.next()) {
                    temp = qry.value(0).toString();
                }
                temp += "\n"+cihazSeriNo;
                qry.clear();
                qry.prepare("UPDATE `müsteri` SET `Cihaz Seri No` = '"+temp+"' WHERE İsim = '" + isim.trimmed() + "';");
                qry.exec();
            }else {
                qry.prepare("SELECT `Cihaz Seri No` FROM `müsteri`");
                qry.exec();
                QList<QString> list;
                while(qry.next()) { list.append(qry.value(0).toString()); }

                if(list.contains(cihazSeriNo)){
                    QMessageBox::information(this,"HATA","Bir Cihaz Seri No birden çok müşteriye ait olamaz!!");
                }else {
                    qry.clear();
                    qry.prepare("INSERT INTO müsteri(`İsim`,`Adres`,`Cihaz Seri No`) "
                                "VALUES(:isim,:adres,:cihazSeriNo)");
                    qry.bindValue(":isim",isim.trimmed());
                    qry.bindValue(":adres",adres);
                    qry.bindValue(":cihazSeriNo",cihazSeriNo);

                    if(qry.exec()) {
                        setLog("[NOTE] musteri.cpp musteri eklendi!!");
                    }else {
                        setLog("[ERROR] musteri.cpp : " + qry.lastError().text());
                    }
                }
            }
        }else {
            QMessageBox::information(this,"Error", "Cihaz Seri Numarasını Kontrol Edin!!");
        }
        ui->textEditIsim->clear();
        ui->textEditAdres->clear();
        ui->cihazSeriNo->clear();
        qry.clear();

        refresh();

    }else {
        QMessageBox::information(this, "Not Connected", "Database Is Not Connected");
        setLog("[ERROR] musteri.cpp : " + database.lastError().text());
        cout << "Database not connected!" << endl;
    }

}
void Musteri::refresh() {
    QSqlQueryModel *model = new QSqlQueryModel();

    if(database.isOpen()) {
        QSqlQuery* qry = new QSqlQuery(database);

        //model = new QSqlQueryModel();

        //setValue("select * from cihazkimlik");
        //ui->tableView->setModel(model);
        qry ->prepare("select * from müsteri");
        qry -> exec();
        model->setQuery(*qry);
        ui->tableView->setModel(model);
        ui->tableView->resizeColumnsToContents();
        ui->tableView->resizeRowsToContents();
        ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    }else {
        QMessageBox::information(this, "Not Connected", database.lastError().text());
        setLog("[ERROR] musteri.cpp : " + database.lastError().text());
        cout << "Database not connected!" << endl;
    }
}

void Musteri::on_tableView_clicked(const QModelIndex &index)
{
    int row = ui->tableView->currentIndex().row();
    rowId = ui->tableView->model()->data(ui->tableView->model()->index(row,0)).toString();
}


void Musteri::on_pushButton_sil_clicked()
{
    QSqlQuery qry;

    qry.prepare("DELETE FROM müsteri WHERE `Id` = " + rowId);
    qry.exec();

    qry.clear();

    QSqlQueryModel *model = new QSqlQueryModel();

    if(database.isOpen()) {
        QSqlQuery* qry = new QSqlQuery(database);

        //model = new QSqlQueryModel();

        //setValue("select * from cihazkimlik");
        //ui->tableView->setModel(model);
        qry ->prepare("select * from müsteri");
        if(qry->exec()) {
            setLog("[NOTE] musteri.cpp musteri silindi!!");
        }else {
            setLog("[ERROR] musteri.cpp : " + qry->lastError().text());
        }
        model->setQuery(*qry);
        ui->tableView->setModel(model);
        ui->tableView->resizeColumnsToContents();
        ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    }else {
        QMessageBox::information(this, "Not Connected", database.lastError().text());
        setLog("[ERROR] musteri.cpp : " + database.lastError().text());
        cout << "Database not connected!" << endl;
    }
}


void Musteri::on_tableView_doubleClicked(const QModelIndex &index)
{
    int row = ui->tableView->currentIndex().row();
    QString rowValue = ui->tableView->model()->data(ui->tableView->model()->index(row,3)).toString();


    seriNo = rowValue;

    InformationMusteriDialog *musteriDialog = new InformationMusteriDialog();
    musteriDialog->initialize(database, seriNo, username);
    musteriDialog->exec();
    refresh();
}


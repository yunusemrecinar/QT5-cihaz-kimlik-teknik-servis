#include "informationmusteridialog.h"
#include "ui_informationmusteridialog.h"
#include <QSqlDatabase>
#include <iostream>
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <QStringListModel>
#include <QDropEvent>
#include <QMouseEvent>
#include <QDragEnterEvent>
#include <QDragMoveEvent>
#include <QSqlQueryModel>
#include <QTime>

using namespace std;

InformationMusteriDialog::InformationMusteriDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::InformationMusteriDialog)
{
    ui->setupUi(this);
    changes();

}

InformationMusteriDialog::~InformationMusteriDialog()
{
    delete ui;
}
void InformationMusteriDialog::changes() {
    ui->listViewMusteri->setDragEnabled(true);
    ui->listViewMusteri->setAcceptDrops(true);
    ui->listViewMusteri->setDropIndicatorShown(true);
    ui->listViewMusteri->setDefaultDropAction(Qt::MoveAction);

    ui->listViewToplam->setDragEnabled(true);
    ui->listViewToplam->setAcceptDrops(true);
    ui->listViewToplam->setDropIndicatorShown(true);
    ui->listViewToplam->setDefaultDropAction(Qt::MoveAction);

    ui->listViewToplam->setModel(new QStringListModel());
    ui->listViewMusteri->setModel(new QStringListModel());

    ui->listViewMusteri->setStyleSheet(
                "QListView { font-size: 20pt; font-weight: bold; }"
                     "QListView::item { background-color: #E74C3C; padding: 10%;"
                     "border: 1px solid #C0392B; }"
                     "QListView::item::hover { background-color: #C0392B }");

    ui->listViewToplam->setStyleSheet(
                "QListView { font-size: 20pt; font-weight: bold; }"
                     "QListView::item { background-color: #2ECC71; padding: 10%;"
                     "border: 1px solid #27AE60; }"
                     "QListView::item::hover { background-color: #27AE60 }");

    ui->listViewToplam->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->listViewMusteri->setEditTriggers(QAbstractItemView::NoEditTriggers);

    ui->filter->setPlaceholderText("Filtrele");
    ui->filter->setReadOnly(1);

}
void InformationMusteriDialog::listViewMusteriChanged() {
    updateChangesMusteri();
}
void InformationMusteriDialog::listViewToplamChanged() {
    updateChangesToplam();
}
void InformationMusteriDialog::fillListViews() {

    if(database.isOpen()) {
        QSqlQuery* qry = new QSqlQuery(database);

        qry->prepare("SELECT `Cihaz Seri No` From `cihazisim` WHERE `İsim` = 'LAB'");
        if(qry -> exec()) {
            while(qry->next()) {
                ui->listViewToplam->model()->insertRow(ui->listViewToplam->model()->rowCount());
                QModelIndex oIndex = ui->listViewToplam->model()->index(
                            ui->listViewToplam->model()->rowCount() - 1, 0);

                ui->listViewToplam->model()->setData(oIndex, qry->value(0).toString());
            }
        }else {
            setLog("[ERROR] informationmusteridialog.cpp : " + qry->lastError().text());
        }
        qry->clear();
        qry->prepare("SELECT `Cihaz Seri No` FROM `cihazisim` WHERE `İsim` = '" + ui->textEditIsim->toPlainText() + "';");
        if(qry -> exec()) {
            while(qry->next()) {
                ui->listViewMusteri->model()->insertRow(ui->listViewMusteri->model()->rowCount());
                QModelIndex oIndex = ui->listViewMusteri->model()->index(
                            ui->listViewMusteri->model()->rowCount() - 1, 0);

                ui->listViewMusteri->model()->setData(oIndex, qry->value(0).toString());
            }
        }else {
            setLog("[ERROR] informationmusteridialog.cpp : " + qry->lastError().text());
        }

        connect(ui->listViewMusteri->model(),&QAbstractItemModel::dataChanged,this, &InformationMusteriDialog::listViewMusteriChanged);
        connect(ui->listViewToplam->model(),&QAbstractItemModel::dataChanged,this,&InformationMusteriDialog::listViewToplamChanged);
    }else {
        setLog("[ERROR] informationmusteridialog.cpp : " + database.lastError().text());
    }
}
void InformationMusteriDialog::initialize(QSqlDatabase d, QString s, QString user)
{
    database = d;
    seriNo = s;
    username = user;

    QString adresTemp;
    if(database.isOpen()) {

        QSqlQuery* qry = new QSqlQuery(database);

        qry ->prepare("select * from `müsteri` where `Id` = '" + seriNo + "'");

        if(qry->exec()) {
            while(qry->next()) {
                ui->textEditIsim->setText(qry->value(1).toString());
                ui->textEditAdres->setText(qry->value(2).toString());               
            }
        }else {
            QMessageBox::critical(this, tr("error::"), qry->lastError().text());
            setLog("[ERROR] informationmusteridialog.cpp : " + qry->lastError().text());
        }

        fillListViews();
    }else {
        QMessageBox::information(this, "Not Connected", "Database Is Not Connected1");
        setLog("[ERROR] informationmusteridialog.cpp : " + database.lastError().text());
        cout << "Database not connected!" << endl;
    }

}
void InformationMusteriDialog::updateChangesToplam() {
    if(database.isOpen()) {

        QModelIndex oIndex;
        QString value;
        QSqlQuery* qry = new QSqlQuery(database);
        int rowCount = ui->listViewToplam->model()->rowCount();

        for(int i = 0; i < rowCount; i++) {
            oIndex = ui->listViewToplam->model()->index(i, 0);
            value = ui->listViewToplam->model()->data(oIndex).toString();
            qry->prepare("UPDATE `cihazisim` SET `İsim` = 'LAB' WHERE `Cihaz Seri No` = '" + value + "';");
            if(qry->exec()){
                setLog("[NOTE] informationmusteridialog.cpp : " + value + " nolu cihazın müşterisi  LAB olarak değiştirildi.");
            }else {
                setLog("[ERROR] informationmusteridialog.cpp : " + qry->lastError().text());
            }
            qry->clear();
        }
    }
}
void InformationMusteriDialog::updateChangesMusteri() {
    if(database.isOpen()) {

        QModelIndex oIndex;
        QString value;
        QSqlQuery* qry = new QSqlQuery(database);
        int rowCount = ui->listViewMusteri->model()->rowCount();

        for(int i = 0; i < rowCount; i++) {
            oIndex = ui->listViewMusteri->model()->index(i, 0);
            value = ui->listViewMusteri->model()->data(oIndex).toString();
            qry->prepare("UPDATE `cihazisim` SET `İsim` = '" + ui->textEditIsim->toPlainText() + "' WHERE `Cihaz Seri No` = '" + value + "';");
            if(qry->exec()){
                setLog("[NOTE] informationmusteridialog.cpp : " + value + " nolu cihazın müşterisi " + ui->textEditIsim->toPlainText() + " olarak değiştirildi.");
            }else {
                setLog("[ERROR] informationmusteridialog.cpp : " + qry->lastError().text());
            }
            qry->clear();
            qry->prepare("UPDATE cihazkimlikserver SET `Müşteri` = '" + ui->textEditIsim->toPlainText() + "' WHERE `Cihaz Seri No` = '" + value +"';");
            qry->exec();
            qry->clear();
            qry->prepare("UPDATE cihazkimlik SET `Müşteri Adı` = '" + ui->textEditIsim->toPlainText() + "' WHERE `Cihaz Seri No` = '" + value +"';");
            qry->exec();
            qry->clear();
            qry->prepare("UPDATE cihazkimlikmobiot SET `Müşteri` = '" + ui->textEditIsim->toPlainText() + "' WHERE `Cihaz Seri No` = '" + value +"';");
            qry->exec();
            qry->clear();
        }
    }
}
/*
void InformationMusteriDialog::on_pushButton_clicked()
{
    if(database.isOpen()) {

        QSqlQuery qry;

        QString isim = ui->textEditIsim->toPlainText();
        QString adres = ui->textEditAdres->toPlainText();

        qry.prepare("UPDATE `müsteri` SET `İsim` = '" + isim + "' WHERE `Cihaz Seri No` = '" + seriNo + "';");
        qry.exec();
        qry.clear();
        qry.prepare("UPDATE `müsteri` SET `Adres` = '" + adres + "' WHERE `Cihaz Seri No` = '" + seriNo + "';");
        if(qry.exec()){

        }else {
            QMessageBox::critical(this, tr("error::"), qry.lastError().text());
            setLog("[ERROR] informationmusteridialog.cpp : " + qry.lastError().text());
        }
        qry.clear();
    }else{
        QMessageBox::information(this, "Not Connected", "Database Is Not Connected");
        setLog("[ERROR] informationmusteridialog.cpp : " + database.lastError().text());
        cout << "Database not connected!" << endl;
    }
    this->close();
}
*/
void InformationMusteriDialog::setLog(QString content) {

    QSqlQuery qry;
    QString date = QDateTime::currentDateTime().toString("dd.MM.yyyy hh:mm:ss");
    qry.prepare("INSERT INTO processlogs(`tarih`,`username`,`process`) VALUES (:tarih,:username,:process)");
    qry.bindValue(":tarih",date);
    qry.bindValue(":username",username);
    qry.bindValue(":process",content);
    qry.exec();
}


void InformationMusteriDialog::on_filter_selectionChanged()
{
    ui->filter->setText("");
    ui->filter->setReadOnly(0);
}


void InformationMusteriDialog::on_filter_textChanged(const QString &arg1)
{
    QSqlQueryModel *model = new QSqlQueryModel();

    if(database.isOpen()) {
        QSqlQuery* qry = new QSqlQuery(database);
        ui->listViewToplam->setModel(new QStringListModel());
        qry ->prepare("select `Cihaz Seri No` from cihazisim where `Cihaz Seri No` LIKE '" + arg1 + "%' OR LOWER(`İsim`) LIKE '" + arg1.toLower() + "%';");
        if(qry -> exec()) {
            while(qry->next()) {
                ui->listViewToplam->model()->insertRow(ui->listViewToplam->model()->rowCount());
                QModelIndex oIndex = ui->listViewToplam->model()->index(
                            ui->listViewToplam->model()->rowCount() - 1, 0);

                ui->listViewToplam->model()->setData(oIndex, qry->value(0).toString());
            }
        }else {
            setLog("[ERROR] informationmusteridialog.cpp : " + qry->lastError().text());
        }
    }else {
        QMessageBox::information(this, "Not Connected", database.lastError().text());
        setLog("[ERROR] informationmusteridialog.cpp : " + database.lastError().text());
        cout << "Database not connected!" << endl;
    }


}

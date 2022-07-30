#include "toolbardialog.h"
#include "ui_toolbardialog.h"
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QMessageBox>

#include <iostream>
using namespace std;

ToolBarDialog::ToolBarDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ToolBarDialog)
{
    ui->setupUi(this);
}

ToolBarDialog::~ToolBarDialog()
{
    delete ui;
}

void ToolBarDialog::initialize(QSqlDatabase d, QString type, QString databaseName)
{
    ui->label->setText(type);
    database = d;
    databaseName_ = databaseName;
    refresh();
}
void ToolBarDialog::refresh() {
    QSqlQueryModel * modal = new QSqlQueryModel();
    if(database.isOpen()) {

        QSqlQuery* qry = new QSqlQuery(database);

        qry ->prepare("select * from `" + databaseName_ +"`");
        qry -> exec();
        modal->setQuery(*qry);
        ui->tableView->setModel(modal);
        ui->tableView->resizeColumnsToContents();
        ui->tableView->resizeRowsToContents();
        ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    }else {
        QMessageBox::information(this, "Not Connected", "Database Is Not Connected");
        cout << "Database not connected!" << endl;
    }
}

void ToolBarDialog::on_pushButtonEkle_clicked()
{
    QString name = ui->lineEdit->text();

    if(database.isOpen()) {

        QSqlQuery qry;

                qry.prepare("INSERT INTO `" + databaseName_ +"` VALUES(:isim)");
                qry.bindValue(":isim",ui->lineEdit->text());
                if(name.length() != 0)
                    qry.exec();
        ui->lineEdit->clear();
        refresh();
    }else {
        QMessageBox::information(this, "Not Connected", "Database Is Not Connected");
        cout << "Database not connected!" << endl;
    }
}


void ToolBarDialog::on_pushButtonSil_clicked()
{
    if(database.isOpen()) {

        QSqlQuery qry;

                qry.prepare("DELETE FROM `" + databaseName_ +"` WHERE name = '" + rowLocation + "';");
                qry.exec();

        refresh();
    }else {
        QMessageBox::information(this, "Not Connected", "Database Is Not Connected");
        cout << "Database not connected!" << endl;
    }
}


void ToolBarDialog::on_tableView_clicked(const QModelIndex &index)
{
    int row = ui->tableView->currentIndex().row();
    rowLocation = ui->tableView->model()->data(ui->tableView->model()->index(row,0)).toString();
}


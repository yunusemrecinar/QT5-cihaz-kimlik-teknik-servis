#include "servisgetdialog.h"
#include "ui_servisgetdialog.h"

ServisGetDialog::ServisGetDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ServisGetDialog)
{
    ui->setupUi(this);
}

ServisGetDialog::~ServisGetDialog()
{
    delete ui;
}

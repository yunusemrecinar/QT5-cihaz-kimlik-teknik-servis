#include "servisdialog.h"
#include "ui_servisdialog.h"

ServisDialog::ServisDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ServisDialog)
{
    ui->setupUi(this);
}

ServisDialog::~ServisDialog()
{
    delete ui;
}

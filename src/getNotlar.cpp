#include "getNotlar.h"
#include "ui_notlar.h"

notlar::notlar(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::notlar)
{
    ui->setupUi(this);
}

notlar::~notlar()
{
    delete ui;
}

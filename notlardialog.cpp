#include "notlardialog.h"
#include "ui_notlardialog.h"

notlarDialog::notlarDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::notlarDialog)
{
    ui->setupUi(this);
}

notlarDialog::~notlarDialog()
{
    delete ui;
}

void notlarDialog::initialize(QString s) {
    ui->label->setText(s);
}

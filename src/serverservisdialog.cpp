#include "serverservisdialog.h"
#include "ui_serverservisdialog.h"

ServerServisDialog::ServerServisDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ServerServisDialog)
{
    ui->setupUi(this);
}

ServerServisDialog::~ServerServisDialog()
{
    delete ui;
}

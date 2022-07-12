#include "lineeditpopupform.h"
#include "ui_lineeditpopupform.h"
#include <QLineEdit>

LineEditPopUpForm::LineEditPopUpForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LineEditPopUpForm)
{
    ui->setupUi(this);
    setWindowFlag(Qt::Popup);
    m_lineedit = nullptr;




}

LineEditPopUpForm::~LineEditPopUpForm()
{
    delete ui;
}

void LineEditPopUpForm::on_testDurumu_geldi_clicked()
{
    if(m_lineedit) {
        m_lineedit->setText("Geldi");
    }
}


void LineEditPopUpForm::on_testDurumu_continue_clicked()
{
    if(m_lineedit) {
        m_lineedit->setText("Devam Ediyor");
    }
}


void LineEditPopUpForm::on_testDurumu_waiting_clicked()
{
    if(m_lineedit) {
        m_lineedit->setText("Bekliyor");
    }
}


void LineEditPopUpForm::on_testDurumu_bitti_clicked()
{
    if(m_lineedit) {
        m_lineedit->setText("Bitti");
    }
}


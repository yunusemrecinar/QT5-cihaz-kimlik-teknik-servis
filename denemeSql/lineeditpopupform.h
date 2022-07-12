#ifndef LINEEDITPOPUPFORM_H
#define LINEEDITPOPUPFORM_H

#include <QWidget>

class QLineEdit;

namespace Ui {
class LineEditPopUpForm;
}

class LineEditPopUpForm : public QWidget
{
    Q_OBJECT

public:
    explicit LineEditPopUpForm(QWidget *parent = nullptr);
    ~LineEditPopUpForm();

    void set_lineedit(QLineEdit *lineedit) {
        m_lineedit = lineedit;
    }

    QLineEdit *lineedit() const {
        return m_lineedit;
    }

private slots:
    void on_testDurumu_geldi_clicked();

    void on_testDurumu_continue_clicked();

    void on_testDurumu_waiting_clicked();

    void on_testDurumu_bitti_clicked();

private:
    Ui::LineEditPopUpForm *ui;
    QLineEdit *m_lineedit;
};

#endif // LINEEDITPOPUPFORM_H

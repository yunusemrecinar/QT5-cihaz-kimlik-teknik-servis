#ifndef SECDIALOG_H
#define SECDIALOG_H
#include <QtSql>

#include <QSqlDatabase>
#include <QMessageBox>
#include <QDialog>
#include <QMenu>


class QMenu;
class LineEditPopUpForm;

namespace Ui {
class SecDialog;
}

class SecDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SecDialog(QWidget *parent = nullptr);
    ~SecDialog();

private slots:
    void on_pushButton_clicked();

private:
    Ui::SecDialog *ui;
    QSqlDatabase database1;

    QMenu *m_lineedit_menu;
    LineEditPopUpForm *m_lineedit_popup_form;
};

#endif // SECDIALOG_H

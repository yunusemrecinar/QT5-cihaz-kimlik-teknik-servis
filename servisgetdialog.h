#ifndef SERVISGETDIALOG_H
#define SERVISGETDIALOG_H

#include <QDialog>
#include <QSqlDatabase>
#include "notlardialog.h"

namespace Ui {
class ServisGetDialog;
}

class ServisGetDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ServisGetDialog(QWidget *parent = nullptr);
    ~ServisGetDialog();

    QString key;

public slots:
    void initialize(QString s);
private slots:
    void on_pushButton_clicked();

private:
    Ui::ServisGetDialog *ui;

    QSqlDatabase database;

    notlarDialog *notlar;

};

#endif // SERVISGETDIALOG_H

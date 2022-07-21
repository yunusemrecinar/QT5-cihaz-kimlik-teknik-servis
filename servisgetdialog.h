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
    QString indexValue;

public slots:
    void initialize(QString s,QString index);
private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::ServisGetDialog *ui;

    QSqlDatabase database;

    notlarDialog *notlar;

};

#endif // SERVISGETDIALOG_H

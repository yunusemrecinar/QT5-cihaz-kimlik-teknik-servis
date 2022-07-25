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
    void initialize(QString index, QSqlDatabase d);
private slots:

    void on_pushButton_2_clicked();
    void donanimlar();
private:
    Ui::ServisGetDialog *ui;

    QString donanim;

    QSqlDatabase database;

    notlarDialog *notlar;

};

#endif // SERVISGETDIALOG_H

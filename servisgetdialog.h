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
    QString degisenParcalar = "";
    QString olay;
public slots:
    void initialize(QString index, QSqlDatabase d);
private slots:
    void changes();
    void on_pushButton_clicked();
    void donanimlar();
    void degisenParca();
    void commandChangedOlay(const QString& command_text);
private:
    Ui::ServisGetDialog *ui;

    QString donanim;

    QSqlDatabase database;

    notlarDialog *notlar;

};

#endif // SERVISGETDIALOG_H

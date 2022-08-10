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
    QString seriNo;

public slots:
    void initialize(QString index, QSqlDatabase d);
private slots:
    void changes();
    void on_pushButton_clicked();
    void donanimlar();
    void degisenParca();
    void commandChangedOlay(const QString& command_text);

    void on_donanim_1_clicked();

    void on_donanim_2_clicked();

    void on_donanim_3_clicked();

    void on_donanim_4_clicked();

    void on_donanim_8_clicked();

    void on_donanim_7_clicked();

    void on_donanim_9_clicked();

    void on_donanim_5_clicked();

    void on_donanim_6_clicked();

    void on_donanim_11_clicked();

    void on_donanim_10_clicked();
private:
    Ui::ServisGetDialog *ui;

    QString donanim;

    QSqlDatabase database;

    notlarDialog *notlar;

};

#endif // SERVISGETDIALOG_H

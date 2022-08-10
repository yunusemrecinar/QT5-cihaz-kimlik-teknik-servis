#ifndef INFORMATIONMUSTERIDIALOG_H
#define INFORMATIONMUSTERIDIALOG_H

#include <QDialog>
#include <QSqlDatabase>


namespace Ui {
class InformationMusteriDialog;
}

class InformationMusteriDialog : public QDialog
{
    Q_OBJECT

public:
    explicit InformationMusteriDialog(QWidget *parent = nullptr);
    ~InformationMusteriDialog();
public slots:
    void initialize(QSqlDatabase d, QString s);
private slots:

    void on_pushButton_clicked();

private:
    Ui::InformationMusteriDialog *ui;

    QSqlDatabase database;

    QString seriNo;
};

#endif // INFORMATIONMUSTERIDIALOG_H

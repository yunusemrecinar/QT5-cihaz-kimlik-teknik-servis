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

    QString username;
public slots:
    void initialize(QSqlDatabase d, QString s, QString username);
private slots:

    void on_pushButton_clicked();
    void setLog(QString log);
    void fillListViews();
    void changes();
    void updateChanges();

private:
    Ui::InformationMusteriDialog *ui;

    QSqlDatabase database;

    QString seriNo;

};

#endif // INFORMATIONMUSTERIDIALOG_H

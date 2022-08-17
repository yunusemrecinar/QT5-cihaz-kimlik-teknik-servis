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

    void setLog(QString log);
    void fillListViews();

    void changes();

    void updateChangesMusteri();
    void updateChangesToplam();

    void on_filter_selectionChanged();
    void on_filter_textChanged(const QString &arg1);

    void listViewMusteriChanged();
    void listViewToplamChanged();

private:
    Ui::InformationMusteriDialog *ui;

    QSqlDatabase database;

    QString seriNo;

};

#endif // INFORMATIONMUSTERIDIALOG_H

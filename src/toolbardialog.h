#ifndef TOOLBARDIALOG_H
#define TOOLBARDIALOG_H

#include <QDialog>
#include <QSqlDatabase>
namespace Ui {
class ToolBarDialog;
}

class ToolBarDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ToolBarDialog(QWidget *parent = nullptr);
    ~ToolBarDialog();

    QString rowLocation;

    QString username;
public slots:
    void initialize(QSqlDatabase d, QString type, QString databaseName, QString username);

private:
    Ui::ToolBarDialog *ui;

    QSqlDatabase database;

    QString databaseName_;

private slots:
    void refresh();
    void on_pushButtonEkle_clicked();
    void on_pushButtonSil_clicked();
    void on_tableView_clicked();

    void setLog(QString log);
};

#endif // TOOLBARDIALOG_H

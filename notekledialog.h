#ifndef NOTEKLEDIALOG_H
#define NOTEKLEDIALOG_H

#include <QDialog>
#include <QSqlDatabase>

namespace Ui {
class NotEkleDialog;
}

class NotEkleDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NotEkleDialog(QWidget *parent = nullptr);
    ~NotEkleDialog();
public slots:
    void initialize(QString s);
private slots:
    void on_pushButton_clicked();

private:
    Ui::NotEkleDialog *ui;

    QSqlDatabase database;

    QString servisNo;
};

#endif // NOTEKLEDIALOG_H

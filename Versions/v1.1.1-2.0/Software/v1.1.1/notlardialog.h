#ifndef NOTLARDIALOG_H
#define NOTLARDIALOG_H

#include <QDialog>
#include <QSqlDatabase>

namespace Ui {
class notlarDialog;
}

class notlarDialog : public QDialog
{
    Q_OBJECT

public:
    explicit notlarDialog(QWidget *parent = nullptr);
    ~notlarDialog();
public slots:
    void initialize(QString sira, QSqlDatabase d);
private slots:
    void on_pushButton_clicked();

private:
    Ui::notlarDialog *ui;
    QSqlDatabase database;
    QString data;
    QString servisNo;
};

#endif // NOTLARDIALOG_H

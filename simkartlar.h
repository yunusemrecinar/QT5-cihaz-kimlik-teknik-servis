#ifndef SIMKARTLAR_H
#define SIMKARTLAR_H

#include <QDialog>
#include <QSqlDatabase>

namespace Ui {
class SimKartlar;
}

class SimKartlar : public QDialog
{
    Q_OBJECT

public:
    explicit SimKartlar(QWidget *parent = nullptr);
    ~SimKartlar();
    QString rowLocation;
public slots:
    void initialize(QSqlDatabase d);
private:
    Ui::SimKartlar *ui;

    QSqlDatabase database;
private slots:
    void refresh();
    void on_pushButtonEkle_clicked();
    void on_pushButtonSil_clicked();
    void on_tableView_clicked();
};

#endif // SIMKARTLAR_H

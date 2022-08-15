#ifndef MUSTERIEKLE_H
#define MUSTERIEKLE_H

#include <QDialog>
#include <QSqlDatabase>


namespace Ui {
class MusteriEkle;
}

class MusteriEkle : public QDialog
{
    Q_OBJECT

public:
    explicit MusteriEkle(QWidget *parent = nullptr);
    ~MusteriEkle();
    QString username;

public slots:
    void initialize(QSqlDatabase, QString username);
private slots:
    void on_pushButton_clicked();
    void setLog(QString log);
private:
    Ui::MusteriEkle *ui;

    QSqlDatabase database;
};

#endif // MUSTERIEKLE_H

#ifndef MUSTERI_H
#define MUSTERI_H

#include <QDialog>
#include <QSqlDatabase>
#include <QSqlQueryModel>

namespace Ui {
class Musteri;
}

class Musteri : public QDialog
{
    Q_OBJECT

public:
    explicit Musteri(QWidget *parent = nullptr);
    ~Musteri();
    bool checkSeriNo = false;
public slots:
    void initialize(QSqlDatabase d);
private slots:
    void on_pushButton_clicked();

private:
    QSqlDatabase database;
    Ui::Musteri *ui;
};

#endif // MUSTERI_H

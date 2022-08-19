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
    QString rowId;
    QString username;
    QString musteriAdi;
public slots:
    void initialize(QSqlDatabase d, QString username);
private slots:
    void on_pushButton_clicked();

    void refresh();

    void on_tableView_clicked(const QModelIndex &index);

    void on_pushButton_sil_clicked();

    void on_tableView_doubleClicked(const QModelIndex &index);

    void on_lineEditSort_selectionChanged();

    void on_lineEditSort_textChanged(const QString &arg1);

    void setLog(QString log);
private:
    QSqlDatabase database;
    Ui::Musteri *ui;

    QString seriNo;
};

#endif // MUSTERI_H

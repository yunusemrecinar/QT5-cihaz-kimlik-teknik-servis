#ifndef SERVERGETDIALOG_H
#define SERVERGETDIALOG_H

#include <QDialog>
#include <QSqlDatabase>

namespace Ui {
class ServerGetDialog;
}

class ServerGetDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ServerGetDialog(QWidget *parent = nullptr);
    ~ServerGetDialog();

    QString key;
    QString indexValue;
    QString degisenParcalar = "";
    QString olay;
    QString seriNo;
public slots:
    void initialize(QString index, QSqlDatabase d);
private slots:
    void changes();

    void donanimlar();
    void degisenParca();
    void commandChangedOlay(const QString& command_text);
    void on_pushButton_clicked();

    void on_donanim_1_clicked();

    void on_donanim_2_clicked();

    void on_donanim_3_clicked();

private:
    Ui::ServerGetDialog *ui;

    QSqlDatabase database;

    QString donanim;
};

#endif // SERVERGETDIALOG_H

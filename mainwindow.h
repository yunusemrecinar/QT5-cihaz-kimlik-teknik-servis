#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSql>
#include <QSqlDatabase>
#include <QMessageBox>
#include "secdialog.h"
#include "informationdialog.h"
#include "servisdialog.h"
#include "servisgetdialog.h"

class QMenu;
class LineEditPopUpForm;

QT_BEGIN_NAMESPACE
namespace Ui {class MainWindow; }
QT_END_NAMESPACE


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    static MainWindow selectedVal;

    QString mainWindowValue;

    QSqlDatabase database1;
    QSqlDatabase database;

    QString hostName;
    QString userName;
    QString password;
    QString dbName;
    QString serviceValue;
    QString rowCount;

public slots:
    void readFile(QString filename);
    //QSqlQueryModel* setValue(QString qry);
signals:
    void notifyMessageSent(const QString& message);
private slots:

    //void on_pushButton_clicked();

    void addColumns();

    void on_pushButton_load_clicked();

    //void readFile(QString filename);

    void on_pushButton_2_clicked();

    //void on_tableView_activated(const QModelIndex &index);

    //void on_getInformation_clicked();

    //void on_pushButton_servis_verigetir_clicked();

    void on_pushButton_servis_ekle_clicked();

    //void on_pushButton_servis_bilgial_clicked();

    //void on_tableView_teknikServis_activated(const QModelIndex &index);

    void on_tableView_clicked(const QModelIndex &index);

    void on_tableView_teknikServis_clicked(const QModelIndex &index);

    void on_lineEdit_textChanged(const QString &arg1);

    void on_tableView_doubleClicked(const QModelIndex &index);

    void on_tableView_teknikServis_doubleClicked(const QModelIndex &index);

private:
    Ui::MainWindow *ui;

    QString selectedValue;
    InformationDialog* _information;
    InformationDialog *informationdialog;
    SecDialog *secdialog;
    ServisDialog *servisDialog;
    ServisGetDialog *servisGetDialog;


    QList<int> columnsToHide;
    //QSqlDatabase database2;

    QMenu *m_lineedit_menu;
    LineEditPopUpForm *m_lineedit_popup_form;
};
#endif // MAINWINDOW_H

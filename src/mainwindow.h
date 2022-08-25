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
#include <QTimer>
#include "serverservisdialog.h"

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

    QString type = "";

    int check = 0;

    QString isim;

    QSqlDatabase database1;
    QSqlDatabase database;

    QString name;

    QString hostName;
    QString userName;
    QString password;
    QString dbName;
    QString serviceValue;
    QString rowCount;

    QString rowMusteri;

public slots:
    void readFile(QString filename);

    void userCheck(QString filename);

    void changes();

    void refresh();

    void refreshMobiot();

    void refreshServer();

    //QSqlQueryModel* setValue(QString qry);
signals:
    void notifyMessageSent(const QString& message);
private slots:
    void setLog(QString log);

    //void on_pushButton_clicked();

    void resizeEvent(QResizeEvent* event);

    void refreshLog();

    void refreshServis();

    void hideColumns();

    void addModels();

    void addModemTipi();

    void hideColumnsMobiot();

    void hideColumnsServer();

    void addColumns();

    //void readFile(QString filename);

    void on_pushButton_2_clicked();

    //void on_tableView_activated(const QModelIndex &index);

    //void on_getInformation_clicked();

    //void on_pushButton_servis_verigetir_clicked();

    void on_pushButton_servis_ekle_clicked();

    //void on_pushButton_servis_bilgial_clicked();

    //void on_tableView_teknikServis_activated(const QModelIndex &index);

    void on_tableView_clicked();

    void on_tableView_teknikServis_clicked();

    void on_lineEdit_textChanged(const QString &arg1);

    void on_tableView_doubleClicked();

    void on_tableView_teknikServis_doubleClicked();

    void on_pushButton_clicked();

    void on_pushButton_modemTipi_clicked();

    void on_pushButton_Model_clicked();

    void on_lineEdit_selectionChanged();

    void on_splitter_splitterMoved();

    void on_pushButton_simKart_clicked();

    void on_pushButton_modeoGetir_clicked();

    void on_pushButton_mobiotGetir_clicked();

    void on_pushButton_serverGetir_clicked();

    void on_servisLineEdit_textChanged(const QString &arg1);

    void on_servisLineEdit_selectionChanged();

private:
    Ui::MainWindow *ui;

    QString selectedValue;
    InformationDialog* _information;
    InformationDialog *informationdialog;
    SecDialog *secdialog;
    ServisDialog *servisDialog;
    ServisGetDialog *servisGetDialog;
    ServerServisDialog *serverServisDialog;

    QList<int> columnsToHideService;
    QList<int> columnsToHide;
    QList<int> columnsToHideMobiot;
    QList<int> columnsToHideServer;
    //QSqlDatabase database2;

    QMenu *m_lineedit_menu;
    LineEditPopUpForm *m_lineedit_popup_form;

    QTimer *timer;

    QSqlQueryModel *model = new QSqlQueryModel();
    QSqlQueryModel *modelMobiot = new QSqlQueryModel();
    QSqlQueryModel *modelServer = new QSqlQueryModel();

    QString cihazModel;

    int countModel;
    int countModemTipi;
};
#endif // MAINWINDOW_H

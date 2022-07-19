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

    QString serviceValue;

public slots:

signals:
    void notifyMessageSent(const QString& message);
private slots:

    void on_pushButton_clicked();

    void on_pushButton_load_clicked();

    void on_pushButton_2_clicked();

    void on_tableView_activated(const QModelIndex &index);

    void on_getInformation_clicked();

    void on_pushButton_servis_verigetir_clicked();

    void on_pushButton_servis_ekle_clicked();

    void on_pushButton_servis_bilgial_clicked();

    void on_tableView_teknikServis_activated(const QModelIndex &index);

    void on_tableView_clicked(const QModelIndex &index);

    void on_tableView_teknikServis_clicked(const QModelIndex &index);

private:
    Ui::MainWindow *ui;

    QString selectedValue;
    InformationDialog* _information;
    InformationDialog *informationdialog;
    SecDialog *secdialog;
    ServisDialog *servisDialog;
    ServisGetDialog *servisGetDialog;

    QSqlDatabase database;

    //QSqlDatabase database2;

    QMenu *m_lineedit_menu;
    LineEditPopUpForm *m_lineedit_popup_form;
};
#endif // MAINWINDOW_H

#include "mainwindow.h"

#include <QApplication>
#include <QtSql/QtSql>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QMessageBox>
#include <iostream>
using namespace std;


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setStyle("fusion");
    MainWindow w;
    w.database = QSqlDatabase::addDatabase("QMYSQL");
    w.database.setHostName(w.hostName);
    w.database.setUserName(w.userName);
    w.database.setPassword(w.password);
    w.database.setDatabaseName(w.dbName);
    w.database.open();
    w.show();
    return a.exec();
}

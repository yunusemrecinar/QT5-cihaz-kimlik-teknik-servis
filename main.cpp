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
    w.readFile("test.txt");
    w.database = QSqlDatabase::addDatabase("QMYSQL");
    w.database.setHostName(w.hostName);
    w.database.setUserName(w.userName);
    w.database.setPassword(w.password);
    w.database.setDatabaseName(w.dbName);
    w.database.open();
    w.userCheck("name.txt");
    if(w.check == 0) {
         exit(EXIT_FAILURE);
    }
    w.refresh();
    w.show();
    return a.exec();
}

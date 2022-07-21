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

    w.show();
    return a.exec();
}

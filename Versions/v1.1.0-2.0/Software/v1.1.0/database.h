#ifndef DATABASE_H
#define DATABASE_H
#include <QSqlDatabase>

class database
{
public:
    database();
    QSqlDatabase db;
    QString hostName;
    QString userName;
    QString password;
    QString dbName;
public slots:
    void connectDb();
    void readFile(QString filename);
};

#endif // DATABASE_H

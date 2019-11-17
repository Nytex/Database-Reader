#ifndef DATABASEWRAPPER_H
#define DATABASEWRAPPER_H

#include <QObject>
#include <QDebug>
#include <QSqlQuery>
#include <QSqlField>
#include <QtSql>
#include <QCoreApplication>
#include <QSqlDatabase>

class DatabaseWrapper : public QObject
{
    Q_OBJECT
public:
    explicit DatabaseWrapper(QObject *parent = nullptr);
    ~DatabaseWrapper();

signals:

public slots:
    void init();
    void deinit();
    QStringList readAllData();

    //Insert and Remove Data
    void createTable();
    bool createDatabase();
    void insertData(QString content);
    void removeData(QString content);
    void clearDatabase();



private:
    QSqlDatabase db;
    QSqlQuery qry;

};

#endif // DATABASEWRAPPER_H

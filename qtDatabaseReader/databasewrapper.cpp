#include "databasewrapper.h"

DatabaseWrapper::DatabaseWrapper(QObject *parent) : QObject(parent)
{

}

DatabaseWrapper::~DatabaseWrapper()
{

}

void DatabaseWrapper::init()
{
    QSqlQuery qry("SELECT * FROM DATA_TABLE");
    //Create Table if no Exist
    if(!qry.exec()){
        createTable();
    }

    qry.finish();
}

void DatabaseWrapper::deinit()
{
    db.close();
}

QStringList DatabaseWrapper::readAllData()
{
    db.open();

    QStringList currentData;



    //return if database unable to open
    if(!db.isOpen())
        return currentData;

    QSqlQuery query("SELECT * FROM DATA_TABLE");
    while (query.next())
        currentData.append(query.value("DATA").toString());

    //Close database
    db.close();

    return currentData;

}

void DatabaseWrapper::createTable()
{
    QString TABLE_NAME = "DATA_TABLE";
    QString COLUMN_ID = "ID";
    QString COLUMN_CREATED = "CREATED";
    QString COLUMN_UPDATED = "UPDATED";
    QString COLUMN_DATA = "DATA";


    QSqlQuery query("CREATE TABLE " + TABLE_NAME + "("
                    + COLUMN_ID + " INTEGER PRIMARY KEY AUTOINCREMENT,"
                    + COLUMN_CREATED + " DATETIME DEFAULT CURRENT_TIMESTAMP,"
                    + COLUMN_UPDATED + " DATETIME DEFAULT CURRENT_TIMESTAMP,"
                    + COLUMN_DATA + " TEXT"
                    + ")");

    // Create table trigger
    QSqlQuery trigger1("CREATE TRIGGER "+TABLE_NAME+"_AI AFTER INSERT ON "+TABLE_NAME+" WHEN (NEW.CREATED IS NULL) BEGIN UPDATE "+TABLE_NAME+" SET CREATED = DATETIME('now','localtime') WHERE ID = NEW.ID; END;");
    QSqlQuery trigger2("CREATE TRIGGER "+TABLE_NAME+"_AU AFTER UPDATE ON "+TABLE_NAME+" begin UPDATE "+TABLE_NAME+" SET UPDATED = DATETIME('now','localtime') WHERE ID = OLD.ID; END;");

    query.exec();
    query.finish();
    trigger1.exec();
    trigger1.finish();
    trigger2.exec();
    trigger2.finish();
}

bool DatabaseWrapper::createDatabase()
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("C:/Test/Qt_Database.db");

    if(db.open())
        return true;
    else
        return false;
}

void DatabaseWrapper::insertData(QString content)
{
    db.open();
    QSqlQuery query;
    query.prepare("INSERT INTO DATA_TABLE(DATA) VALUES(:CONTENT)");
    query.bindValue(":CONTENT",content);

    query.exec();
}

void DatabaseWrapper::removeData(QString content)
{
    db.open();
    QSqlQuery query;
    query.prepare("DELETE FROM DATA_TABLE WHERE DATA=:CONTENT");
    query.bindValue(":CONTENT",content);

    query.exec();
}

void DatabaseWrapper::clearDatabase()
{
    db.open();
    QSqlQuery d_qry("DELETE FROM DATA_TABLE");
    d_qry.exec();
    d_qry.finish();
}

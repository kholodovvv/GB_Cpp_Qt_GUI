#include "database.h"
#include <QFile>
#include <QVariant>

DataBase::DataBase(QObject *parent)
    :QObject(parent)
{

}

DataBase::~DataBase()
{
    if(db.isOpen()) db.close();
}

bool DataBase::openDB(const QString dbname)
{
    if(QFile(dbname).exists()){
        db = QSqlDatabase::addDatabase("QSQLITE", dbname);
        db.setDatabaseName(dbname);
    }else{
        return false;
    }

    return db.open() ?  true : false;
}

void DataBase::CloseDB()
{
    if(db.isOpen()) db.close();
}

bool DataBase::insertRecord(const QString &dt, const QString &task, const int &prog)
{
    QSqlQuery query(db);
    query.prepare("INSERT INTO Tasks (date, task, progress) VALUES (:Dt, :Task, :Progress);");
    query.bindValue(":Dt", dt);
    query.bindValue(":Task", task);
    query.bindValue(":Progress", prog);

    return query.exec() ? true : false;
}

void DataBase::readData()
{
    QSqlQuery query(db);
    if(query.exec("SELECT date, task, progress FROM Tasks")){
        for(;query.next();){
            emit loadData(query.value(0).toString(), query.value(1).toString(), query.value(2).toString());
        }
    }
}

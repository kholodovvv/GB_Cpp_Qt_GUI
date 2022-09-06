#ifndef DATABASE_H
#define DATABASE_H

#include <QObject>
#include <QSql>
#include <QSqlQuery>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlTableModel>

class DataBase: public QObject
{

Q_OBJECT

public:
    explicit DataBase(QObject* parent = nullptr);
    virtual ~DataBase();

    Q_INVOKABLE
    bool openDB(const QString);

    Q_INVOKABLE
    void CloseDB();

    Q_INVOKABLE
    bool insertRecord(const QString&, const QString&, const int&);

    Q_INVOKABLE
    void readData();

private:
    QSqlDatabase db;
    QSqlTableModel model;

signals:
    void loadData(QVariant dt, QVariant task, QVariant prog);
};

#endif // DATABASE_H

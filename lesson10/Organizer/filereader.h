#ifndef FILEREADER_H
#define FILEREADER_H

#include <QObject>
#include <QFile>

class FileReader: public QObject
{
    Q_OBJECT

public:
    explicit FileReader();
    virtual ~FileReader();

    Q_INVOKABLE
    void readFile();

    Q_INVOKABLE
    void addRecord(QString, QString, QString);

private:
    QFile *file;
    int count_record;

signals:
    void loadData(QString str);
};

#endif // FILEREADER_H

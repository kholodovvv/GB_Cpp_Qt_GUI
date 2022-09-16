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
    //void initEnd(bool succed);
    void loadData(int counter); //Так как заданием не предусмотрено
    //отображение сохраненных данных в программе, то и извлекать их из
    //файла не за чем. Вернём просто количество записей в файле.
};

#endif // FILEREADER_H

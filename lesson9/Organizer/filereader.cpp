#include "filereader.h"
#include <QTextStream>

FileReader::FileReader(): file(nullptr), count_record(0)
{

}

FileReader::~FileReader()
{
    if(file)file->close();
}

void FileReader::readFile()
{
    file = new QFile("./db", this);

    if(!file) return;
    if(!file->open(QIODevice::ReadWrite)){
        return;
    }

    QTextStream stream(file);

    while(!stream.atEnd()){
        QString line = stream.readLine();
        if(line.length() > 0) count_record++;
    }

    emit loadData(count_record);
}

void FileReader::addRecord(QString task, QString dl, QString progress)
{
    QTextStream stream(file);
    stream << task + "\n";
    stream.reset();
    stream << dl + "\n";
    stream.reset();
    stream << progress + "\n";
}

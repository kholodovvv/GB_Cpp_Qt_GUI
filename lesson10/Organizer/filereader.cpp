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
    QString buildLine;
    int counter = 0;

    while(!stream.atEnd()){
        QString line = stream.readLine();

        if(line.length() > 0){
            buildLine.append(" " + line);
            counter++;
        }

        if(counter == 3){
            emit loadData(buildLine);
            counter = 0;
            buildLine.clear();
        }
    }

}

void FileReader::addRecord(QString task, QString dl, QString progress)
{
    QTextStream stream(file);
    stream << dl + "\n";
    stream.reset();
    stream << task + "\n";
    stream.reset();
    stream << progress + "\n";
}

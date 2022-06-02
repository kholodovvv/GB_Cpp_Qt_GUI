#ifndef TEXTPARSER_H
#define TEXTPARSER_H

#include <QString>
#include <QVector>

class TextParser{
public:
    TextParser();
    bool TextChange(QString in_str);
    QString GetString();

private:
    qint32 cur_pos, point_pos;
    QString resp_str; //возвращаемая разобраная строка
    QVector<QPair<QString, QChar>> vecReplWord;
};

#endif // TEXTPARSER_H

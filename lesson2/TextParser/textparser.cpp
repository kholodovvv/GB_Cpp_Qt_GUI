#include "textparser.h"

#include <QDebug>

TextParser::TextParser()
{
    cur_pos = 0;
    point_pos = 0;

    //заполняем вектор замены ключевых слов
    QPair<QString, QChar> pr;

    pr.first = "руб";
    pr.second = QChar(8381);
    vecReplWord.push_back(pr);

    pr.first = "промилле";
    pr.second = QChar(2030);
    vecReplWord.push_back(pr);

    pr.first = "евро";
    pr.second = QChar(8364);
    vecReplWord.push_back(pr);

    pr.first = "копирайт";
    pr.second = QChar(169);
    vecReplWord.push_back(pr);
}

//метод проверяет есть ли в тексте секции #@ключевое слово@ для замены
//если есть, то разберёт строку, заменит "ключевое слово" на символ и вернёт true
bool TextParser::TextChange(QString in_str)
{
    QString key_word;
    qint16 size_word;
    bool repl_flag = false; //флаг поднимается когда нашлась замена "ключевому слову"

    key_word = in_str.section("@", 1, 1);
    if(key_word.length() < 3){
        return false;
    }else{
        //поиск символа для замены
        for(auto it = vecReplWord.begin(); it != vecReplWord.end(); it++){
            if(it->first == key_word){
                size_word = key_word.length();
                key_word = it->second;
                repl_flag = true;
                break;
            }
        }

        //если найдена замена ключевому слову, тогда производим разбор и замену в строке
        if(repl_flag){
            point_pos = in_str.indexOf("#@", cur_pos); //позиция первого вхождения
            cur_pos += point_pos + (size_word + 1);
            resp_str = in_str.replace(point_pos, cur_pos - point_pos, key_word);
        }else{
            return false;
        }

    }

    return true;
}

QString TextParser::GetString()
{
    return resp_str;
}

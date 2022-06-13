#ifndef HOTKEYSWINDOW_H
#define HOTKEYSWINDOW_H

#include <QWidget>

#include "mainwindow.h"


namespace Ui {
class hotkeyswindow;
}

class hotkeyswindow : public QWidget
{
    Q_OBJECT

public:
    explicit hotkeyswindow(QWidget *parent = nullptr);
    ~hotkeyswindow();

private:
    Ui::hotkeyswindow *ui;
    //MainWindow* MW;
};

#endif // HOTKEYSWINDOW_H

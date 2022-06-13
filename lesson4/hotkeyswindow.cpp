#include "hotkeyswindow.h"
#include "ui_hotkeyswindow.h"

hotkeyswindow::hotkeyswindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::hotkeyswindow)
{
    ui->setupUi(this);


    /*for(auto it = MW->vecHotKey.begin(); it != MW->vecHotKey.end(); it++){
        ui->cmbCommands->insertItem(it->idx, it->command);
    }*/
}

hotkeyswindow::~hotkeyswindow()
{
    delete ui;
}

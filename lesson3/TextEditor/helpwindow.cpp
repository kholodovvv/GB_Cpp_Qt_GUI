#include "helpwindow.h"
#include "ui_helpwindow.h"

#include <QFile>
#include <QMessageBox>

helpwindow::helpwindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::helpwindow)
{
    ui->setupUi(this);

    QFile res(":/help/help.html");

    if(res.exists()){
        if(res.open(QIODevice::ReadOnly|QIODevice::Text)){
            ui->textBrowser->setHtml(res.readAll());
        }else{
            QMessageBox::critical(this, "Ошибка", "Ошибка открытия файла!");
        }
    }

}

helpwindow::~helpwindow()
{
    delete ui;
}

void helpwindow::on_pbtnClose_clicked()
{
    QWidget::close();
}

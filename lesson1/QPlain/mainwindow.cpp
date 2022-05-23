#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pbtnAddText_clicked()
{
    if(ui->plTextEdit1->toPlainText().isEmpty()){
        QMessageBox::critical(this, "Ошибка", "Отсутствует текст для добавления");
    }else{
        ui->plTextEdit2->appendPlainText(ui->plTextEdit1->toPlainText());
    }

}

void MainWindow::on_pbtnEditText_clicked()
{
    if(ui->plTextEdit2->toPlainText().isEmpty()){
        QMessageBox::critical(this, "Ошибка", "Отсутствует текст для замены");
    }else{
        ui->plTextEdit1->setPlainText(ui->plTextEdit2->toPlainText());
    }
}

void MainWindow::on_pbtnAddHtml_clicked()
{
    ui->plTextEdit2->clear();
    ui->plTextEdit2->appendHtml("<Html><H3><font color='blue'><b>Hello World!</b></font></H3></Html>");
}

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QPlainTextEdit>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    textParser = new TextParser();
    ui->plText->installEventFilter(this);


}

MainWindow::~MainWindow()
{
    if (textParser) {
        delete textParser;
        textParser = nullptr;
    }

    delete ui;
}


void MainWindow::on_plText_textChanged()
{
    if(textParser->TextChange(ui->plText->toPlainText())){
        ui->plText->setPlainText(textParser->GetString());
    }
}


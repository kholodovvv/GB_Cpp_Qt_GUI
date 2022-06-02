#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QMessageBox>
#include <QDebug>

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

void MainWindow::OpenAndParse(QString filepath)
{
    QFile file(filepath);
    QString textdata, current_textdata, city, temper, curseUSD, curseEUR;

       if(file.open(QIODevice::ReadOnly)){
           textdata = file.readAll();
       }else{
           QMessageBox::critical(this, "Ошибка", "Ошибка открытия файла!");
           return;
       }

       file.close();

    //парсим страницу
    //Выбираем сведения о погоде в регионе
    current_textdata = textdata;
    city = current_textdata.section("data-testid=\"weather-city\">", 1, 1);
    city = city.section("</a>", 0, 0);
    ui->textCity->setText(city);

    current_textdata = textdata;
    temper = current_textdata.section("data-testid=\"weather-temp\">", 1, 1);
    temper = temper.section("</span>", 0, 0);
    ui->textTemperature->setText(temper);

    //Выбираем сведения о курсах валют
    curseUSD = current_textdata.section("<div class=\"rate__currency svelte-19b6xeo\">", 1, 1);
    curseUSD = curseUSD.section("</div>", 0, 0);
    ui->textUSD->setText(curseUSD);

    curseEUR = current_textdata.section("<div class=\"rate__currency svelte-19b6xeo\">", 2, 2);
    qDebug() << curseEUR;
    curseEUR = curseEUR.section("</div>", 0, 0);
    ui->textEUR->setText(curseEUR);
}


void MainWindow::on_pbtnOpen_clicked()
{
    QString open_file_name = QFileDialog::getOpenFileName(this, "Открыть", QDir::currentPath(), "Htm(*.htm);;ALL(*.*)");

    if(!open_file_name.isEmpty())
        OpenAndParse(open_file_name);
}

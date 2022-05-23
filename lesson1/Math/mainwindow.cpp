#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtMath>
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

void MainWindow::on_cmbCalculateEquation_clicked()
{
    float root1, root2;

    //Проверка ввода исходных данных
    if(ui->lneRatioA->text().isEmpty() || ui->lneRatioB->text().isEmpty() || ui->lneRatioC->text().isEmpty())
    {
        QMessageBox::critical(this, "Ошибка!", "Все входные данные обязательны к заполнению");
    }
    else if(ui->lneRatioA->text().toFloat() != 0)
    {
        //Рассчитываем дискриминант D = b2 − 4ac
        float d = qPow(ui->lneRatioB->text().toFloat(), 2) - (4 * ui->lneRatioA->text().toFloat() * ui->lneRatioC->text().toFloat());

        if(d < 0){ //если корней нет
            ui->lneResult->setText("корней нет");
        }
        else if(d == 0) //если корень один -(b / 2) / a
        {
            root1 = (-(ui->lneRatioB->text().toFloat()) / 2) / ui->lneRatioA->text().toFloat();
            ui->lneResult->setText(QString::number(root1));
        }
        else //если 2 корня
        {
            root1 = ((-(ui->lneRatioB->text().toFloat()) / 2) + (qSqrt(d / 4))) / ui->lneRatioA->text().toFloat();
            root2 = ((-(ui->lneRatioB->text().toFloat()) / 2) - (qSqrt(d / 4))) / ui->lneRatioA->text().toFloat();
            ui->lneResult->setText(QString::number(root1) + " ; " + QString::number(root2));
        }
    }
    else //если первый коэффициент равен 0, то уравнение 1-ой степени (a - c) / b
    {
        root1 = (ui->lneRatioA->text().toFloat() - ui->lneRatioC->text().toFloat()) / ui->lneRatioB->text().toFloat();
        ui->lneResult->setText(QString::number(root1));
    }
}

void MainWindow::on_cmbCalculateTriagle_clicked()
{
    float corner;

    //Проверка ввода исходных данных
    if(ui->lneSideA->text().isEmpty() || ui->lneSideB->text().isEmpty() || ui->lneCorner->text().isEmpty())
    {
        QMessageBox::critical(this, "Ошибка!", "Все входные данные обязательны к заполнению");
    }
    else
    {
        if(ui->rdbRadians->isChecked()) //выражаем радианы в градусах 1 град = 180/п
        {
            corner = (ui->lneCorner->text().toFloat() * 180) / 3.1416;
        }
        else
        {
            corner = ui->lneCorner->text().toFloat();
        }

        float result = qSqrt((qPow(ui->lneSideA->text().toFloat(), 2) + qPow(ui->lneSideB->text().toFloat(), 2)) - (2 * ui->lneSideA->text().toFloat() * ui->lneSideB->text().toFloat()                                                                                                           * qCos(corner)));
        ui->lneResultTriagle->setText(QString::number(result));
    }

}


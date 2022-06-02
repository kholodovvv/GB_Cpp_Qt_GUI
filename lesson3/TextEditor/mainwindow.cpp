#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QFile>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    Q_INIT_RESOURCE(resources);
    ui->faqButton->setIconSize(QSize(48,48));
    ui->faqButton->setIcon(QPixmap(":/img/faq.png"));
}

MainWindow::~MainWindow()
{
    delete ui;
}

QString MainWindow::ReadFile(const QString file_path)
{
    QFile file(file_path);
    QString textdata;

    if(file.open(QIODevice::ReadOnly)){
        textdata = file.readAll();
    }else{
        QMessageBox::critical(this, "Ошибка", "Ошибка открытия файла!");
    }

    file.close();

    return textdata;
}

bool MainWindow::SaveFile(const QString file_path, const QString textdata)
{
    QFile file(file_path);
    QByteArray data;

    data.append(QString(textdata).toUtf8());

        if(file.open(QIODevice::WriteOnly)){
            file.write(data);
        }else{
            QMessageBox::critical(this, "Ошибка", "Ошибка записи в файл!");
            return false;
        }

    file.close();

    return true;
}


void MainWindow::on_pbtnOpen_clicked()
{
    QString open_file_name = QFileDialog::getOpenFileName(this, "Открыть", QDir::currentPath(), "Text(*.txt);;ALL(*.*)");

    if(!open_file_name.isEmpty())
        ui->plainTextEdit->setPlainText(ReadFile(open_file_name));
}

void MainWindow::on_pbtnSave_clicked()
{
    QString save_file_name = QFileDialog::getSaveFileName(this, "Сохранить", QDir::currentPath(), "Text(*.txt);;ALL(*.*)");

    if(!save_file_name.isEmpty())
        SaveFile(save_file_name, ui->plainTextEdit->toPlainText()) ? QMessageBox::information(this, "Сообщение", "Файл успешно сохранен!")
                                                                   : QMessageBox::critical(this, "Ошибка", "Ошибка записи файла!");

}

void MainWindow::on_faqButton_clicked()
{
   help_window.show();
}

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //заполняем ListWidget данными
    //устанавливаем размер иконок
    ui->listWidget->setIconSize(QSize(48,48));

    foreach(const QString& item, LIST_ITEMS ) {
        QListWidgetItem* listItem = new QListWidgetItem(item);
        listItem->setIcon(QPixmap(icon_path + item + ".png"));
        // Включаем возможность редактирования
        listItem->setFlags(Qt::ItemIsEditable | Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsDragEnabled);
        ui->listWidget->addItem(listItem);
    }

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pbtnAdd_clicked()
{
    QListWidgetItem *item = new QListWidgetItem;
    item->setIcon(QPixmap(icon_path + "C++" + ".png" ));
    item->setFlags(Qt::ItemIsEditable | Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsDragEnabled);
    ui->listWidget->addItem(item);
}

void MainWindow::on_chkShowIcon_clicked()
{
    if(ui->chkShowIcon->isChecked()){
        ui->listWidget->setViewMode(QListView::IconMode);
    }else{
        ui->listWidget->setViewMode(QListView::ListMode);
    }

}

void MainWindow::on_pbtnDelete_clicked()
{
    QListWidgetItem *item = ui->listWidget->takeItem(ui->listWidget->currentRow());
    delete item;
}

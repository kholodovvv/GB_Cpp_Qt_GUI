#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
: QMainWindow(parent)
{
    fmqw = new FileViewWidget(this);
}

MainWindow::~MainWindow()
{}

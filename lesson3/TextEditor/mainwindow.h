#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "helpwindow.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QString ReadFile(const QString file_path);
    bool SaveFile(const QString file_path, const QString textdata);

private slots:
    void on_pbtnOpen_clicked();
    void on_pbtnSave_clicked();

    void on_faqButton_clicked();

private:
    Ui::MainWindow *ui;
    helpwindow help_window;
};
#endif // MAINWINDOW_H

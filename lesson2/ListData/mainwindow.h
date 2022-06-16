#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QCoreApplication>
#include <QStringListModel>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

static const QStringList LIST_ITEMS =
    QStringList() << "C++" << "Python" << "Java" << "C#" << "PHP";

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pbtnAdd_clicked();

    void on_chkShowIcon_clicked();

    void on_pbtnDelete_clicked();

private:
    Ui::MainWindow *ui;
    QString icon_path = ":/img/";
};
#endif // MAINWINDOW_H

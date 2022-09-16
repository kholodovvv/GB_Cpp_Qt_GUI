#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QTcpSocket>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_cmbSearch_clicked();
    void OnResponse(QNetworkReply &reply);
    void ImageLoader(QNetworkReply &reply);

private:
    void FindRequest(const QString str);
    void TextParser(const QString &txt);
    QNetworkAccessManager* manager;
    const QString host_address = "https://yandex.ru";
    QPixmap pixmap;

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H

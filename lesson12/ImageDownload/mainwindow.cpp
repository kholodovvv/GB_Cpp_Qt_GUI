#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->listWidget->setViewMode(QListView::IconMode); //режим отображения картинок
    ui->listWidget->setIconSize(QSize(200, 200));
}

MainWindow::~MainWindow()
{
    delete ui;
    delete manager;
}

void MainWindow::on_cmbSearch_clicked()
{
    FindRequest(ui->lneTextSearch->text());
}

void MainWindow::FindRequest(const QString str)
{
    ui->listWidget->clear();
    manager = new QNetworkAccessManager(this);

    QNetworkRequest request(QUrl(host_address + "/images/search?text=" + str));

     manager->get(request);

    connect(manager, &QNetworkAccessManager::finished, this, [=](QNetworkReply *reply) {
        if (reply->error()) { qDebug() << reply->errorString(); return; }else{MainWindow::OnResponse(*reply);}
    });

}

void MainWindow::TextParser(const QString &txt)
{
    QRegExp reg("<img class=\"serp.*src=\"//([^\"]+)\"");
    reg.setMinimal(true);

    int lpos;
    manager = new QNetworkAccessManager(this);

    while((lpos = reg.indexIn(txt, lpos)) != -1){
        lpos += reg.matchedLength();

        QNetworkRequest request(QUrl("https://" + reg.cap(1)));
        manager->get(request);

        connect(manager, &QNetworkAccessManager::finished, this, [=](QNetworkReply *reply) {
            if (reply->error()) {
                qDebug() << reply->errorString();
                delete manager;
                return;
            }else{
                MainWindow::ImageLoader(*reply);
            }
        });

    }

}

void MainWindow::ImageLoader(QNetworkReply &reply)
{

    pixmap.loadFromData(reply.readAll());

    if(pixmap.size() != QSize(0, 0)){
        QListWidgetItem *item = new QListWidgetItem(pixmap, "", ui->listWidget, 0);
        ui->listWidget->addItem(item);
    }

}

void MainWindow::OnResponse(QNetworkReply &reply)
{
    QByteArray buffer;

    while(reply.bytesAvailable() > 0){
        buffer = reply.readAll();
    }

    delete manager;
    if(buffer.size() > 0){
        TextParser(QString(buffer));
    }

}


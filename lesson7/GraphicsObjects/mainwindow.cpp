#include "mainwindow.h"
#include <QWheelEvent>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QGraphicsView(parent)
{
    srand(clock());
    scene = new QGraphicsScene(this);
    setScene(scene);


    object_counter = 0;
}

MainWindow::~MainWindow()
{
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    BlockScheme* itm = dynamic_cast<BlockScheme*>(itemAt(event->pos()));

    if(event->button() == Qt::LeftButton && itm == nullptr){
        if(object_counter > 2) object_counter = 0;

        switch (object_counter) {
            case 0:
                BS = new BlockScheme(this);
                connect(BS, SIGNAL(reDraw()), this, SLOT(onReDraw()));
                BS->geometry = BS->Geometry::RECTAGLE;
                object_counter++;
            break;

            case 1:
                BS = new BlockScheme(this);
                connect(BS, SIGNAL(reDraw()), this, SLOT(onReDraw()));
                BS->geometry = BS->Geometry::ELLIPS;
                object_counter++;
            break;

            case 2:
                BS = new BlockScheme(this);
                connect(BS, SIGNAL(reDraw()), this, SLOT(onReDraw()));
                BS->geometry = BS->Geometry::STAR;
                object_counter++;
            break;
        }

        BS->setPos(event->pos().x(), event->pos().y());
        BS->setFlags(QGraphicsItem::ItemIsMovable);
        scene->addItem(BS);

    }else if(event->button() == Qt::RightButton){
        auto iClick = dynamic_cast<BlockScheme*>(itemAt(event->pos()));
        delete iClick;

        onReDraw();
    }else{
        itm->moving = true;
        itm->bpoint = event->pos();
    }

}

void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    BlockScheme* itm = dynamic_cast<BlockScheme*>(itemAt(event->pos()));

    if(event->button() == Qt::LeftButton && itm != nullptr){
        itm->moving = false;
        onReDraw();
    }
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    BlockScheme* itm = dynamic_cast<BlockScheme*>(itemAt(event->pos()));

    if(itm->moving){
        QPoint p = event->pos() - itm->bpoint;
        itm->x += p.x();
        itm->y += p.y();
        itm->bpoint = event->pos();
        onReDraw();
    }
}

void MainWindow::wheelEvent(QWheelEvent *event)
{
    if(event->delta() > 0){
        scale(1.1, 1.1);
    }else{
        scale(1 / 1.1, 1 / 1.1);
    }


}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key::Key_Plus){
        scale(1.1, 1.1);
    }else if(event->key() == Qt::Key::Key_Minus){
        scale(1 / 1.1, 1 / 1.1);
    }
}

void MainWindow::onReDraw()
{
    scene->update();
    update();
}



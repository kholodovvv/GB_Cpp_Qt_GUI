#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QKeyEvent>
#include "blocksceme.h"

class MainWindow : public QGraphicsView
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    QGraphicsScene* scene;
    BlockScheme* BS;
    int object_counter;

private:
    void mousePressEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void wheelEvent(QWheelEvent* event) override;
    void keyPressEvent(QKeyEvent *event) override;

private slots:
    void onReDraw();

};
#endif // MAINWINDOW_H

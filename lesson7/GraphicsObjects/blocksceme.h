#pragma once

#include <QObject>
#include <QGraphicsItem>
#include <QBrush>


class BlockScheme: public QObject, public QGraphicsItem
{
    Q_OBJECT
    Q_PROPERTY(QBrush brush)

public:
    explicit BlockScheme(QObject* parent = nullptr);
    void setBrush(QBrush brush){ this->brush = brush; }

public:
    enum Geometry{RECTAGLE, ELLIPS, STAR};
    Geometry geometry;
    bool moving;
    QPoint bpoint;
    int x, y;

private:
    QBrush brush;

signals:
    void reDraw();

private:
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget);
    QRectF boundingRect() const override;
};

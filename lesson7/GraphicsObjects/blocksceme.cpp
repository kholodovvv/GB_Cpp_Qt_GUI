#include "blocksceme.h"
#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <qmath.h>

BlockScheme::BlockScheme(QObject *parent)
    :QObject(parent), QGraphicsItem()
{
    x = 0;
    y = 0;

    brush.setColor(QColor(rand() % 256, rand() % 256, rand() % 256));
    brush.setStyle(Qt::BrushStyle::SolidPattern);
    moving = false;
}

void BlockScheme::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setBrush(brush);
    if(geometry == Geometry::ELLIPS) painter->drawEllipse(x, y, 200, 100);
    if(geometry == Geometry::RECTAGLE) painter->drawRect(x, y, 200, 100);

    if(geometry == Geometry::STAR){
        qreal R = 100; // радиус
        const qreal Pi = 3.1415926;
        qreal deg = Pi * 72/180;
        QPoint points[5] = {
            QPoint(R,0),
            QPoint(R*cos(deg),-R*sin(deg)),
            QPoint(R*cos(2*deg),-R*sin(2*deg)),
            QPoint(R*cos(3*deg),-R*sin(3*deg)),
            QPoint(R*cos(4*deg),-R*sin(4*deg)),
        };

        QPainterPath starPath;
        starPath.moveTo(points[0]);
        starPath.lineTo(points[2]);
        starPath.lineTo(points[4]);
        starPath.lineTo(points[1]);
        starPath.lineTo(points[3]);
        starPath.closeSubpath();

        painter->translate(100, 120);
        painter->drawPath(starPath);
    }

    Q_UNUSED(option);
    Q_UNUSED(widget);
}

QRectF BlockScheme::boundingRect() const
{
    return QRectF(x, y, 200, 100);
}

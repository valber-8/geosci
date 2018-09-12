#ifndef RECTOBJECT_H
#define RECTOBJECT_H

#include <QGraphicsRectItem>
#include <QRect>
#include <QString>
#include <QRectF>
#include <QPainter>
#include <QBrush>
#include <QPen>
#include <QGraphicsTextItem>
#include <QPointF>
class RectObject : public QGraphicsItem
{
public:
    RectObject();
    RectObject(QRectF,QString,QColor,QPen);
    void setColor(QColor);
    void setPen(QPen);
    QColor color();
    QPen pen();
    void setText(QString);
    QRect rect();
private:
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    virtual QRectF boundingRect() const;

    QRectF _rect;
    QColor _color;
    QPen _pen;

    void paint ( QPainter *,
                 const QStyleOptionGraphicsItem *,
                 QWidget *);
    QGraphicsTextItem _text;

    QPointF press_point;
    bool pressed;
};

#endif // RECTOBJECT_H

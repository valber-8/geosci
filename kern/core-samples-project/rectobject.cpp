#include "rectobject.h"
#include <QPainter>
#include <QGraphicsRectItem>
#include <QFont>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>
RectObject::RectObject(QRectF r,QString t,QColor c,QPen p)
{
    _rect=r;
    _text.setFont(QFont("Helvetica",24));
    _text.setPos(r.x()+10,r.y()+10);
    _text.setPlainText(t);
    _text.setParentItem(this);
    _color=c;
    _pen=p;
    this->setAcceptHoverEvents(true);
}

void RectObject::paint ( QPainter * painter,
             const QStyleOptionGraphicsItem * option,
             QWidget * widget = 0 )
{
    painter->setBrush(QBrush(color()));
    painter->setPen(pen());
    painter->drawRect(boundingRect());
    painter->setPen(Qt::black);
}

QRectF RectObject::boundingRect() const
{
    return _rect;
}

void RectObject::setText(QString t)
{
    _text.setPlainText(t);
}

QColor RectObject::color()
{
    return _color;
}

QPen RectObject::pen()
{
    return _pen;
}

void RectObject::setPen(QPen p)
{
    _pen=p;
}

void RectObject::setColor(QColor c)
{
    _color=c;
}

void RectObject::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if(pressed)
    {
        QPointF d(event->scenePos()-press_point);
        _rect.moveTo(d.x(),d.y());
        _text.setPos(_rect.x()+10,_rect.y()+10);
        update();
    }

}

void RectObject::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    pressed=1;
    press_point=event->scenePos()-QPointF(_rect.x(),_rect.y());
}

void RectObject::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    pressed=0;
}

QRect RectObject::rect(){
    return QRect(_rect.x(),_rect.y(),_rect.width(),_rect.height());
}

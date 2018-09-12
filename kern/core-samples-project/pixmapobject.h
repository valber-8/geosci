#ifndef PIXMAPOBJECT_H
#define PIXMAPOBJECT_H

#include <QGraphicsItem>
#include <QPixmap>
#include <QPointF>

class PixmapObject : public QGraphicsItem
{
public:
    PixmapObject();
    PixmapObject(QPixmap,QPointF);
private:
    QPixmap _pix;
    QPointF _pos;
    virtual QRectF boundingRect() const;
    void paint ( QPainter *,
                 const QStyleOptionGraphicsItem *,
                 QWidget *);
};

#endif // PIXMAPOBJECT_H

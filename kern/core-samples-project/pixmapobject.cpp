#include "pixmapobject.h"
#include <QPainter>
PixmapObject::PixmapObject()
{
}

PixmapObject::PixmapObject(QPixmap pix,QPointF pos)
{
    _pix=pix;
    _pos=pos;
}

void PixmapObject::paint( QPainter * painter,
                        const QStyleOptionGraphicsItem * option,
                        QWidget * widget = 0 )
{
    painter->drawPixmap(_pos,_pix);
}

QRectF PixmapObject::boundingRect() const{
    return QRectF(_pos.x(),_pos.y(),_pix.width(),_pix.height());
}

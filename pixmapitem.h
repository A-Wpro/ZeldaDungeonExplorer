#ifndef PIXMAPITEM_H
#define PIXMAPITEM_H


#include <QtWidgets/QGraphicsObject>
#include <QGraphicsPixmapItem>

class Player;

class PixmapItem : public QGraphicsObject
{
public:
    PixmapItem(const QString &fileName, QGraphicsItem * parent = 0);
    PixmapItem(const QString &fileName, QGraphicsScene *scene);
    void changePix(const QString &fileName);
    QSizeF size() const;
    QRectF boundingRect() const override;
    void paint(QPainter *, const QStyleOptionGraphicsItem *, QWidget *) override;
    //bool collidesWithItem(const QGraphicsItem *other, Qt::ItemSelectionMode mode = Qt::IntersectsItemShape) const override;

private:
    QPixmap pix;
};

#endif // PIXMAPITEM_H

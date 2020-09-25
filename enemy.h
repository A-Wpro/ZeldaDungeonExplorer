#ifndef ENEMY_H
#define ENEMY_H

#include <QGraphicsPixmapItem>
#include <QSequentialAnimationGroup>
#include <QObject>
#include <QTimer>
#include "levelscene.h"


class enemy: public QObject,public QGraphicsPixmapItem{
    Q_OBJECT
public:
    enemy();
    int getlongueurE() const { return this->longueurE; } // définition au sein de la classe
    void setlongueurE(int longueurE);

    int getlargeurE() const { return this->largeurE; } // définition au sein de la classe
    void setlargeurE(int largeurE);

public slots:
    void detectCollision();
    void destroy();
    void remove();

signals:
    void killEnemy();

private:
    int largeurE ;
    int longueurE ;
    QSequentialAnimationGroup * destroyAnimation;
};

inline void enemy::setlongueurE(int longueurE) // définition au sein de la classe (inline)
{
    this->longueurE = longueurE;
}
inline void enemy::setlargeurE(int largeurE) // définition au sein de la classe (inline)
{
    this->largeurE = largeurE;
}
#endif // ENEMY_H

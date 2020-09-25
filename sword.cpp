#include "sword.h"
#include <QTimer>
#include <QList>
#include <QGraphicsScene>

#include <QDebug>

#include "sword.h"
#include "player.h"

#include "enemy.h"


sword::sword(): QObject(), QGraphicsPixmapItem(){

    setlargeurEpee(10);
    setlongeurEpee(50);

    // connect
    QTimer * timer = new QTimer();
    connect(timer,SIGNAL(timeout()),this ,SLOT(hit()));
    timer ->start(100); //tout les50 ms l'épee bouge
};

void sword::hit(){
    //si l'épée touche
    QList<QGraphicsItem *>  colliding_items = collidingItems();
    for (int i = 0, n=colliding_items.size(); i<n; ++i){
        if (typeid (*(colliding_items[i]))== typeid(QGraphicsPixmapItem))
        {//on detruit l'enemy
            scene()->removeItem(colliding_items[i]);
            delete colliding_items[i];
            delete this;
            qDebug() << "detruit";
            return;
        }
        else
        {
            delete this;
            qDebug() << "rate";
            return;
        }
    }
 }


#include "enemy.h"
#include "player.h"
#include <QTimer>
#include <QGraphicsScene>
#include <QList>
#include <QDebug>
#include <stdlib.h>
#include <QObject>
#include <QApplication>
#include <QDesktopWidget>
#include <QGraphicsPixmapItem>
#include <QSequentialAnimationGroup>
#include <QPropertyAnimation>
#include "sword.h"


static QSequentialAnimationGroup *setupDestroyAnimation(enemy *enemy)
{
    QSequentialAnimationGroup *group = new QSequentialAnimationGroup(enemy);
    for (int i = 1; i<= 8; i++)
    {
        PixmapItem *step = new PixmapItem(QString(":/Assets/explosion/step%1").arg(i), enemy);
        step->setScale(0.4);
        step->setZValue(6);
        step->setOpacity(0);
        step->setY( - 6);
        step->setX(-10);

        QPropertyAnimation *anim = new QPropertyAnimation(step, "opacity");
        anim->setEndValue(1);
        anim->setDuration(100);
        group->insertAnimation(i-1, anim);

        QPropertyAnimation *anim2 = new QPropertyAnimation(step, "opacity");
        anim2->setEndValue(0);
        anim2->setDuration(100);
        group->addAnimation(anim2);
    }
    //AnimationManager::self()->registerAnimation(group);
    return group;
}

enemy::enemy(): QObject(),QGraphicsPixmapItem(){

    setlargeurE(10);
    setlongueurE(10);

    const int width = 2160;
    const int height = 3840;
    //set Random nb
    int random_nbW = rand() % (width-100);
    int random_nbH = rand() % (height-100);
    setPos(random_nbH,random_nbW);

    QTimer * timer2 = new QTimer(this);
    connect(timer2, SIGNAL(timeout()), this, SLOT(detectCollision()));
    timer2->start(50);

    destroyAnimation = setupDestroyAnimation(this);

/**
    QObject::connect(this, SIGNAL(planeCollision()), this, SLOT(destroy()));

    QObject::connect(this, SIGNAL(planeDestroyed()), this, SLOT(destroy()));

    timerM = new QTimer;

    QObject::connect(timerM, SIGNAL(timeout()), this, SLOT(move()));
    timerM->start(50);
**/
}

void enemy::detectCollision()
{
    QList<QGraphicsItem *>  colliding_items = collidingItems();
    for (int i = 0, n=colliding_items.size(); i<n; ++i)
    {
        if (typeid(*(colliding_items[i])) == typeid(sword))
        {//on detruit 1pv et l'enemie
            //NbVie->perdreVie();
            delete colliding_items[i];
            emit killEnemy();
            //delete this;
            return;
        }
    }
}

void enemy::destroy()
{
    destroyAnimation->start();

    QTimer *timer = new QTimer;

    QObject::connect(timer, SIGNAL(timeout()), this, SLOT(remove()));
    timer->start(800);
}

void enemy::remove()
{
    //scene()->removeItem(this);

    delete this;
    //return;
}


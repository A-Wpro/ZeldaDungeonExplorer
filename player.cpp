#include "player.h"
#include "sword.h"
#include "enemy.h"

// le header
#include <QGraphicsScene>
#include <QtEvents>
#include <QApplication>
#include <QDesktopWidget>
#include <QPropertyAnimation>

#include <iostream>


static QSequentialAnimationGroup *setupTeleportationAnimation(Player *player)
{
    QSequentialAnimationGroup *group = new QSequentialAnimationGroup(player);
    for (int i = 1; i<= 10; i++)
    {
        PixmapItem *step = new PixmapItem(QString(":/Assets/teleportation/step%1").arg(i), player);
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


Player::Player() : PixmapItem(QString(":/Assets/walkR10.png"))
{
    setFlag(QGraphicsItem::ItemIsFocusable);
    setFocus();
    setZValue(8);
    setlargeur(10);
    setlongueur(10);
    setmovement(10);

    teleportationAnimation = setupTeleportationAnimation(this);

    //scene()->addItem(this);
};


void Player::keyPressEvent(QKeyEvent *event)
{
    QPixmap swordR = QPixmap(":/Assets/swordR.png");
    QPixmap swordL = QPixmap(":/Assets/swordL.png");
    QPixmap swordU = QPixmap(":/Assets/swordU.png");
    QPixmap swordD = QPixmap(":/Assets/swordD.png");


    if (event->key() == Qt::Key_Left){
        setFlag(QGraphicsItem::ItemIsFocusable);
        setFocus();
        //if (pos().x() > 0)
        emit goLeft();
        changePix(":/Assets/walkL1.png");
        //setPos(x() - getmovement(), y());
    }
    if (event->key() == Qt::Key_Right){
        setFlag(QGraphicsItem::ItemIsFocusable);
        setFocus();
        //if(pos().x() + getlongueur() < height)
        emit goRight();
        changePix(":/Assets/walkR1.png");
        //setPos(x() + getmovement(), y());
    }
    if (event->key() == Qt::Key_Up){
        setFlag(QGraphicsItem::ItemIsFocusable);
        setFocus();
        //if(pos().y() - getlargeur() > -width)
        emit goUp();
        changePix(":/Assets/walkU1.png");
        //setPos(x() , y()- getmovement());
    }
    if (event->key() == Qt::Key_Down){
        setFlag(QGraphicsItem::ItemIsFocusable);
        setFocus();
        //if(pos().y()<0)
        emit goDown();
        changePix(":/Assets/walkD1.png");
       // setPos(x(), y() + getmovement());
    }

    if (event->key() == Qt::Key_Z){
        //attack with sword
        sword * Psword = new sword();
   //     Psword->setRect(0,0,Psword->getlargeurEpee(),Psword->getlongeurEpee());
        Psword->setPos(x()+getlongueur()-Psword->getlargeurEpee(),y()-Psword->getlongeurEpee());//la pos de l'épée
        Psword->setPixmap(swordU);
        scene()->addItem(Psword);
    }
    else if (event->key() == Qt::Key_D){
        //attack with sword
        sword * Psword = new sword();
      //  Psword->setRect(0,0,Psword->getlongeurEpee(),Psword->getlargeurEpee());
          Psword->setPos(x()+getlongueur(),y()+getlargeur()-Psword->getlargeurEpee());//la pos de l'épée
          Psword->setPixmap(swordR);
          scene()->addItem(Psword);
    }
    else if (event->key() == Qt::Key_Q){
        //attack with sword
        sword * Psword = new sword();
   //     Psword->setRect(0,0,Psword->getlongeurEpee(),Psword->getlargeurEpee());
          Psword->setPos(x()-Psword->getlongeurEpee(),y());//la pos de l'épée
          Psword->setPixmap(swordL);
          scene()->addItem(Psword);
    }
    else if (event->key() == Qt::Key_S){
        //attack with sword
        sword * Psword = new sword();
     //   Psword->setRect(0,0,Psword->getlargeurEpee(),Psword->getlongeurEpee());
          Psword->setPos(x(),y()+getlargeur());//la pos de l'épée
          Psword->setPixmap(swordD);
          scene()->addItem(Psword);
    }
}

void Player::teleport()
{
    teleportationAnimation->start();

/**
    QTimer *timer = new QTimer;

    QObject::connect(timer, SIGNAL(timeout()), this, SLOT(remove()));
    timer->start(800);
    **/
}



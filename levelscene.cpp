#include "levelscene.h"
#include <QGraphicsScene>
#include <QBrush>
#include <QImage>
#include <QGraphicsItem>
#include <QPixmap>
#include <QGraphicsPixmapItem>
#include <QDebug>
#include <QPainter>
#include <iostream>
#include <sstream>
#include <QTimer>
#include <qmath.h>
#include <math.h>

#include "player.h"
#include "enemy.h"

LevelScene::LevelScene(QImage backgroundBrush, int level, int nOutputWidth, int nOutputHeight, vector<vector<int>> mapArr): QGraphicsScene()
{
    setSceneRect(0,0,3840,2168);
    setBackgroundBrush(QBrush(backgroundBrush));
    sceneWidth = nOutputWidth;
    sceneHeight = nOutputHeight;
    mapA = mapArr;
    currentLevel = level;
    initializeObstacles();


    QTimer * timer  = new QTimer();
    QObject::connect(timer,SIGNAL(timeout()), this,SLOT(spawn()));
    timer ->start(2000);

    QTimer *timer2 = new QTimer(this);
    connect(timer2,SIGNAL(timeout()),this,SLOT(move()));
    timer2->start(50);

}

void LevelScene::initializeObstacles()
{
    qDebug()<<"hey!";
    bool tOutSet = false;
    bool tBackSet = false;

    if (!tBackSet and !tOutSet)
    {
        for (int y=0; y<sceneHeight; ++y)
        {
            for(int x=0; x<sceneWidth; ++x)
            {
                if (mapA[x][y]!=0 and mapA[x][y]!=6)
                {
                    tBackSet =createTeleporterBack(x, y, 3500, tBackSet);
                    tOutSet = createTeleporterOut(x, y, 7000, tOutSet);
                }
            }
        }
    }
    if(!tBackSet)
    {
        for (int y=0; y<sceneHeight; ++y)
        {
            for(int x=0; x<sceneWidth; ++x)
            {
                if (mapA[x][y]!=0 and mapA[x][y]!=6)
                {
                    tBackSet =createTeleporterBack(x, y, 3500, tBackSet);
                }
            }
        }
    }
    if(!tOutSet)
    {
        for (int y=0; y<sceneHeight; ++y)
        {
            for(int x=0; x<sceneWidth; ++x)
            {
                if (mapA[x][y]!=0 and mapA[x][y]!=6)
                {
                    tOutSet = createTeleporterOut(x, y, 7000, tOutSet);
                }
            }
        }
    }

    QImage *rocher = new QImage;
    rocher->load(":/Assets/rocher.png");

    QImage *buisson = new QImage;
    buisson->load(":/Assets/buisson.png");

    QImage *mont = new QImage;
    mont->load(":/Assets/mont20.png");

    for (int y=0; y<sceneHeight; ++y)
    {
        for(int x=0; x<sceneWidth; ++x)
        {
            if(mapA[x][y]== 3)
            {
                QGraphicsPixmapItem *obstacle = new QGraphicsPixmapItem(QPixmap::fromImage(*rocher));
                obstacle->setPos(x*32, y*32);
                obstacle->setPixmap(QPixmap::fromImage(*rocher));
                this->addItem(obstacle);
            }
            else if(mapA[x][y]==4)
            {
                QGraphicsPixmapItem *obstacle = new QGraphicsPixmapItem(QPixmap::fromImage(*buisson));
                obstacle->setPos(x*32, y*32);
                addItem(obstacle);
            }
            else if (mapA[x][y]==6)
            {
                QGraphicsPixmapItem *obstacle = new QGraphicsPixmapItem(QPixmap::fromImage(*mont));
                obstacle->setPos(x*32, y*32);
                addItem(obstacle);
            }
            else if (mapA[x][y]==7)
            {
                std::string temp0;
                std::ostringstream temp1;

                temp1 <<"N :"<<currentLevel;
                temp0 = temp1.str();

                QImage *telBack = new QImage;
                telBack->load(":/Assets/teleporterBack.png");
                QPainter *p = new QPainter(telBack);
                QString strDisplay = QString::fromUtf8(temp0.c_str());
                p->setPen(QPen(Qt::white));
                p->setFont(QFont("Times", 10, QFont::Bold));
                p->drawText(telBack->rect(), Qt::AlignCenter, strDisplay);

                QGraphicsPixmapItem *teleporter = new QGraphicsPixmapItem(QPixmap::fromImage(*telBack));
                teleporter->setPos((x-1)*32, (y-1)*32);
                addItem(teleporter);

                player = new Player();

                player->setPos((x-1)*32, (y-1)*32);
                addItem(player);
                player->setFlag(QGraphicsItem::ItemIsFocusable);
                player->setFocus();

                QObject::connect(player, SIGNAL(goRight()), this, SLOT(goRight()));
                QObject::connect(player, SIGNAL(goDown()), this, SLOT(goDown()));
                QObject::connect(player, SIGNAL(goLeft()), this, SLOT(goLeft()));
                QObject::connect(player, SIGNAL(goUp()), this, SLOT(goUp()));
            }
            else if (mapA[x][y]==8)
            {
                std::string temp0;
                std::ostringstream temp1;

                temp1 <<"N :"<<(currentLevel + 1);
                temp0 = temp1.str();

                QImage *telOut = new QImage;
                telOut->load(":/Assets/teleporterOut.png");

                QPainter *p = new QPainter(telOut);
                QString strDisplay = QString::fromUtf8(temp0.c_str());
                p->setPen(QPen(Qt::white));
                p->setFont(QFont("Times", 10, QFont::Bold));
                p->drawText(telOut->rect(), Qt::AlignCenter, strDisplay);

                QGraphicsPixmapItem *teleporter = new QGraphicsPixmapItem(QPixmap::fromImage(*telOut));
                teleporter->setPos((x-1)*32, (y-1)*32);
                addItem(teleporter);
            }
        }
    }
}

void LevelScene::surroundingsEquals(int x, int y, int R)
{
    mapA[x][y]=R;

    mapA[x+1][y]=1;
    mapA[x+1][y-1]=1;
    mapA[x+1][y+1]=1;
    mapA[x][y-1]=1;

    mapA[x][y+1]=1;
    mapA[x-1][y]=1;
    mapA[x-1][y-1]=1;
    mapA[x-1][y+1]=1;
}


bool LevelScene::createTeleporterBack(int x, int y, int threshold, bool tSet)
{
    int i = x*y;
    if (!tSet and i>=threshold and x<(sceneWidth/2) and x>3 and y>3 and y<sceneWidth-3 and y<sceneHeight-3)
    {
        teleporterBack = QPoint(x, y);
        surroundingsEquals(x, y, 7);
        tSet = true;
    }
    else if(!tSet and x>3 and y>3 and x<sceneWidth-3 and x<sceneHeight-3)
    {
        if (rand()%1001==1000 and x<(sceneWidth/2))
        {
            teleporterBack = QPoint(x, y);
            surroundingsEquals(x, y, 7);
            tSet = true;
        }
    }
    return tSet;
}

bool LevelScene::createTeleporterOut(int x, int y, int threshold, bool tSet)
{
    int i=x*y;

    if (!tSet and i>=threshold and x>(sceneWidth/2) and x>3 and y>3 and x<sceneWidth-3 and y<sceneHeight-3)
    {
        teleporterOut = QPoint(x, y);
        surroundingsEquals(x, y, 8);
        tSet = true;
    }
    else if(!tSet)
    {
        if (rand()%1001==1000 and x>(sceneWidth/2) and x>3 and y>3 and x<sceneWidth-3 and y<sceneHeight-3)
        {
            teleporterOut = QPoint(x, y);
            surroundingsEquals(x, y, 8);
            tSet = true;
        }
    }
    return tSet;
}

void LevelScene::goUp()
{
    int x_center = player->pos().x() + player->size().width()/2;
    int y_center = player->pos().y() + player->size().height()/2 + 10;

    int x_tile = (int)x_center/32;
    int y_tile = (int)y_center/32;

    if (mapA[x_tile][y_tile-1]== 1 or mapA[x_tile][y_tile-1]== 7 or mapA[x_tile][y_tile-1]== 8)
    {
        player->setPos(player->pos().x(), player->pos().y()-player->getmovement());
        if (mapA[x_tile][y_tile-1]==8)
        {
            player->teleport();

            chargingTimer = new QTimer;
            chargingTimer->setSingleShot(true);
            connect(chargingTimer, SIGNAL(timeout()), this, SLOT(teleportUs()));
            chargingTimer->start(1600);
        }
    }
}

void LevelScene::teleportUs()
{
    //delete chargingTimer;
    if(!reached)
    {
        emit reachedOut();
    }
    reached = true;

}

void LevelScene::goDown()
{
    int x_center = player->pos().x() + player->size().width()/2;
    int y_center = player->pos().y() + player->size().height()/2 + 10;

    int x_tile = (int)x_center/32;
    int y_tile = (int)y_center/32;

    if (mapA[x_tile][y_tile+1]== 1 or mapA[x_tile][y_tile+1]== 7 or mapA[x_tile][y_tile+1]== 8)
    {
        player->setPos(player->pos().x(), player->pos().y()+player->getmovement());
        if (mapA[x_tile][y_tile+1]==8)
        {
            player->teleport();
            chargingTimer = new QTimer;
            chargingTimer->setSingleShot(true);
            connect(chargingTimer, SIGNAL(timeout()), this, SLOT(teleportUs()));
            chargingTimer->start(1600);

        }
    }
}

void LevelScene::goLeft()
{
    int x_center = player->pos().x() + player->size().width()/2+10;
    int y_center = player->pos().y() + player->size().height()/2 + 10;

    int x_tile = (int)x_center/32;
    int y_tile = (int)y_center/32;

    if (mapA[x_tile-1][y_tile]== 1 or mapA[x_tile-1][y_tile]== 7 or mapA[x_tile-1][y_tile]== 8)
    {
        player->setPos(player->pos().x()-player->getmovement(), player->pos().y());
        if (mapA[x_tile-1][y_tile]==8)
        {
            player->teleport();
            chargingTimer = new QTimer;
            chargingTimer->setSingleShot(true);
            connect(chargingTimer, SIGNAL(timeout()), this, SLOT(teleportUs()));
            chargingTimer->start(1600);
        }
    }
}

void LevelScene::goRight()
{
    int x_center = player->pos().x() + player->size().width()/2-20;
    int y_center = player->pos().y() + player->size().height()/2 + 10;

    int x_tile = (int)x_center/32;
    int y_tile = (int)y_center/32;

    if (mapA[x_tile+1][y_tile]== 1 or mapA[x_tile+1][y_tile]== 7 or mapA[x_tile+1][y_tile]== 8)
    {
        player->setPos(player->pos().x()+player->getmovement(), player->pos().y());
        if (mapA[x_tile+1][y_tile]==8)
        {
            player->teleport();
            chargingTimer = new QTimer;
            chargingTimer->setSingleShot(true);
            connect(chargingTimer, SIGNAL(timeout()), this, SLOT(teleportUs()));
            chargingTimer->start(1600);
        }
    }
}

void LevelScene::move()
{
    //set Random nb
    QPixmap pixL = QPixmap(":/Assets/cyclopeL1.png");
    QPixmap pixU = QPixmap(":/Assets/cyclopeUp.png");
    QPixmap pixR = QPixmap(":/Assets/cyclopeR1.png");
    QPixmap pixD = QPixmap(":/Assets/cyclopeDown.png");

    if(!enemies.empty())
    {
        for (int i = 0; i<enemies.size(); i++)
        {
            int dir = rand() % 8;
            int dis = rand() % 5;

            int X = enemies[i]->pos().x();
            int Y = enemies[i]->pos().y();

            int width = enemies[i]->getlongueurE();
            int height = enemies[i]->getlargeurE();

            if ( Y<=96)
            {
                enemies[i]->setPos(X, sceneHeight*32 - 128);
            }
            else if ( X<=96)
            {
                enemies[i]->setPos(sceneWidth*32 -64, Y);
            }

            switch(dir) {
              case 1:
                if(Y <= 64){
                    enemies[i]->setPos(X,Y+dis);
                    enemies[i]->setPixmap(pixL);
                }

                break;
              case 2:
                if(Y <= 64){
                    enemies[i]->setPos(X,Y+dis);
                    enemies[i]->setPixmap(pixL);
                }
                else if(Y - width > sceneWidth){
                    enemies[i]->setPos(X,Y-dis);
                    enemies[i]->setPixmap(pixL);
                }
                break;
              case 3:
                if(Y <= 64){
                    enemies[i]->setPos(X,Y+dis);
                    enemies[i]->setPixmap(pixL);
                }
                else if(Y<=64 && X + width< sceneHeight){
                  enemies[i]->setPos(X+dis,Y+dis);
                  enemies[i]->setPixmap(pixL);
                }
              break;
              case 4:
                if(Y <= 64){
                    enemies[i]->setPos(X,Y+dis);
                    enemies[i]->setPixmap(pixL);
                }
               else if(Y - width > sceneWidth && X + height <sceneHeight){
                   enemies[i]->setPos(X+dis,Y-dis);
                   enemies[i]->setPixmap(pixD);
               }
              break;
              case 5:
                if(Y <= 64){
                    enemies[i]->setPos(X,Y+dis);
                    enemies[i]->setPixmap(pixL);
                }
                else if(Y <=64 && X+width <sceneWidth){
                    enemies[i]->setPos(X-dis,Y+dis);
                    enemies[i]->setPixmap(pixD);
                }
              break;
              case 6:
                if(Y <= 64){
                    enemies[i]->setPos(X,Y+dis);
                    enemies[i]->setPixmap(pixL);
                }
                else if(Y  +height >= (sceneHeight-64) && X>=64){
                    enemies[i]->setPos(X-dis,Y-dis);
                    enemies[i]->setPixmap(pixD);
                }
              break;
              case 7:
                if(Y <= 64){
                    enemies[i]->setPos(X,Y+dis);
                    enemies[i]->setPixmap(pixL);
                }
                else if(X+ height < sceneHeight){
                    enemies[i]->setPos(X+dis,Y);
                    enemies[i]->setPixmap(pixD);
                }
              break;
              case 8:
                if(Y <= 64){
                    enemies[i]->setPos(X,Y+dis);
                    enemies[i]->setPixmap(pixL);
                }
                else if(X>0){
                    enemies[i]->setPos(X-dis,Y);
                    enemies[i]->setPixmap(pixU);
                }
              break;
              default:
                 enemies[i]->setPos(X,Y);
                 enemies[i]->setPixmap(pixU);
            }
        }
    }
}

void LevelScene::spawn(){
    enemy *mechant = new enemy();
    enemies.append(mechant);
    this->addItem(enemies.last());
    QObject::connect(enemies.last(), SIGNAL(killEnemy()), this, SLOT(killTarget()));
}

void LevelScene::killTarget(){
    for (int i = 0; i<enemies.size(); ++i)
    {
        if (sqrt(pow(enemies[i]->pos().x()-player->pos().x(), 2) + pow(enemies[i]->pos().y()-player->pos().y(), 2))<= 100 )
        {
            enemies[i]->destroy();

            int index = enemies.indexOf(enemies[i]);
            qDebug()<<index;
            //this->removeItem(enemies[index]);
            enemies.removeAt(index);

        }
    }
}


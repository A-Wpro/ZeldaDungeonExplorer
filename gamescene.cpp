#include "gamescene.h"
#include <QGraphicsScene>
#include <QBrush>
#include <QImage>
#include <QGraphicsItem>
#include <QPixmap>
#include <QGraphicsPixmapItem>
#include <QDebug>

GameScene::GameScene(QImage backgroundBrush, int nOutputWidth, int nOutputHeight, int **mapArr): QGraphicsScene()
{
    setSceneRect(0,0,3840,2168);
    setBackgroundBrush(QBrush(backgroundBrush));
    sceneWidth = nOutputWidth;
    sceneHeight = nOutputHeight;
    mapA = mapArr;
    initializeObstacles();
}

void GameScene::initializeObstacles()
{
    qDebug()<<"hey!";
    for (int y=0; y<sceneHeight; ++y)
    {
        for(int x=0; x<sceneWidth; ++x)
        {
                if(mapA[x][y]== 3)
                {
                    qDebug()<<"hey!";
                    qDebug()<<x;
                    qDebug()<<y;
                    QImage *rocher = new QImage;
                    rocher->load(":/Assets/rocher.png");
                    QGraphicsPixmapItem *obstacle = new QGraphicsPixmapItem(QPixmap::fromImage(*rocher));
                    obstacle->setPos(x*32, y*32);
                    obstacle->setPixmap(QPixmap::fromImage(*rocher));
                    this->addItem(obstacle);
                }
                else if(mapA[x][y]==4)
                {
                    QImage *buisson = new QImage;
                    buisson->load(":/Assets/buisson.png");
                    QGraphicsPixmapItem *obstacle = new QGraphicsPixmapItem(QPixmap::fromImage(*buisson));
                    obstacle->setPos(x*32, y*32);
                    addItem(obstacle);

                }
                else if (mapA[x][y]==5)
                {
                    QImage *three = new QImage;
                    three->load(":/Assets/three.png");
                    QGraphicsPixmapItem *obstacle = new QGraphicsPixmapItem(QPixmap::fromImage(*three));
                    obstacle->setPos(x*32, y*32);
                    addItem(obstacle);
                }
                else if (mapA[x][y]==6)
                {
                    QImage *mont = new QImage;
                    mont->load(":/Assets/mont20.png");
                    QGraphicsPixmapItem *obstacle = new QGraphicsPixmapItem(QPixmap::fromImage(*mont));
                    obstacle->setPos(x*32, y*32);
                    addItem(obstacle);
                }
            }
        }
}



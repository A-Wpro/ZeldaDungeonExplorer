#ifndef LEVELSCENE_H
#define LEVELSCENE_H
#include <QGraphicsScene>
#include <QObject>
#include <QWidget>
#include <iostream>
#include <vector>
#include <QList>

#include "player.h"
#include "pixmapitem.h"
#include "enemy.h"

using namespace std;

class enemy;

class LevelScene : public QGraphicsScene
{
    Q_OBJECT
public:
    LevelScene(QImage backgroundBrush, int level, int nOutputWidth, int nOutputHeight, vector<vector<int>> mapArr);
    void initializeObstacles();

    void surroundingsEquals(int x, int y, int R);
    bool createTeleporterBack(int x, int y, int R, bool tSet);
    bool createTeleporterOut(int x, int y, int R, bool tSet);


public slots:
    void spawn();
    void move();
    void killTarget();
    void teleportUs();

signals:
    void reachedOut();

public slots:
    void goUp();
    void goDown();
    void goLeft();
    void goRight();

private:
    bool reached=false;
    int currentLevel;
    int sceneWidth;
    int sceneHeight;
    vector<vector<int>> mapA;
    QPoint teleporterOut;
    QPoint teleporterBack;
    Player *player;
    QList<enemy*> enemies;
    QTimer *chargingTimer;
};

#endif // LEVELSCENE_H

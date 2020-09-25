#ifndef GAMESCENE_H
#define GAMESCENE_H
#include <QGraphicsScene>
#include <QImage>

class GameScene : public QGraphicsScene
{
public:
    GameScene(QImage backgroundBrush, int nOutputWidth, int nOutputHeight, int **mapArr);
    void initializeObstacles();

private:
    int sceneWidth;
    int sceneHeight;
    int **mapA;
};

#endif // GAMESCENE_H

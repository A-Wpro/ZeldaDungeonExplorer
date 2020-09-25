#ifndef DUNGEONGENERATOR_H
#define DUNGEONGENERATOR_H
#include <QImage>
#include <QDebug>
#include <QList>
#include <QObject>

#include <opencv4/opencv2/highgui/highgui.hpp>
#include <opencv4/opencv2/core/core.hpp>
#include <opencv4/opencv2/imgproc.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv4/opencv2/imgproc/imgproc.hpp>

#include <opencv4/opencv2/imgcodecs.hpp>

#include <iostream>
#include <sstream>

#include "gameview.h"
#include "levelscene.h"
#include "pixmapitem.h"

using namespace std;
using namespace cv;


class DungeonGenerator: public QObject
{
    Q_OBJECT
public:
    explicit DungeonGenerator(QObject* parent = 0);
    ~DungeonGenerator();
    void generatePerlinNoise(int nOutputWidth, int nOutputHeight, float *fNoiseSeed2D, int nOctaveCount, float fScalingBias, float *fPerlinNoise2D);
    QImage Mat2QImage(cv::Mat const& src);
    cv::Mat QImage2Mat(QImage const& src);

    int* generateDiffuseNoise(int R, int nWidth, int nHeight);
    void createTeleporter(int i, int nOutputWidth, LevelScene level);

    LevelScene* getCurrentScene() const { return levels.last(); }

public slots:
    void createLevel();

private:
    View *view;
    QList<LevelScene*> levels;
    int level;
    QPoint player;
};

#endif // DUNGEONGENERATOR_H

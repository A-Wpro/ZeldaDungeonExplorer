#include "dungeongenerator.h"
#include <ctime>
#include <cstdlib>

DungeonGenerator::DungeonGenerator(QObject* parent): QObject(parent)
{
    view = new View("Top left view");
    createLevel();
    level = 0;
}

DungeonGenerator::~DungeonGenerator(){}

void DungeonGenerator::createLevel()
{
    qDebug()<<"createLevel";

    cv::Mat carreauImg;
    cv::Mat carreau2Img;
    cv::Mat grassImg;
    cv::Mat waterImg;

    cv::Mat highGrass;
    cv::Mat montainImg;

    int nOutputWidth = 120;
    int nOutputHeight = 68;

    vector<vector<int>> mapArr(nOutputWidth, vector<int> (nOutputHeight,1));

    qDebug()<<nOutputWidth;
    qDebug()<<nOutputHeight;

    int nOctaveCount = 3;

    float fScalingBias = exp(-5.0f);

    float eN = 1;

    float *fNoiseSeed2D = new float[nOutputWidth * nOutputHeight];
    float *fPerlinNoise2D = new float[nOutputWidth * nOutputHeight];

    srand(time(NULL));
    for (int i = 0; i < nOutputWidth * nOutputHeight; i++) fNoiseSeed2D[i] = (float)rand()/ (float)RAND_MAX;

    generatePerlinNoise(nOutputWidth, nOutputHeight,fNoiseSeed2D, nOctaveCount, fScalingBias, fPerlinNoise2D);

    carreauImg = cv::imread("Assets/carreau.png");
    carreau2Img = cv::imread("Assets/carreau2.png");
    waterImg = cv::imread("Assets/watero.png");
    grassImg = cv::imread("Assets/grassTile.png");
    highGrass = cv::imread("Assets/grass.png");
    montainImg = cv::imread("Assets/mont.png");

    int sceneWidth = nOutputWidth*waterImg.rows;
    int sceneHeight = nOutputHeight*waterImg.cols;

    int *highGrassNoise = generateDiffuseNoise(10, nOutputWidth, nOutputHeight);
    int *buissonNoise = generateDiffuseNoise(29, nOutputWidth, nOutputHeight);
    int *carreauObstacles = generateDiffuseNoise(20, nOutputWidth, nOutputHeight);
    int *notPavedObstacles = generateDiffuseNoise(100, nOutputWidth, nOutputHeight);

    cv::Mat sceneImage = cv::Mat::zeros(sceneHeight, sceneWidth, CV_8UC3);

    for (int i = 0; i< (nOutputWidth * nOutputHeight); ++i)
    {
        int pixel_bw = (int)((pow(fPerlinNoise2D[i], eN))*6);

        int x_top_left = (i%nOutputWidth)*carreauImg.rows;
        int y_top_left = (i/nOutputWidth)*carreauImg.cols;

        if (pixel_bw==0)
        {
            cv::Rect region_of_interest = Rect(x_top_left, y_top_left, carreauImg.rows, carreauImg.cols);

            cv::Mat image_roi = sceneImage(region_of_interest);

            mapArr[i%nOutputWidth][(int)(i/nOutputWidth)]=0;

            waterImg.copyTo(image_roi);
        }
        else if (pixel_bw==1)
        {
            if (notPavedObstacles[i]==1)
            {
                mapArr[i%nOutputWidth][(int)(i/nOutputWidth)]=3;
            }
            else
            {
                mapArr[i%nOutputWidth][(int)(i/nOutputWidth)]=1;
            }
            cv::Rect region_of_interest = Rect(x_top_left, y_top_left, carreauImg.rows, carreauImg.cols);

            cv::Mat image_roi = sceneImage(region_of_interest);
            carreauImg.copyTo(image_roi);

        }
        else if (pixel_bw==2)
        {
            if (carreauObstacles[i]==1)
            {
                mapArr[i%nOutputWidth][(int)(i/nOutputWidth)]=3;
            }
            else
            {
                mapArr[i%nOutputWidth][(int)(i/nOutputWidth)]=1;
            }
            cv::Rect region_of_interest = Rect(x_top_left, y_top_left, carreauImg.rows, carreauImg.cols);
            cv::Mat image_roi = sceneImage(region_of_interest);
            carreau2Img.copyTo(image_roi);
        }
        else if (pixel_bw==3)
        {
            if (notPavedObstacles[i]==1)
            {
                mapArr[i%nOutputWidth][(int)(i/nOutputWidth)]=3;
            }
            else if(buissonNoise[i]==1)
            {
                mapArr[i%nOutputWidth][(int)(i/nOutputWidth)]=4;
            }
            else
            {
                mapArr[i%nOutputWidth][(int)(i/nOutputWidth)]=1;
            }
            cv::Rect region_of_interest = Rect(x_top_left, y_top_left, carreauImg.rows, carreauImg.cols);
            cv::Mat image_roi = sceneImage(region_of_interest);

            grassImg.copyTo(image_roi);

            if (highGrassNoise[i]==1)
            {
                cv::Rect region_of_interest = Rect(x_top_left, y_top_left, highGrass.rows, highGrass.cols);
                cv::Mat image_roi = sceneImage(region_of_interest);

                highGrass.copyTo(image_roi);
            }
        }
        else if (pixel_bw==4)
        {
            if (notPavedObstacles[i]==1)
            {
                mapArr[i%nOutputWidth][(int)(i/nOutputWidth)]=3;
            }
            else if(buissonNoise[i]==1)
            {
                mapArr[i%nOutputWidth][(int)(i/nOutputWidth)]=4;
            }
            else
            {
                mapArr[i%nOutputWidth][(int)(i/nOutputWidth)]=1;
            }
            cv::Rect region_of_interest = Rect(x_top_left, y_top_left, carreauImg.rows, carreauImg.cols);

            cv::Mat image_roi = sceneImage(region_of_interest);

            grassImg.copyTo(image_roi);

            if (highGrassNoise[i]==1)
            {
                cv::Rect region_of_interest = Rect(x_top_left, y_top_left, highGrass.rows, highGrass.cols);
                cv::Mat image_roi = sceneImage(region_of_interest);

                highGrass.copyTo(image_roi);
            }
        }
        else if (pixel_bw==5)
        {
            mapArr[i%nOutputWidth][(int)(i/nOutputWidth)]=6;

            cv::Rect region_of_interest = Rect(x_top_left, y_top_left, carreauImg.rows, carreauImg.cols);
            cv::Mat image_roi = sceneImage(region_of_interest);

            grassImg.copyTo(image_roi);
        }
        else if (pixel_bw==6)
        {
            mapArr[i%nOutputWidth][(int)(i/nOutputWidth)]=6;
        }
        else
        {
            mapArr[i%nOutputWidth][(int)(i/nOutputWidth)]=6;
            cv::Rect region_of_interest = Rect(x_top_left, y_top_left, carreauImg.rows, carreauImg.cols);
            cv::Mat image_roi = sceneImage(region_of_interest);

            grassImg.copyTo(image_roi);
        }
        if ((i%nOutputWidth==0) or (i%nOutputWidth==1) or (i%nOutputWidth==(nOutputWidth-2) or (i%nOutputWidth==(nOutputWidth-1) or (int)(i/nOutputWidth)==(nOutputHeight-1) or (int)(i/nOutputWidth)==(nOutputHeight-2) or (int)(i/nOutputWidth)==1) or (int)(i/nOutputWidth)==0))
        {
             mapArr[i%nOutputWidth][(int)(i/nOutputWidth)]=6;
        }
    }

    QImage *sceneBackground = new QImage;
    *sceneBackground = Mat2QImage(sceneImage);

    LevelScene *scene = new LevelScene(*sceneBackground, level, nOutputWidth, nOutputHeight, mapArr);

    level+=1;
    levels.append(scene);

    QObject::connect(levels.last(), SIGNAL(reachedOut()), this, SLOT(createLevel()));


    view->view()->setScene(levels.last());
    view->show();
}

void DungeonGenerator::generatePerlinNoise(int nOutputWidth, int nOutputHeight, float *fNoiseSeed2D, int nOctaveCount, float fScalingBias, float *fPerlinNoise2D)
{
    for (int x = 0; x < nOutputWidth; x++)
    {
        for (int y = 0; y < nOutputHeight; y++)
        {
            float fNoise = 0.0f;
            float fScaleAcc = 0.0f;
            float fScale = 1.0f;

            for (int o = 0; o < nOctaveCount; o++)
            {
                int nPitch = nOutputWidth >> o;

                int nSampleX1 = (x / nPitch) * nPitch;
                int nSampleY1 = (y / nPitch) * nPitch;

                int nSampleX2 = (nSampleX1 + nPitch) % nOutputWidth;
                int nSampleY2 = (nSampleY1 + nPitch) % nOutputWidth;

                float fBlendX = (float)(x - nSampleX1) / (float)nPitch;
                float fBlendY = (float)(y - nSampleY1) / (float)nPitch;

                float fSampleT = (1.0f - fBlendX) * fNoiseSeed2D[nSampleY1 * nOutputWidth + nSampleX1] + fBlendX * fNoiseSeed2D[nSampleY1 * nOutputWidth + nSampleX2];
                float fSampleB = (1.0f - fBlendX) * fNoiseSeed2D[nSampleY2 * nOutputWidth + nSampleX1] + fBlendX * fNoiseSeed2D[nSampleY2 * nOutputWidth + nSampleX2];

                fScaleAcc += fScale;
                fNoise += (fBlendY * (fSampleB - fSampleT) + fSampleT) * fScale;
                fScale = fScale / fScalingBias;
            }
            // Scale to seed range
            fPerlinNoise2D[y * nOutputWidth + x] = (fNoise / fScaleAcc);
        }
    }
    return;
}

QImage DungeonGenerator::Mat2QImage(cv::Mat const& src)
{
     cv::Mat temp; //make the same cv::Mat
     cv::cvtColor(src, temp, 4); //cvtColor Makes a copt, that what i need
     QImage dest((const uchar *) temp.data, temp.cols, temp.rows, temp.step, QImage::Format_RGB888);
     dest.bits(); // enforce deep copy, see documentation
     // of QImage::QImage ( const uchar * data, int width, int height, Format format )
     return dest;
}

cv::Mat DungeonGenerator::QImage2Mat(QImage const& src)
{
     cv::Mat result(src.height(),src.width(),CV_8UC3,(uchar*)src.bits(),src.bytesPerLine());
     //cv::Mat result; // deep copy just in case (my lack of knowledge with open cv)
     //cvtColor(tmp, result, 4);
     return result;
}

int* DungeonGenerator::generateDiffuseNoise(int R, int nWidth, int nHeight)
{
    int *vec = new int[nWidth*nHeight];
    srand(time(NULL));
    for(int i=0; i<(nWidth*nHeight); i++)
    {
        int r = (int)rand()%R;
        if (r==(R-1)){
            vec[i]=1;
        }
        else
        {
            vec[i]=0;
        }
    }
    return vec;
}


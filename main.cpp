#include "main.h"
#include <QApplication>
#include <QFontDatabase>
#include "gameview.h"
#include "gamescene.h"
#include "dungeongenerator.h"

GameScene *scene;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QFontDatabase::addApplicationFont(":/fonts/OCRAEXT.TTF");
    DungeonGenerator *dungeon = new DungeonGenerator();
    return a.exec();
}

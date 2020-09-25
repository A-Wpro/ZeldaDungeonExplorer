#ifndef PLAYER_H
#define PLAYER_H
#include "pixmapitem.h"
#include "levelscene.h"

#include <QObject>
#include <QSequentialAnimationGroup>

class Player: public PixmapItem
{
    Q_OBJECT
public:
    Player();
    void keyPressEvent(QKeyEvent * event);

    int getmovement() const { return this->movement; } // définition au sein de la classe
    void setmovement(int value);

    int getlongueur() const { return this->longueur; } // définition au sein de la classe
    void setlongueur(int longueur);

    int getlargeur() const { return this->largeur; } // définition au sein de la classe
    void setlargeur(int largeur);

public slots:
    void teleport();

signals:
    void goRight();
    void goLeft();
    void goUp();
    void goDown();
    void generateScene();

private:
    int movement ;
    int largeur ;
    int longueur ;
    QSequentialAnimationGroup * teleportationAnimation;
};

inline void Player::setmovement(int movement) // définition au sein de la classe (inline)
{
    this->movement = movement;
}
inline void Player::setlongueur(int longueur) // définition au sein de la classe (inline)
{
    this->longueur = longueur;
}
inline void Player::setlargeur(int largeur) // définition au sein de la classe (inline)
{
    this->largeur = largeur;
}

#endif // LINK_H

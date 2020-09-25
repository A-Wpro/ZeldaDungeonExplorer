

#ifndef SWORD_H
#define SWORD_H

#include <QGraphicsRectItem> // les objets de la scene
#include <QObject> //pour le slot
#include <QGraphicsPixmapItem>

class sword: public QObject, public QGraphicsPixmapItem{
    Q_OBJECT //macro
public:
    sword();

    int getlongeurEpee() const { return this->longeurEpee; } // définition au sein de la classe
    void setlongeurEpee(int longeurEpee);

    int getlargeurEpee() const { return this->largeurEpee; } // définition au sein de la classe
    void setlargeurEpee(int largeurEpee);

public slots:
    void hit();

private:
    int longeurEpee ;
    int largeurEpee ;


};
inline void sword::setlargeurEpee(int largeurEpee) // définition au sein de la classe (inline)
{
    this->largeurEpee = largeurEpee;
}
inline void sword::setlongeurEpee(int longeurEpee) // définition au sein de la classe (inline)
{
    this->longeurEpee = longeurEpee;
}



#endif // SWORD_H

#ifndef PACMANGAME_H
#define PACMANGAME_H

#include <vector>

#include <QSize>
#include <QGraphicsScene>
#include <QTimer>
#include <QPainter>

#include "wall.h"
#include "pacman.h"
#include "ghost.h"
#include "score.h"
#include "health.h"


#include <list>
#include <map>
//#include <QMediaPlayer>
#include "dot.h"

//#include <QGraphicsItemGroup>


class PacmanGame:  public QObject, public QGraphicsRectItem{
    Q_OBJECT
private:
    Pacman *pacman;
    Ghost *ghost;
    std::list<Ghost*> ghosts{};
//obrisala current_score, nalazi se u pacman klasi
    //Wall *walls[200];             // <- ne treba odavno, imamo walls_and_borders listu
    std::list<Wall*> walls_and_borders{};
    std::map<std::pair<int,int>,Dot*> dots{};

    // dodao da bi mozda napravili konstruktor za PacmanGame kome se prosledjuje
    // integer koji oznacava mapu

    //std::set<QGraphicsItem*> allDots{};           // cuvamo kao skupove ovog tipa jer mozemo da dobijemo
    //std::set<QGraphicsRectItem*> allGhosts{};     // pokazivace na objekte u trenutku kad ih ubacujemo na scenu
/*
    QMediaPlayer * beginning;
    QMediaPlayer * chomp;
    QMediaPlayer * eatfruit;
    QMediaPlayer * eatghost;
    QMediaPlayer * death;
*/
    //  tabela skorova !!!
    //  bolje tipa vektor sa 10 mesta, da otmemo odmah 10 slotova
    //  za skorove, da ne alociramo memoriju ako je slucajno nema


    int x;
    int y;
    int width = 0;
public:
    PacmanGame(int selectMap);
    Score *score;
    Health *health;
    int pacPosX;
    int pacPosY;
    int mapSelector;
    int flag =0;
    virtual ~PacmanGame();
    Pacman* getPacman();
    Wall* getWall();
    int getWidth();
    int getHeight();
    void populateScene(QGraphicsScene &scene);
    void setMapSelector(int x);
    int getX() const;
    int getY() const;
};

#endif // PACMANGAME_H

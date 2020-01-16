#ifndef GAME_H
#define GAME_H

#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QObject>
#include <QScreen>
#include "pacmangame.h"
#include "button.h"

#include <QDebug>
#include "wall.h"
#include <QGraphicsPixmapItem>


class Game: public QGraphicsView
{
       Q_OBJECT
public:
    int mapSelector;
    PacmanGame *game1;
    QGraphicsScene *scene;
    Game(QWidget *parent = NULL);
    void displayMainManu();
    void gameOver(QString message);
    void again();

public slots:
    void start();
    void resetGame();
};

#endif // GAME_H

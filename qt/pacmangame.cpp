#include "pacmangame.h"
//#include "globalVariables.h"

#include <iostream>
#include <QDesktopWidget>
#include <QApplication>

#include <QGraphicsItem>
#include <fstream>
#include <QFile>
#include <stdio.h>
#include <QTextStream>
#include <QChar>
#include <list>
#include <numeric>
#include <QString>
#include "dot.h"
#include <QStyleOption>

PacmanGame::PacmanGame()
{

/*
    // ingame sounds
    beginning = new QMediaPlayer{};
    beginning->setMedia(QUrl("qrc:/Sounds/pacman_beginning.wav"));

    chomp = new QMediaPlayer{};
    chomp->setMedia(QUrl("qrc:/Sounds/pacman_chomp.wav"));

    eatfruit = new QMediaPlayer{};
    eatfruit->setMedia(QUrl("qrc:/Sounds/pacman_eatfruit.wav"));

    eatghost = new QMediaPlayer{};
    eatghost->setMedia(QUrl("qrc:/Sounds/pacman_eatghost.wav"));

    death = new QMediaPlayer{};
    death->setMedia(QUrl("qrc:/Sounds/pacman_death.wav"));
*/

    std::string mapCe = ":/new/PacFiles/mapa";
    int mapSelector = 1;                // napravicemo vec neko biranje
    mapCe += std::to_string(mapSelector) + ".txt";
    QString gameMap = QString::fromStdString(mapCe);
    QFile mapa{gameMap};
    mapa.open(QFile::ReadOnly | QFile::Text);
    QTextStream inMap{&mapa};

    char c;


    int x = 0, y = 0, broj_duha = 0;

    int direction;                      // ideja da u fajlu mapa imamo vec odredjen smer pekmena da bismo mogli
                                        // da usmerimo animaciju, taj broj da stoji pre svega ostalog
    inMap >> direction;
    QChar nula('0');                // 0 => bobica
    QChar kec('1');                 // 1 => zid
    QChar taraba('#');              // # => duh
    QChar pacPosition('P');         // P => pocetna pozicija
    QChar bigDot('B');              // B => velika bobica
    QChar fruit('V');              // V => vockica
    QChar emptySpace('=');          // '=' => prazan prostor
    QChar noviRed('\n');

    int width = 0;

    int spacing = 35;
    Wall *w1;
    Dot *tuf{};

    inMap >> c;                         // kupi novi red posle ucitanog smera

    while(!inMap.atEnd()){
        width++;
        inMap >> c;
        if( (c == nula || c == bigDot) || c==fruit){
            // stavi bobicu, stavimo koliziju pekmena sa
            // bobicom da unisti bobicu i podesi skor
            tuf = new Dot(x,y, c);
            std::pair<int, int> par = {x,y};
            dots[par] = tuf;
            x+=spacing;
        }
        else if(c == kec){
            w1 = new Wall(x,y,spacing,spacing);
            this->walls_and_borders.push_back(w1);
            x+=spacing;
            //i++; // counts walls
        }
        else if(c == noviRed){
            width--;
            std::cout << width << "\n";
            x = 0;
            y+=spacing;
        }
        else if (c == taraba){
            ++broj_duha;
            this->ghost = new Ghost(x+2,y+2, broj_duha);
            this->ghosts.push_back(ghost);
            x+=spacing;
        }
        else if(c == pacPosition){
            //this->pacman->setCurrentDirection(direction);
            this->pacman = new Pacman(x+2,y+2);
            x+=spacing;
        }
        else if(c == emptySpace){
            x+=spacing;
        }
    }

}

PacmanGame::~PacmanGame()
{

}

Pacman* PacmanGame::getPacman(){
    return this->pacman;
}


int PacmanGame::getWidth(){
    QRect rec = QApplication::desktop()->screenGeometry();
    return rec.width();
}


int PacmanGame::getHeight(){
    QRect rec = QApplication::desktop()->screenGeometry();
    return rec.height();
}


//Wall* PacmanGame::getWall(){

//}

bool add_to_scene(QGraphicsScene &scene, Wall* zid){
    scene.addItem(zid);
    return true;
}

void PacmanGame::populateScene(QGraphicsScene &scene){
   // getWall();
    //QGraphicsItemGroup *group = new QGraphicsItemGroup{};


    for(auto x : this->walls_and_borders){
        scene.addItem(x);
        x->setBrush(Qt::darkGray);
    }

    for(auto x : this->ghosts){
        scene.addItem(x);
    }

    //Global prom{};
    for(auto x: this->dots){
        //global::allDots.insert(scene.addEllipse(x.second->getDot()));
        //prom.addDot(scene.addEllipse(x.second->getDot()));
        scene.addEllipse(x.second->getDot());
    }


    scene.addItem(this->pacman);
    /*
    scene = std::accumulate(std::begin(this->walls_and_borders), std::end(this->walls_and_borders),
                    QGraphicsScene, add_to_scene);
    */

}

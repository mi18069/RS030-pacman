#include "game.h"
#include <QDebug>
#include <iterator>


#include "wall.h"
#include "pacman.h"
#include "ghost.h"
#include "score.h"
#include "health.h"


#include <list>
#include <map>
//#include <QMediaPlayer>
#include "dot.h"
#include <QPixmap>
#include <vector>
#include <algorithm>

extern int level_map;

Game::Game(QWidget *parent)
{
    QSize size = qApp->screens()[0]->size();

    this->setFixedSize(size.width(), size.height());
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);


    scene = new QGraphicsScene();
    scene->setSceneRect(0, 0, size.width(), size.height());
    //  Creating an item to place in the scene
    setScene(scene);


}


void Game::displayMainManu()
{
    //QPixmap m(":/Images/pacmanManu.jpg");
    //scene->addPixmap(m);
    //this->setPixmap(QPixmap(":/Images/pacmanManu.jpg"));
   // scene->setBackgroundBrush(m.scaled(100,100,Qt::IgnoreAspectRatio,Qt::SmoothTransformation));
    //scene->setBackgroundBrush(QBrush);
    //this->setScene(scene);

    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::black);
    //setBrush(brush);
    scene->setBackgroundBrush(brush);

    //QPixmap m(":/Images/pacmanManu.jpg");

    QGraphicsTextItem *text =  new QGraphicsTextItem(QString("P A C M A N"));
    //text->setScale(100);
    text->setDefaultTextColor(Qt::white);
    int txPos = this->width()/2- text->boundingRect().width()/2;
    int tyPos = 150;
    text->setPos(txPos,tyPos);
    scene->addItem(text);


    //level_map = 0;


    Button *playButton = new Button(QString("Play"));
    int bxPos = this->width()/2- playButton->boundingRect().width()/2;
    int byPos = 275;
    playButton->setPos(bxPos,byPos);
    QObject::connect(playButton, SIGNAL(clicked()),this, SLOT(start()) );
    this->scene->addItem(playButton);

    Button *scoreButton = new Button(QString("Score"));
    bxPos = this->width()/2- scoreButton->boundingRect().width()/2;
    byPos = 350;
    scoreButton->setPos(bxPos,byPos);
    QObject::connect(scoreButton, SIGNAL(clicked()),this, SLOT(score()) );
    this->scene->addItem(scoreButton);


    Button *quitButton = new Button(QString("Quit"));
    bxPos = this->width()/2- quitButton->boundingRect().width()/2;
    byPos = 425;
    quitButton->setPos(bxPos,byPos);
    QObject::connect(quitButton, SIGNAL(clicked()),this, SLOT(close()) );
    this->scene->addItem(quitButton);

}
/*
int indeks(int rezultat, std::list<std::pair<std::string, int> > & l){


    std::list<std::pair<std::string, int> >::iterator it;
    for (int i =0 ,it=l.begin(); it!=l.end(); it++, i++){
        if (rezultat >= (*it)->second){
            // vector vec sortiran opadajuce
            return i;
        }

    }
    return -1;

}
*/

void Game::gameOver(QString message)
{
    for (size_t i=0, n = scene->items().size(); i<n; i++){
        scene->items()[i]->setEnabled(false);
    }

    qDebug() << "usli smo u funkciju gameOver()";
  //  scene->clear();
    qDebug() << "ocistili smo ekran";


/*


    int i = indeks(this->game1->score->getScore(), listOfScores);
    if( i >= 0){
        // nas score idde u listu
        // da omogucimo korisniku da unese svoje ime

        std::pair<std::string, int> tmp("bla", this->game1->score->getScore());

        //std::vector<std::pair<std::string, int> > tmp;
        //std::copy(listOfScores.begin(), listOfScores.end(), tmp.begin());
        listOfScores.insert(i,tmp);

        // treba da azuriramo nas text fajl
        QFile inputFile(":/new/PacFiles/score.txt");
        if (inputFile.open(QIODevice::ReadWrite)){
                       std::list<std::pair<std::string, int> >::iterator it;
                       for (int i=1, it=listOfScores.begin(); it!=listOfScores.end(); it++, i++){
                        QString player = QString(QString(i)+ ". " + QString(*it->first)+ " " + QString(*it->second));
                                QTextStream stream(&inputFile);
                                stream << player << endl;
                       }
         }
    }// end of if(i>=0)

*/
/*
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::black);
    //setBrush(brush);
    scene->setBackgroundBrush(brush);
*/

    QGraphicsTextItem *text1 =  new QGraphicsTextItem(message);
    QFont font;
    font.setPixelSize(60);
    text1->setFont(font);
    //text1->setDefaultTextColor(Qt::white);
    int txPos1 = this->width()/2- text1->boundingRect().width()/2;
    int tyPos1 = 100;
    text1->setPos(txPos1,tyPos1);
    scene->addItem(text1);

    Button *scoreButton = new Button(QString("Score"));
    int bxPos = this->width()/2- scoreButton->boundingRect().width()/2;
    int byPos = 200;
    scoreButton->setPos(bxPos,byPos);
    QObject::connect(scoreButton, SIGNAL(clicked()),this, SLOT(score()) );
    this->scene->addItem(scoreButton);

    Button *mainButton = new Button(QString("Main Menu"));
    bxPos = this->width()/2- mainButton->boundingRect().width()/2;
    byPos = 350;
    mainButton->setPos(bxPos,byPos);
    QObject::connect(mainButton, SIGNAL(clicked()),this, SLOT(resetGame()) );
    this->scene->addItem(mainButton);



    Button *quitButton = new Button(QString("Quit"));
    bxPos = this->width()/2- quitButton->boundingRect().width()/2;
    byPos = 500;
    quitButton->setPos(bxPos,byPos);
    QObject::connect(quitButton, SIGNAL(clicked()),this, SLOT(close()) );
    this->scene->addItem(quitButton);




}

void Game::score(){
    scene->clear();

    QGraphicsTextItem *text =  new QGraphicsTextItem(QString("S C O R E"));
    int txPos = this->width()/2- text->boundingRect().width()/2;
    int tyPos = 150;
    text->setPos(txPos,tyPos);
    scene->addItem(text);

    QFile inputFile(":/new/PacFiles/score.txt");
    if (inputFile.open(QIODevice::ReadOnly))
    {
       int i = 0;
       QTextStream in(&inputFile);
       while (!in.atEnd())
       {
          QString tekst = in.readLine();

              text =  new QGraphicsTextItem(QString(tekst));
              txPos = this->width()/2- text->boundingRect().width()/2;
              tyPos = 200+i*20;
              text->setPos(txPos,tyPos);
              scene->addItem(text);
              i++;
       }
       inputFile.close();
    }







    Button *mainButton = new Button(QString("Main Menu"));
    int bxPos = this->width()/2- mainButton->boundingRect().width()/2;
    int byPos = 450;
    mainButton->setPos(bxPos,byPos);
    QObject::connect(mainButton, SIGNAL(clicked()),this, SLOT(resetGame()) );
    this->scene->addItem(mainButton);



    Button *quitButton = new Button(QString("Quit"));
    bxPos = this->width()/2- quitButton->boundingRect().width()/2;
    byPos = 525;
    quitButton->setPos(bxPos,byPos);
    QObject::connect(quitButton, SIGNAL(clicked()),this, SLOT(close()) );
    this->scene->addItem(quitButton);

    scene->update();
}



void Game::again(){
    for (size_t i=0, n = scene->items().size(); i<n; i++){
        scene->items()[i]->setEnabled(false);
    }

    qDebug() << "usli smo u funkciju again()";
    //scene->clear();




    Button *resetButton = new Button(QString("NEXT LEVEL"));
    int bxPos = this->width()/2- resetButton->boundingRect().width()/2;
    int byPos = 125;
    resetButton->setPos(bxPos,byPos);
    QObject::connect(resetButton, SIGNAL(clicked()),this, SLOT(start()) );
    this->scene->addItem(resetButton);


    Button *mainButton = new Button(QString("Main Menu"));
    bxPos = this->width()/2- mainButton->boundingRect().width()/2;
    byPos = 200;
    mainButton->setPos(bxPos,byPos);
    QObject::connect(mainButton, SIGNAL(clicked()),this, SLOT(resetGame()) );
    this->scene->addItem(mainButton);


    Button *quitButton = new Button(QString("Quit"));
    bxPos = this->width()/2- quitButton->boundingRect().width()/2;
    byPos = 275;
    quitButton->setPos(bxPos,byPos);
    QObject::connect(quitButton, SIGNAL(clicked()),this, SLOT(close()) );
    this->scene->addItem(quitButton);
}







void Game::start()
{
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::white);
    //setBrush(brush);
    scene->setBackgroundBrush(brush);

   // qDebug() << "poziva se reset";
    for (size_t i=0, n = scene->items().size(); i<n; i++){
        scene->items()[i]->setEnabled(false);
    }
    qDebug() << "uslo u funkciju start()";

    this->scene->clear();

    //int level_map =1;
    game1 = new PacmanGame(level_map);


    game1->getPacman()->setFlag(QGraphicsItem::ItemIsFocusable);
    game1->getPacman()->setFocus();
    game1->populateScene(*this->scene);


    //  Adding a view so that we can see something

    this->scene->addItem(game1);
    qDebug() << "level je "<< level_map <<"\n";
    //scene->addItem(game1->getPacman());

}

void Game::resetGame()
{
    qDebug() << "poziva se reset";
    for (size_t i=0, n = scene->items().size(); i<n; i++){
        scene->items()[i]->setEnabled(false);
    }
    level_map =1;
    scene->clear();
    this->displayMainManu();
    //start();
}

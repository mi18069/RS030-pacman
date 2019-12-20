#include "pacman.h"

Pacman::Pacman()
{
    // ideja da li da imamo unique_ptr koji pokazuje na Pacman???
    //setRect(0, 0, 30, 30);
    setRect(37, 37, 30, 30);

    QTimer *timer = new QTimer(this);

    connect(timer, SIGNAL(timeout()), this, SLOT(move()));

    timer->start(25);
}

void Pacman::keyPressEvent(QKeyEvent *event)
{
    //treba u meni-ju korisnik da izabere da li ce da se krece na strelicu ili na jkli.. za sada ovako

    // **Micovic je mislio na hjkl, slova koja se koriste za pomeranje pozicije u vim-u

    //kolizija sa Ghost-om

    if (event->key() == Qt::Key_Left)
    {
        this->nextDirection = 1;
    }
    else if (event->key() == Qt::Key_Right)
    {
        this->nextDirection = 2;
    }
    else if (event->key() == Qt::Key_Up)
    {
        this->nextDirection = 3;
    }
    else if (event->key() == Qt::Key_Down)
    {
        this->nextDirection = 4;
    }
    else if (event->key() == Qt::Key_H)
    { // left
        this->nextDirection = 1;
    }
    else if (event->key() == Qt::Key_L)
    { //right
        this->nextDirection = 2;
    }
    else if (event->key() == Qt::Key_K)
    { // up
        this->nextDirection = 3;
    }
    else if (event->key() == Qt::Key_J)
    { //down
        this->nextDirection = 4;
    }
    else if (event->key() == Qt::Key_Escape)
    {
        qDebug() << "IZLAAAZ";
        QCoreApplication::quit();
    }
}

void Pacman::move()
{
    if (this->nextDirection != 0)
    {
        if (this->nextDirection == 1)
            setPos(x() - 5, y());
        else if (this->nextDirection == 2)
            setPos(x() + 5, y());
        else if (this->nextDirection == 3)
            setPos(x(), y() - 5);
        else if (this->nextDirection == 4)
            setPos(x(), y() + 5);

        // pokusas sa next
        // ako ima kolizije korak unazad
        // i nastavis sa current
        // ako nema kolizije super stavis da current bude next a next da bude nula

        // vraca listu objkekata sa kojim je u koliziji
        // ako lista nije prazna onda korak unazad
        QList<QGraphicsItem *> colliding_items = collidingItems();
        int n = colliding_items.size();
        if (n != 0)
        {
            if (this->nextDirection == 1)
                setPos(x() + 5, y());
            else if (this->nextDirection == 2)
                setPos(x() - 5, y());
            else if (this->nextDirection == 3)
                setPos(x(), y() + 5);
            else if (this->nextDirection == 4)
                setPos(x(), y() - 5);

            if (this->currentDirection == 1)
                setPos(x() - 5, y());
            else if (this->currentDirection == 2)
                setPos(x() + 5, y());
            else if (this->currentDirection == 3)
                setPos(x(), y() - 5);
            else if (this->currentDirection == 4)
                setPos(x(), y() + 5);
            colliding_items = collidingItems();
            int n = colliding_items.size();
            if (n != 0)
            {
                // ako ima kolizije unazad
                if (this->currentDirection == 1)
                    setPos(x() + 5, y());
                else if (this->currentDirection == 2)
                    setPos(x() - 5, y());
                else if (this->currentDirection == 3)
                    setPos(x(), y() + 5);
                else if (this->currentDirection == 4)
                    setPos(x(), y() - 5);
            }
        }
        else
        {
            //ako je sve uredu staviti trenutnu poziciju na sledecu
            this->currentDirection = this->nextDirection;
            this->nextDirection = 0;
        }
    }
    else
    { // ako next ne postoji samo radi normalno
        if (this->currentDirection == 1)
            setPos(x() - 5, y());
        else if (this->currentDirection == 2)
            setPos(x() + 5, y());
        else if (this->currentDirection == 3)
            setPos(x(), y() - 5);
        else if (this->currentDirection == 4)
            setPos(x(), y() + 5);
        QList<QGraphicsItem *> colliding_items = collidingItems();
        int n = colliding_items.size();
        if (n != 0)
        {
            // ako ima kolizije unazad
            if (this->currentDirection == 1)
                setPos(x() + 5, y());
            else if (this->currentDirection == 2)
                setPos(x() - 5, y());
            else if (this->currentDirection == 3)
                setPos(x(), y() + 5);
            else if (this->currentDirection == 4)
                setPos(x(), y() - 5);
        }
    }

    if (x() < 0)
        setPos(0, y());
    if (y() < 0)
        setPos(x(), 0);
    if (x() > this->scene()->width() - this->boundingRect().size().rwidth())
        setPos(this->scene()->width() - this->boundingRect().size().rwidth(), y());
    if (y() > this->scene()->height() - this->boundingRect().size().rheight())
        setPos(x(), this->scene()->height() - this->boundingRect().size().rheight());
}

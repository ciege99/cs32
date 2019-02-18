#include "Actor.h"
#include "StudentWorld.h"
#include "GameConstants.h"
#include "GraphObject.h"

// Students:  Add code to this file, Actor.h, StudentWorld.h, and StudentWorld.cpp

//constructors

BaseActor::BaseActor(int imageID, double startX,
                    double startY, Direction dir, int depth, StudentWorld *world) :
                    GraphObject(imageID, startX, startY, dir, depth), m_alive(true), m_world(world)
                    {}

MoveableActors::MoveableActors(int imageID, double startX,
                               double startY, Direction dir, int depth, StudentWorld* world) :
                                BaseActor (imageID, startX, startY, dir, depth, world)
                                {}

Humans::Humans(int imageID, double startX, double startY,
               Direction dir, int depth, StudentWorld* world) : MoveableActors(imageID, startX, startY, dir, depth, world), m_isInfected(false), m_infectedTotal(0)
                    {}


Penelope::Penelope(double startX, double startY, StudentWorld* world) : Humans(IID_PLAYER, startX, startY, 0, 0, world), m_landmines(0), m_vaccines(0), m_gasCans(0)
    {}


Environment::Environment(int imageID, double startX, double startY,
                         Direction dir, int depth, StudentWorld* world) :
                        BaseActor(imageID, startX, startY, dir, depth, world)
                        {}

Permanents::Permanents(int imageID, double startX, double startY, Direction dir,
                       int depth, StudentWorld* world) :
                        Environment(imageID, startX, startY, dir, depth, world)
                        {}

Walls::Walls(double startX, double startY, StudentWorld* world) :
            Permanents(IID_WALL, startX, startY, 0, 0, world)
            {}



// doSomething

void Humans::doSomething() {
    if (! this->isAlive() ) //check that human is alive
        return;
    
    if (this->isInfected())
    {
        m_infectedTotal++;
        if (m_infectedTotal >= 500)
        {
            this->beKilled();   //from BaseActor class
            this->getWorld()->playSound(SOUND_PLAYER_DIE);
            return;
        }
    }
    
    if ( this->isPlayer() )
    {
        int ch;
        if (this->getWorld()->getKey(ch))
        {
            double oldX = this->getX();
            double oldY = this->getY();
            switch (ch) {
                case KEY_PRESS_LEFT:
                    setDirection(left);
                    if (! this->getWorld()->overlap(oldX-4, oldY, this))
                        break;
                    this->moveTo(oldX-4, oldY);
                    break;
                case KEY_PRESS_RIGHT:
                    setDirection(right);
                    if (! this->getWorld()->overlap(oldX+4, oldY, this))
                        break;
                    this->moveTo(oldX+4, oldY);
                    break;
                case KEY_PRESS_UP:
                    setDirection(up);
                    if (! this->getWorld()->overlap(oldX, oldY+4, this))
                        break;
                    this->moveTo(oldX, oldY+4);
                    break;
                case KEY_PRESS_DOWN:
                    setDirection(down);
                    if (! this->getWorld()->overlap(oldX, oldY-4, this))
                        break;
                    this->moveTo(oldX, oldY-4);
                    
                    //still need to add in parts for actions
            }
        }
        // all the stuff Penelope does during her turn
    }
}


// BaseActor functions
bool BaseActor::isAlive() {
    return m_alive;
}

void BaseActor::beKilled() {
    m_alive = false;
}

bool BaseActor::canOverlap() {
    return true;
}

StudentWorld* BaseActor::getWorld() {
    return m_world;
}


// Humans functions

bool Humans::isInfected() {
    return m_isInfected;
}

int Humans::getInfectedTotal() {
    return m_infectedTotal;
}

void Humans::onCollision(BaseActor *a) {
    return; //humans don't do anything on collision
}

// Penelope functions

bool Penelope::isPlayer() {
    return true;
}



// Permanents functions

void Permanents::doSomething() {
    return;     //most permanents do nothing, so this is good default
}


// Walls functions

void Walls::onCollision(BaseActor *a) {
    return;
}

bool Walls::canOverlap() {
    return false;
}



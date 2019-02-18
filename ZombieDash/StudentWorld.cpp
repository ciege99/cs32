#include "StudentWorld.h"
#include "GameConstants.h"
#include "Level.h"
#include <string>
#include <list>
using namespace std;

GameWorld* createStudentWorld(string assetPath)
{
	return new StudentWorld(assetPath);
}

// Students:  Add code to this file, StudentWorld.h, Actor.h and Actor.cpp

StudentWorld::StudentWorld(string assetPath)
: GameWorld(assetPath), character(nullptr)
{}

StudentWorld::~StudentWorld() {
    this->cleanUp();
}


int StudentWorld::init()
{
    string levelFile = "level01.txt";
    Level lev(assetPath());
    lev.loadLevel(levelFile);
    for (double i = 0; i < 16; i++)
        for (double j = 0; j < 16; j++)
        {
            Level::MazeEntry ge;
            ge = lev.getContentsOf(i, j);
            switch (ge)
            {
                case Level::empty:
                    break;
                case Level::player:
                    character = new Penelope(i*16, j*16, this);
                    break;
                case Level::wall:
                    actors.push_back(new Walls(i*16, j*16, this));
                    break;
                default:
                    break;
            }
        }

    
    //character = new Penelope(200, 200, this);
    //actors.push_back(new Walls(0, 0, this));
    return GWSTATUS_CONTINUE_GAME;
}

int StudentWorld::move()
{
    // This code is here merely to allow the game to build, run, and terminate after you hit enter.
    // Notice that the return value GWSTATUS_PLAYER_DIED will cause our framework to end the current level.
    character->doSomething();
    list<BaseActor*>::iterator it;
    for (it = actors.begin(); it != actors.end(); it++)
    {
        if ((*it)->isAlive())
            (*it)->doSomething();
    }
    //decLives();
    return GWSTATUS_CONTINUE_GAME;
}

void StudentWorld::cleanUp()
{
    delete character;
    for (int i = 0; i < actors.size(); i++)
    {
        std::list<BaseActor*>::iterator it;
        it = actors.begin();
        actors.erase(it);
    }
}


bool StudentWorld::overlap(double newX, double newY, BaseActor *a) {

    std::list<BaseActor*>::iterator it;
    it = actors.begin();
    while (it != actors.end())
    {
        if ((*it) == a) // if the iterator is pointing to same actor as passed in
            it++;
        double bX, bY, dX, dY;

        bX = (*it)->getX();
        bY = (*it)->getY();
        dX = newX - bX;
        dY = newY - bY;
        if (! (*it)->canOverlap())
        {
            if ((newX >= bX && newX <= bX+SPRITE_WIDTH-1 &&
                 newY >= bY && newY <= bY+SPRITE_HEIGHT-1) ||
                (newX+SPRITE_WIDTH-1 >= bX && newX+SPRITE_WIDTH-1 <= bX+SPRITE_WIDTH-1 &&
                 newY >= bY && newY <= bY+SPRITE_HEIGHT-1) ||
                (newX >= bX && newX <= bX+SPRITE_WIDTH-1 &&
                 newY+SPRITE_HEIGHT-1 >= bY && newY+SPRITE_HEIGHT-1 <= bY+SPRITE_HEIGHT-1) ||
                (newX+SPRITE_WIDTH-1 >= bX && newX+SPRITE_WIDTH-1 <= bX+SPRITE_WIDTH-1 &&
                 newY+SPRITE_HEIGHT-1 >= bY && newY+SPRITE_HEIGHT-1 <= bY+SPRITE_HEIGHT-1))
                return false;   //don't let actors overlap with walls
        }
        else if (((dX*dX) + (dY*dY)) <= 100)
        {
            a->onCollision((*it));
            (*it)->onCollision(a);
            return (*it)->canOverlap();
        }
        it++;
    }
    return true;
}

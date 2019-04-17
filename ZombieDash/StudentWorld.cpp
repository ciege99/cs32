#include "StudentWorld.h"
#include "Actor.h"
#include "GraphObject.h"
#include "GameConstants.h"
#include "Level.h"
#include <string>
#include <list>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <cmath>
using namespace std;

GameWorld* createStudentWorld(string assetPath)
{
	return new StudentWorld(assetPath);
}

// Students:  Add code to this file, StudentWorld.h, Actor.h and Actor.cpp

StudentWorld::StudentWorld(string assetPath)
: GameWorld(assetPath), character(nullptr), numHumans(0), numZombies(0), levelWon(false)
{}

StudentWorld::~StudentWorld() {
    this->cleanUp();
}


int StudentWorld::init()
{
    levelWon = false; // start out a level not won
    numHumans = 0;
    numZombies = 0;
    
    
    ostringstream oss;  //set levelFile
    oss << "level";
    oss << setw(2) << setfill('0') << getLevel();
    oss << ".txt";
    
    string levelFile = oss.str();
    //string levelFile = "level04.txt";
    Level lev(assetPath());
    Level::LoadResult result = lev.loadLevel(levelFile);
    if (result == Level::load_fail_bad_format)  //level error if file not formatted correctly
        return GWSTATUS_LEVEL_ERROR;
    else if (result == Level::load_fail_file_not_found || getLevel() == 100)
        return GWSTATUS_PLAYER_WON; //player won if no files left or passed level 99

    
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
                    character = new Penelope(i*SPRITE_WIDTH, j*SPRITE_HEIGHT, this);
                    actors.push_back(character);
                    break;
                case Level::citizen:
                {
                    numHumans++;
                    BaseActor* citizen = new Citizens(i*SPRITE_WIDTH, j*SPRITE_HEIGHT, this);
                    actors.push_back(citizen);

                    break;
                }
                case Level::vaccine_goodie:
                    actors.push_back(new Vaccine(i*SPRITE_WIDTH, j*SPRITE_HEIGHT, this));
                    break;
                case Level::landmine_goodie:
                    actors.push_back(new LandmineGoodie(i*SPRITE_WIDTH, j*SPRITE_HEIGHT, this));
                    break;
                case Level::gas_can_goodie:
                    actors.push_back(new GasCan(i*SPRITE_WIDTH, j*SPRITE_HEIGHT, this));
                    break;
                case Level::pit:
                    actors.push_back(new Pits(i*SPRITE_WIDTH, j*SPRITE_HEIGHT, this));
                    break;
                case Level::wall:
                    actors.push_back(new Walls(i*SPRITE_WIDTH, j*SPRITE_HEIGHT, this));
                    break;
                case Level::exit:
                    actors.push_back(new Exits(i*SPRITE_WIDTH, j*SPRITE_HEIGHT, this));
                    break;
                case Level::dumb_zombie:
                {
                    numZombies++;
                    BaseActor* dZombie = new DumbZombies(i*SPRITE_WIDTH, j*SPRITE_HEIGHT, this);
                    actors.push_back(dZombie);
                    break;
                }
                case Level::smart_zombie:
                {
                    numZombies++;
                    BaseActor* sZombie = new SmartZombies(i*SPRITE_WIDTH, j*SPRITE_HEIGHT, this);
                    actors.push_back(sZombie);
                    break;
                }
                default:
                    break;
            }
        }

    this->setStats();
    
    return GWSTATUS_CONTINUE_GAME;
}

int StudentWorld::move()
{
    
    list<BaseActor*>::iterator it;
    for (it = actors.begin(); it != actors.end(); it++) //loop through and doSomething
    {                                                   //for every actor
        if (! character-> isAlive())    //check that character is alive
        {
            decLives();         //declives and return died if Penelope died
            return GWSTATUS_PLAYER_DIED;
        }
        
        if ( (*it)->isAlive() ) //check actor is alive
            (*it)->doSomething();
        
        if (levelWon == true)
        {
            playSound(SOUND_LEVEL_FINISHED);    //return finished level if levelWon
            return GWSTATUS_FINISHED_LEVEL;
        }
    }
    


    
    //this loop will erase the dead actors from the frame
    it = actors.begin();
    while (it != actors.end())
    {
        if ( !(*it)->isAlive())
        {
            BaseActor* temp = (*it);
            delete temp;
            it = actors.erase(it);
            
        }
        else
            it++;
    }
    
    this->setStats();
    return GWSTATUS_CONTINUE_GAME;
}

void StudentWorld::cleanUp()
{

    std::list<BaseActor*>::iterator it;
    it = actors.begin();
    
    while (it != actors.end())
    {
        BaseActor* temp = (*it);
        delete temp;
        it = actors.erase(it);
    }
}






bool StudentWorld::validFlamePosition(double newX, double newY) {
    list<BaseActor*>::iterator it;
    it = actors.begin();


    
    while (it != actors.end())
    {
        double bX, bY, dX, dY;
        
        if ((! (*it)->isAlive())) //make sure they're alive
            it++;
        
        bX = (*it)->getX();
        bY = (*it)->getY();
        dX = newX - bX; //differences between the positions
        dY = newY - bY;
        
        if ((*it)->flameCannotOverlap()) //Both block movement
        {
            if (((dX*dX) + (dY*dY)) <= 100)
                return false;     //don't let flames overlap walls or exits
        }
        it++;
    }
    return true;
}

bool StudentWorld::validVomitPosition(double newX, double newY) {
    list<BaseActor*>::iterator it;
    it = actors.begin();
    double bX, bY;
    
    while (it != actors.end())
    {
        if ((! (*it)->isAlive())) //make sure they're alive
            it++;
        
        bX = (*it)->getX();
        bY = (*it)->getY();
        
        if ((*it)->flameCannotOverlap() && !(*it)->notBlock()) //Both block movement
        {
            if (findEucidDistance(newX, newY, bX, bY) <= 10)
                return false;     //vomit is stopped by walls
        }
        it++;
    }
    return true;
}

void StudentWorld::CollisionChecker(Environment *a) {
    std::list<BaseActor*>::iterator it;
    it = actors.begin();
    
    if (! a->isAlive()) //stop if a is not alive
        return;
    
    while (it != actors.end())
    {
        if (! a->isAlive()) //if a died, stop looping
            break;
        
        if ((*it) == a) // if the iterator is pointing to same actor as passed in
        {
            it++;
            continue;
        }
    
        if ((! (*it)->isAlive()) ) //make sure they're alive
        {
            it++;
            continue;
        }
        
        double newX, newY, bX, bY;
        newX = a->getX();
        newY = a->getY();
        bX = (*it)->getX();
        bY = (*it)->getY();
        double dist = findEucidDistance(newX, newY, bX, bY);
        

        if (dist <= 10)
            a->onCollision((*it));  // let environment actor do its action
        it++;
    }
}


bool StudentWorld::blockMovement(double newX, double newY, BaseActor *a)
{
    std::list<BaseActor*>::iterator it;
    it = actors.begin();            //returns true if unblocked, false if blocked
    if (! a->isAlive())
        return false;
    while (it != actors.end())
    {
        if ((*it) == a) // if the iterator is pointing to same actor as passed in
        {
            it++;
            continue;
        }
        double bX, bY;
        
        if ((! (*it)->isAlive()) || (! a->isAlive()) ) //make sure they're alive
            it++;
        
        bX = (*it)->getX();
        bY = (*it)->getY();
        
        if (! (*it)->notBlock() && ! a->notBlock()) //Both block movement
        {
            if ((newX >= bX && newX <= bX+SPRITE_WIDTH-1 &&
                 newY >= bY && newY <= bY+SPRITE_HEIGHT-1) ||
                (newX+SPRITE_WIDTH-1 >= bX && newX+SPRITE_WIDTH-1 <= bX+SPRITE_WIDTH-1 &&
                 newY >= bY && newY <= bY+SPRITE_HEIGHT-1) ||
                (newX >= bX && newX <= bX+SPRITE_WIDTH-1 &&
                 newY+SPRITE_HEIGHT-1 >= bY && newY+SPRITE_HEIGHT-1 <= bY+SPRITE_HEIGHT-1) ||
                (newX+SPRITE_WIDTH-1 >= bX && newX+SPRITE_WIDTH-1 <= bX+SPRITE_WIDTH-1 &&
                 newY+SPRITE_HEIGHT-1 >= bY && newY+SPRITE_HEIGHT-1 <= bY+SPRITE_HEIGHT-1))
                return false;   //don't let actors touch walls or each other
        }
        it++;
    }
        return true;
}



void StudentWorld::setLevelWin() {
    levelWon = true;
}



void StudentWorld::setStats() {
    ostringstream oss;
    oss << "Score: ";
    oss << setfill('0') << internal << setw(6) << getScore() ;
    oss << "  Level: ";
    oss  << getLevel();
    oss << "  Lives: " << setw(1) << getLives();
    oss << "  Vacc: " << character->getVaccines();
    oss << "  Flames: " << character->getFlames();
    oss << "  Mines: " << character->getLandmines();
    oss << "  Infected: " << character->getInfectedTotal();
    oss << endl;
    string output = oss.str();
    this->setGameStatText(output);
}


bool StudentWorld::vomitDistance(BaseActor* z) {
    list<BaseActor*>::iterator it;
    for (it = actors.begin(); it != actors.end(); it++)
    {
        if ((*it)->canBeInfected())
        {
            double humanXCoord = (*it)->getX();
            double humanYCoord = (*it)->getY();
            double zXCoord = z->getX();
            double zYCoord = z->getY();
            switch(z->getDirection())
            {
                case BaseActor::right: //right
                {
                    double vomitX = zXCoord+SPRITE_WIDTH;
                    double vomitY = zYCoord;
                    if (validVomitMaker(vomitX, vomitY, humanXCoord, humanYCoord))
                        return true;
                    break;
                }
                case BaseActor::left:   //left
                {
                    double vomitX = zXCoord-SPRITE_WIDTH;
                    double vomitY = zYCoord;
                    if (validVomitMaker(vomitX, vomitY, humanXCoord, humanYCoord))
                        return true;
                    break;
                }
                case BaseActor::up:    //up
                {
                    double vomitX = zXCoord;
                    double vomitY = zYCoord+SPRITE_WIDTH;
                    if (validVomitMaker(vomitX, vomitY, humanXCoord, humanYCoord))
                        return true;
                    break;
                }
                case BaseActor::down: //down
                {
                    double vomitX = zXCoord;
                    double vomitY = zYCoord-SPRITE_WIDTH;
                    if (validVomitMaker(vomitX, vomitY, humanXCoord, humanYCoord))
                        return true;
                    break;
                }
            }
        }
        else
            continue;
    }
    return false;   //no good vomit coordinates
}


void StudentWorld::createLandmine(double startX, double startY) {
    Landmine* newLandmine = new Landmine(startX, startY, this);
    actors.push_back(newLandmine);
}

void StudentWorld::createFlamethrower(double startX, double startY, Direction dir)
{
    double newX = startX;
    double newY = startY;
    switch(dir) {
        case BaseActor::right:
        {
            for (int i = 1; i < 4; i++) {
                newX = startX + (i*SPRITE_WIDTH);
                if (! createFlame(newX, newY, dir))
                    break;
            }
            break;
        }
        case BaseActor::left:
        {
            for (int i = 1; i < 4; i++) {
                newX = startX - (i*SPRITE_WIDTH);
                if (! createFlame(newX, newY, dir))
                    break;
            }
            break;
        }
        case BaseActor::up:
        {
            for (int i = 1; i < 4; i++) {
                newY = startY + (i*SPRITE_HEIGHT);
                if (! createFlame(newX, newY, dir))
                    break;
            }
            break;
        }
        case BaseActor::down:
        {
            for (int i = 1; i < 4; i++) {
                newY = startY - (i*SPRITE_HEIGHT);
                if (! createFlame(newX, newY, dir))
                    break;
            }
            break;

        }
    }
}

bool StudentWorld::createFlame(double startX, double startY, Direction dir) {
    if (this->validFlamePosition(startX, startY))
    {
        actors.push_back(new Flames(startX, startY, dir, this));
        return true;
    }
    return false;
}

void StudentWorld::createLandmineExplosion(double startX, double startY) {
    Flames* newFlame = new Flames(startX, startY, BaseActor::up, this);
    actors.push_back(newFlame);
    Pits* newPit = new Pits(startX, startY, this);
    actors.push_back(newPit);
    
    this->createFlame(startX, startY+SPRITE_HEIGHT, BaseActor::up); //top
    this->createFlame(startX-SPRITE_WIDTH, startY+SPRITE_HEIGHT, BaseActor::up); //top left
    this->createFlame(startX-SPRITE_WIDTH, startY, BaseActor::up);  //left
    this->createFlame(startX-SPRITE_WIDTH, startY-SPRITE_HEIGHT, BaseActor::up); //bot left
    this->createFlame(startX, startY-SPRITE_HEIGHT, BaseActor::up); //bot
    this->createFlame(startX+SPRITE_WIDTH, startY-SPRITE_HEIGHT, BaseActor::up); //bot right
    this->createFlame(startX+SPRITE_WIDTH, startY, BaseActor::up); //right
    this->createFlame(startX+SPRITE_WIDTH, startY+SPRITE_HEIGHT, BaseActor::up); //top right
    
}


bool StudentWorld::addVaccine(BaseActor* a)
{
    if (a == character)
    {
        increaseScore(50);   //increase points by 50
        this->playSound(SOUND_GOT_GOODIE);
        character->addVaccine();
        return true;
    }
    return false;
}

bool StudentWorld::addLandmines(BaseActor *a)
{
    if (a == character)
    {
        increaseScore(50);   //increase points by 50
        this->playSound(SOUND_GOT_GOODIE);
        character->addLandmines();
        return true;
    }
    return false;
}

bool StudentWorld::addFlames(BaseActor *a)
{
    if (a == character)
    {
        increaseScore(50);   //increase points by 50
        this->playSound(SOUND_GOT_GOODIE);
        character->addFlames();
        return true;
    }
    return false;
}


void StudentWorld::playerExit(BaseActor* a)
{
    //if player steps on exit, check that number of humans is <= 0 before exit
    if (a->canBeInfected() && a != character)
    {
        numHumans--;
        increaseScore(500); //decrement humans, increase score, play correct sound
        playSound(SOUND_CITIZEN_SAVED);
        a->setDead();
    }
    if (a == character)
        if (numHumans <= 0) //if all humans are gone, let penelope exit
            setLevelWin();
    
}

bool StudentWorld::findClosestHuman(BaseActor *a, double &distTo) {
    double aX, aY, bX, bY, dX, dY, smallest;
    smallest = 131072;   //set smallest to largest possible Euc. dist. 2*(256^2)
    aX = a->getX();
    aY = a->getY();
    BaseActor *closest = nullptr;
    list<BaseActor*>::iterator it;
    for (it = actors.begin(); it != actors.end(); it++)
    {
        if ((*it) == a)
            it++;
        
        if (! (*it)->isAlive())
            it++;
        
        if ( (*it)->canBeInfected() )   //if it's a zombie looking for humans
        {
            bX = (*it)->getX();
            bY = (*it)->getY();
            dX = aX - bX;
            dY = aY- bY;
            double dist = (dX*dX) + (dY*dY);
            if (dist < smallest)
            {
                closest = (*it);
                smallest = dist;
            }
        }
    }
    
    distTo = smallest;  //pass smallest distance to distTo
    
    bX = closest->getX();
    bY = closest->getY();
    if (smallest > 6400) //80^2 = 6400
        return false; //getRandDirection
    else
        setDirectionToClosest(a, bX, bY);
    return true;
}

double StudentWorld::findClosestZombie(double aX, double aY) {
    double bX, bY, smallest;
    smallest = sqrt(pow(256,2) + pow(256, 2));   //set smallest to largest possible Euc. dist
    list<BaseActor*>::iterator it;
    
    if (numZombies <= 0)
        return (sqrt( (pow(256, 2) + pow(256, 2)) ) );  // return max distance if no zombies
    
    for (it = actors.begin(); it != actors.end(); it++)
    {
        
        
        if (! (*it)->isAlive())
            it++;
        
        if ( (*it)->canMove() && !(*it)->canBeInfected())
        {
            bX = (*it)->getX();
            bY = (*it)->getY(); //use distance func to find the distance
            double dist = findEucidDistance(aX, aY, bX, bY);
            if (dist < smallest)    //set smallest to be equal to smallest distance
            {
                smallest = dist;
            }
        }
    }
    
    return smallest;  //pass smallest distance to distTo
}

bool StudentWorld::setDirectionToClosest(BaseActor *a, double closestX, double closestY) {
    double aX, aY;
    aX = a->getX();
    aY = a->getY();
    const int MOVE = a->getMove();
    
    if (a->canBeInfected())     //if a is a citizen, closest should be penelope
    {
        closestX = character->getX();
        closestY = character->getY();
    }
    
    if (aX == closestX) //same row
    {
        if (closestY > aY)    //target is up
        {
            if (a->canBeInfected()) //for when citizens use this
            {
                if (blockMovement(aX, aY+MOVE, a))
                {
                    a->setDirection(BaseActor::up);
                    return true;
                }
            }
            else    //for when zombies use this
                a->setDirection(BaseActor::up);
        }
        else
        {
            if (a->canBeInfected())
            {
                if (blockMovement(aX, aY-MOVE, a))
                {
                    a->setDirection(BaseActor::down);
                    return true;
                }
            }
            else
                a->setDirection(BaseActor::down);
        }
    }
    else if (aY == closestY)
    {
        if (closestX > aX)    //target is right
        {
            if (a->canBeInfected())
            {
                if (blockMovement(aX+MOVE, aY, a))
                {
                    a->setDirection(BaseActor::right);
                    return true;
                }
            }
            else
                a->setDirection(BaseActor::right);
        }
        else
        {
            if (a->canBeInfected())
            {
                if (blockMovement(aX-MOVE, aY, a))
                {
                    a->setDirection(BaseActor::left);
                    return true;
                }
            }
            else
                a->setDirection(BaseActor::left);
        }
    }
    
    else
    {
        int random = randInt(1, 2); //set a random int that will direct zombie
        if (randomDirSwitch(a, closestX, closestY, random) )
            return true;
        else
        {
            if (random == 1)        //if first direction failed, try the other
            {
                if (randomDirSwitch(a, closestX, closestY, 2))
                    return true;
                else
                    return false;
            }
            else
            {
                if (randomDirSwitch(a, closestX, closestY, 1))
                    return true;
                else
                    return false;
            }
        }
    }
    
    if (a->canBeInfected()) // if this point is reached as a citizen, can't move
        return false;
    return true;        //always true for zombie
}


void StudentWorld::infectedCitizenProtocol(double startX, double startY) {  //call on citizen death
    playSound(SOUND_ZOMBIE_BORN);
    increaseScore(-1000);
    numHumans--;
    switch(randInt(1, 10))
    {
        case 1:         //30% chance of smart, 70% chance of dumb
        case 2:
        case 3:
            actors.push_back(new SmartZombies(startX, startY, this));
            break;
        default:
            actors.push_back(new DumbZombies(startX, startY, this));
            break;
            
    }
}


double StudentWorld::findDistPenelope(BaseActor *a) {
    return findEucidDistance(a->getX(), a->getY(), character->getX(), character->getY());

}


bool StudentWorld::randomDirSwitch(BaseActor *a, double closestX, double closestY, int n) {
    double aY = a->getY();
    double aX = a->getX();
    const int MOVE = a->getMove();
    switch(n) { //randomly send zombie either in vert or horiz
        case 1: //vertical
        {
            if (closestY > aY)  //move up
            {
                if (a->canBeInfected())
                {   //check that humans aren't blocked
                    if (blockMovement(aX, aY+MOVE, a))
                    {
                        a->setDirection(BaseActor::up);
                        return true;
                    }
                }
                else
                    a->setDirection(BaseActor::up);
            }
            else    //move down
            {
                if (a->canBeInfected())
                { //check that humans aren't blocked
                    if (blockMovement(aX, aY-MOVE, a))
                    {
                        a->setDirection(BaseActor::down);
                        return true;
                    }
                }
                else
                    a->setDirection(BaseActor::down);
            }
            break;
        }
        case 2: //horizontal
        {
            if (closestX > aX) //move right
            {
                if (a->canBeInfected())
                {   //check that humans aren't blocked
                    if (blockMovement(aX+MOVE, aY, a))
                    {
                        a->setDirection(BaseActor::right);
                        return true;
                    }
                }
                else
                    a->setDirection(BaseActor::right);
            }
            else    //move left
            {
                if (a->canBeInfected())
                {   // check that humans aren't blocked
                    if (blockMovement(aX-MOVE, aY, a))
                    {
                        a->setDirection(BaseActor::left);
                        return true;
                    }
                }
                else
                    a->setDirection(BaseActor::left);
            }
            break;
        }
    }
    if (a->canBeInfected()) // if this point is reached as a citizen, can't move
        return false;
    return true;        //always true for zombie
}




double StudentWorld::findEucidDistance(double aX, double aY, double bX, double bY) {
    double dX = aX-bX;  //distance formula
    double dY = aY-bY;
    return sqrt(pow(dX, 2) + pow(dY, 2));
}

void StudentWorld::decreaseNumHumans() {
    numHumans--;
}

int StudentWorld::getHumans() {
    return numHumans;
}

bool StudentWorld::validVomitMaker(double vomitX, double vomitY, double humanX, double humanY) {

    if (findEucidDistance(humanX, humanY, vomitX, vomitY) <= 10)
    {
        switch(randInt(1, 3))   //1 in 3 chance of vomitting
        {
            case 1:
            {
                if (validVomitPosition(vomitX, vomitY))    //check to make sure vomit is in valid spot
                {
                    actors.push_back(new Vomit(vomitX, vomitY, this));  //push if so
                    return true;
                }
                break;
            }
            default:
                break;
        }
        
    }
    return false;   //false if nothing created
}

void StudentWorld::chanceOfVaccine(Direction dir, double origX, double origY) {
    switch(randInt(1, 10)) {            // 1 in 10 chance of Vacc
        case 1:
            double posX, posY;
            posSetter(dir, origX, origY, posX, posY);   //posX & posY now hold new position
            if (! overlap(posX, posY))    //if vac won't overlap anything
                actors.push_front(new Vaccine(posX, posY, this));   //push to front so flame does not destroy it
            break;
        default:
            break;
            
    }
}


void StudentWorld::posSetter(Direction dir, double origX, double origY, double& posX, double& posY) {
    //set posX and posY to be new position in the direction of actor
    switch (dir) {
        case BaseActor::right:
            posX = origX + SPRITE_WIDTH;
            posY = origY;
            break;
        case BaseActor::left:
            posX = origX - SPRITE_WIDTH;
            posY = origY;
            break;
        case BaseActor::up:
            posX = origX;
            posY = origY + SPRITE_HEIGHT;
            break;
        case BaseActor::down:
            posX = origX;
            posY = origY - SPRITE_HEIGHT;
            break;
    }
}

bool StudentWorld::overlap(double newX, double newY) {
    std::list<BaseActor*>::iterator it;
    it = actors.begin();
    
    while (it != actors.end())
    {
        if ((! (*it)->isAlive()) ) //make sure they're alive
        {
            it++;
            continue;
        }
        double bX, bY;
        bX = (*it)->getX();
        bY = (*it)->getY();
        double dist = findEucidDistance(newX, newY, bX, bY);
        if (dist <= 10)
            return true;  // return true if coordinates match with any existing coordinates
        it++;
    }
    return false;    //return true if it does not overlap with anything
}

void StudentWorld::infector(BaseActor* vomit, BaseActor* a) {
    if (vomit->isAlive() && a->isAlive() && a->canBeInfected() && !a->isInfected())
    {
        if (a != character) //play sound if citizen is infected
            playSound(SOUND_CITIZEN_INFECTED);
        a->setInfected();
    }

}

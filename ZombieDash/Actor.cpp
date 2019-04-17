#include "Actor.h"
#include "StudentWorld.h"
#include "GameConstants.h"
#include "GraphObject.h"

// Students:  Add code to this file, Actor.h, StudentWorld.h, and StudentWorld.cpp

//constructors

BaseActor::BaseActor(int imageID, double startX,
                    double startY, Direction dir, int depth, StudentWorld *world) :
                    GraphObject(imageID, startX, startY, dir, depth),
                    m_alive(true), m_world(world), m_isInfected(false)
                    {}

MoveableActors::MoveableActors(int imageID, double startX,
                    double startY, Direction dir, int depth, StudentWorld* world) :
                    BaseActor (imageID, startX, startY, dir, depth, world), m_ticks(0)
                    {}

Humans::Humans(int imageID, double startX, double startY,
                    Direction dir, int depth, StudentWorld* world) :
                    MoveableActors(imageID, startX, startY, dir, depth, world),
                    m_infectedTotal(0)
                    {}

Zombies::Zombies(double startX, double startY, Direction dir,
                 int depth, StudentWorld* world) : MoveableActors(IID_ZOMBIE, startX, startY, dir, depth, world), m_planDist(0)
                    {}

Penelope::Penelope(double startX, double startY, StudentWorld* world) :
                    Humans(IID_PLAYER, startX, startY, right, 0, world), m_landmines(0), m_vaccines(0), m_flames(0)
                    {}


Environment::Environment(int imageID, double startX, double startY,
                    Direction dir, int depth, StudentWorld* world) :
                    BaseActor(imageID, startX, startY, dir, depth, world)
                    {}

Goodies::Goodies(int imageID, double startX, double startY, Direction dir, int
                    depth, StudentWorld* world) : Environment(imageID, startX,
                    startY, dir, depth, world)
                    {}



Permanents::Permanents(int imageID, double startX, double startY, Direction dir,
                    int depth, StudentWorld* world) :
                    Environment(imageID, startX, startY, dir, depth, world)
                    {}

Citizens::Citizens(double startX, double startY, StudentWorld* world) :
                    Humans(IID_CITIZEN, startX, startY, right, 0, world), m_saved(false)
                    {}

DumbZombies::DumbZombies(double startX, double startY, StudentWorld* world) :
                    Zombies(startX, startY, right, 0, world)
                    {}

SmartZombies::SmartZombies(double startX, double startY, StudentWorld* world) :
                    Zombies(startX, startY, right, 0, world)
                    {}

Vaccine::Vaccine(double startX, double startY, StudentWorld* world) :
                    Goodies(IID_VACCINE_GOODIE, startX, startY, right, 1, world)
                    {}

GasCan::GasCan(double startX, double startY, StudentWorld* world) :
                    Goodies(IID_GAS_CAN_GOODIE, startX, startY, right, 1, world)
                    {}
LandmineGoodie::LandmineGoodie(double startX, double startY, StudentWorld*
                    world) :
                    Goodies(IID_LANDMINE_GOODIE, startX, startY, right, 1, world)
                    {}

Landmine::Landmine(double startX, double startY, StudentWorld* world) :
                    Goodies(IID_LANDMINE, startX, startY, right, 1, world),
                    m_safetyTicks(30)
                    {}

Projectiles::Projectiles(int imageID, double startX, double startY,
                    Direction dir, int depth, StudentWorld* world) :
                    Permanents(imageID, startX, startY, dir, depth, world),
                    lifespan(2)
                    {}

Pits::Pits(double startX, double startY, StudentWorld* world) :
                    Permanents(IID_PIT, startX, startY, right, 0, world)
                    {}

Walls::Walls(double startX, double startY, StudentWorld* world) :
                    BaseActor(IID_WALL, startX, startY, right, 0, world)
                    {}

Exits::Exits(double startX, double startY, StudentWorld* world) :
                    Permanents(IID_EXIT, startX, startY, right, 1, world)
                    {}


Flames::Flames(double startX, double startY, Direction dir, StudentWorld* world) :
                    Projectiles(IID_FLAME, startX, startY, dir, 0, world)
                    {}

Vomit::Vomit(double startX, double startY, StudentWorld* world) :
                    Projectiles(IID_VOMIT, startX, startY, right, 0, world)
{
    this->getWorld()->playSound(SOUND_ZOMBIE_VOMIT);
}
                                                                  


// doSomething



void Environment::doSomething() {
    differentRequirements();
    this->getWorld()->CollisionChecker(this);     
}

bool Environment::hasOverlapAction() {
    return true;
}


// BaseActor functions
bool BaseActor::isAlive() {
    return m_alive;
}

void BaseActor::beKilled() {
    this->setDead();
}

bool BaseActor::notBlock() {
    return true;
}

bool BaseActor::flameCannotOverlap() {
    return false;
}

StudentWorld* BaseActor::getWorld() {
    return m_world;
}

bool BaseActor::canMove() {
    return false;
}


bool BaseActor::canBeInfected() {
    return false;   //default to false
}



bool BaseActor::canBeKilled() {
    return true;
}

bool BaseActor::isInfected() {
    return m_isInfected;
}


void BaseActor::setInfected() {
    m_isInfected = true;
}


void BaseActor::setDead() {
    m_alive = false;
}

void BaseActor::setIsInfectedFalse() {
    m_isInfected = false;
}

bool BaseActor::hasOverlapAction() {
    return false;
}

int BaseActor::getMove() {
    return 0;   //assume 0 at start
}

// MoveableActors functions

bool MoveableActors::canMove() {
    return true;
}

int MoveableActors::getTicks() {
    return m_ticks;
}

void MoveableActors::increaseTicks() {
    m_ticks++;
}

void MoveableActors::setTicksZero() {
    m_ticks = 0;
}

void MoveableActors::setTicks(int n) {
    m_ticks = n;
}

void MoveableActors::decreaseTicks() {
    m_ticks--;
}


bool MoveableActors::notBlock() {
    return false;   // moveable actors can't overlap
}

bool MoveableActors::mover() {
    // return true if move is possible, false if not
    switch (this->getDirection()) {
        case right:
            if (this->getWorld()->blockMovement(getX()+getMove(), getY(), this))
            {
                this->moveTo(getX()+getMove(), getY());
                return true;
            }
            else
                return false;
            break;
        case left:
            if (this->getWorld()->blockMovement(getX()-getMove(), getY(), this))
            {
                this->moveTo(getX()-getMove(), getY());
                return true;
            }
            else
                return false;
            break;
        case up:
            if (this->getWorld()->blockMovement(getX(), getY()+getMove(), this))
            {
                this->moveTo(getX(), getY()+getMove());
                return true;
            }
            else
                return false;
            break;
        case down:
            if (this->getWorld()->blockMovement(getX(), getY()-getMove(), this))
            {
                this->moveTo(getX(), getY()-getMove());
                return true;
            }
            else
                return false;
            break;
        default:
            return false;
    }
}

void MoveableActors::beKilled() {
    deathProtocol();
    this->setDead();
}

bool MoveableActors::tickManager() {
    this->increaseTicks();
    if (this->getTicks() >= 2)
    {
        this->setTicksZero();    // paralysis tick
        return false;   //return false if it is a paralysis tick
    }
    return true;
}

int MoveableActors::getMove() {
    return 1;
}

// Humans functions

bool Humans::commonHumanActions() {
    if (! this->isAlive() ) //check that human is alive
        return false;
    
    if (this->isInfected())         //return false if it should stop
    {
        this->increaseInfectedTotal();
        if (this->getInfectedTotal() >= 500)
        {
            this->beKilled();   //from BaseActor class
            return false;
        }
    }
    
    return true;
}

void Humans::doSomething() {
    if (! commonHumanActions())
        return;
    
    differentHumanBehavior();
}

int Humans::getInfectedTotal() {
    return m_infectedTotal;
}

void Humans::setHealthy() {
    setIsInfectedFalse();
    m_infectedTotal = 0;
}

void Humans::increaseInfectedTotal() {
    m_infectedTotal++;
}


bool Humans::canBeInfected() {
    return true;
}



// Penelope functions


void Penelope::flamethrower() {
    if (m_flames <= 0)
    {
        return; //return if no gas
    }
    
    m_flames--;
    this->getWorld()->playSound(SOUND_PLAYER_FIRE);
    this->getWorld()->createFlamethrower(getX(), getY(), getDirection());
    
}


void Penelope::placeLandmine() {
    if (m_landmines > 0) {
        m_landmines--;
        this->getWorld()->createLandmine(this->getX(), this->getY());
    }
}

void Penelope::useVaccine() {
    if (m_vaccines > 0) {
        this->setHealthy();
        m_vaccines--;
    }
}

void Penelope::addVaccine() {
    m_vaccines++;
}

void Penelope::addLandmines() {
    m_landmines += 2;
}

void Penelope::addFlames() {
    m_flames += 5;
}

int Penelope::getVaccines() {
    return m_vaccines;
}

int Penelope::getLandmines() {
    return m_landmines;
}

int Penelope::getFlames() {
    return m_flames;
}

void Penelope::deathProtocol() {
    getWorld()->playSound(SOUND_PLAYER_DIE);
}

void Penelope::differentHumanBehavior() {
    int ch;
    if (this->getWorld()->getKey(ch))
    {
        double oldX = this->getX();
        double oldY = this->getY();
        switch (ch) {
            case KEY_PRESS_LEFT:
                setDirection(left); //allow penelope to move if a move is possible for that keypress
                if (! this->getWorld()->blockMovement(oldX-MOVE, oldY, this))
                    break;
                this->moveTo(oldX-MOVE, oldY);
                break;
            case KEY_PRESS_RIGHT:
                setDirection(right);
                if (! this->getWorld()->blockMovement(oldX+MOVE, oldY, this))
                    break;
                this->moveTo(oldX+MOVE, oldY);
                break;
            case KEY_PRESS_UP:
                setDirection(up);
                if (! this->getWorld()->blockMovement(oldX, oldY+MOVE, this))
                    break;
                this->moveTo(oldX, oldY+MOVE);
                break;
            case KEY_PRESS_DOWN:
                setDirection(down);
                if (! this->getWorld()->blockMovement(oldX, oldY-MOVE, this))
                    break;
                this->moveTo(oldX, oldY-MOVE);
                break;
            case KEY_PRESS_SPACE:
                this->flamethrower();
                break;
            case KEY_PRESS_TAB:
                this->placeLandmine();
                break;
            case KEY_PRESS_ENTER:
                this->useVaccine();
                break;
        }
        
    }
}


// Citizens functions

void Citizens::differentHumanBehavior() {
    
    if (! tickManager())
        return;
    
    
    double dist_p, dist_z;  //calculate distances to penelope and zombies
    dist_p = this->getWorld()->findDistPenelope(this);
    dist_z= this->getWorld()->findClosestZombie(getX(), getY());
    if (dist_p < dist_z && dist_p <= 80) // move citizen towards Penelope if closer to Penelope
    {
        double usedInFunc1 = 0;
        double usedInFunc2 = 0; //set direction of Citizens to Penelope
        bool moveToPenelope = this->getWorld()->setDirectionToClosest(this, usedInFunc1, usedInFunc2);
        if (moveToPenelope)
        {
            mover();    //citizens direction has been set for Penelope, so move
            return;
        }
    }
    
    if (dist_z <= 80)
    {
        double curX = this->getX();
        double curY = this->getY();
        double newDistance = dist_z;
        
        double distRight, distLeft, distUp, distDown;   //default values of 80, find greatest value
        distRight = 80;
        distLeft = 80;
        distUp = 80;
        distDown = 80;  //see if there is a greater distance from zombies, move to the greatest
        if (getWorld()->blockMovement(curX+getMove(), curY, this))   //right
        {
            distRight = getWorld()->findClosestZombie(curX+getMove(), curY);
            if (distRight > newDistance)
                newDistance = distRight;
        }
        
        if (getWorld()->blockMovement(curX-getMove(), curY, this))   //left
        {
            distLeft = getWorld()->findClosestZombie(curX-getMove(), curY);
            if (distLeft > newDistance)
                newDistance = distLeft;
        }
        if (getWorld()->blockMovement(curX, curY+getMove(), this))   //up
        {
            distUp = getWorld()->findClosestZombie(curX, curY+getMove());
            if (distUp > newDistance)
                newDistance = distUp;
        }
        
        if (getWorld()->blockMovement(curX, curY-getMove(), this))   //down
        {
            distDown = getWorld()->findClosestZombie(curX, curY-getMove());
            if (distDown > newDistance)
                newDistance = distDown;
        }
        
        if (newDistance == dist_z)  //no good move, just stay in place
            return;
        
        else
        {
            if (newDistance == distRight)
            {
                setDirection(right);
                mover();
            }
            else if (newDistance == distLeft)
            {
                setDirection(left);
                mover();
            }
            else if (newDistance == distUp)
            {
                setDirection(up);
                mover();
            }
            else if (newDistance == distDown)
            {
                setDirection(down);
                mover();
            }
            
        }
    }
    return;
        
}
    
    


void Citizens::deathProtocol() {
    if (isInfected() && getInfectedTotal() >= 500)  //person dies of infection
        getWorld()->infectedCitizenProtocol(getX(), getY());
    else if (m_saved == true) { //person exits
        return;
    }
    else
    {   //person is killed by flame/pit
        getWorld()->playSound(SOUND_CITIZEN_DIE);
        getWorld()->increaseScore(-1000);
        getWorld()->decreaseNumHumans();
    }
}
             
void Citizens::setSaved() {
    m_saved = true;
}


int Citizens::getMove() {
    return 2;
}



// Zombies functions

bool Zombies::commonZombieActions() {
    if (! this->isAlive())  //part 1        //return false if zombie should stop
        return false;
    
    
    if (! tickManager())
        return false;
    
    if (this->getWorld()->vomitDistance(this))  //vomit if it can
    {
        this->getWorld()->playSound(SOUND_ZOMBIE_VOMIT);
        return false;   //immediately return if it vomits
    }
    
    return true;
}

void Zombies::doSomething() {
    if (! commonZombieActions())
        return;
    
    differentZombieActions();
    
    if (mover())    //if a move is possible, decrement distance
        this->modifyPlanDist(-1);
    else
        this->setPlanDistZero();    //set dist zero otherwise
}


void Zombies::modifyPlanDist(int n) {
    m_planDist += n;
}

int Zombies::getPlanDist() {
    return m_planDist;
}

void Zombies::setPlanDistZero() {
    m_planDist = 0;
}



void Zombies::randomPlanDist() {
    int n = randInt(3, 10); //generate random distance plan
    this->modifyPlanDist(n);
}

void Zombies::randomDirectionSelector() {
    
    switch (randInt(1, 4)) {
        case 1:
            this->setDirection(right);
            break;
        case 2:
            this->setDirection(left);
            break;
        case 3:
            this->setDirection(up);
            break;
        case 4:
            this->setDirection(down);
            break;
    }
}



// Goodies functions

void Goodies::differentRequirements() {
    return;
}



// Permanents functions
bool Permanents::canBeKilled() {
    return false;
}


// DumbZombie functions



void DumbZombies::differentZombieActions() {
    
    if (this->getPlanDist() == 0) // part 4 set direction
    {
        randomPlanDist();
        randomDirectionSelector();
    }
    
}

void DumbZombies::deathProtocol()
{
    this->getWorld()->playSound(SOUND_ZOMBIE_DIE);  //play sound and increase score on dumb zombie death
    this->getWorld()->increaseScore(1000);
    this->getWorld()->chanceOfVaccine(getDirection(), getX(), getY());
}


// SmartZombie functions



void SmartZombies::differentZombieActions() {

    if (this->getPlanDist() == 0)
    {
        randomPlanDist();
        double unused;  //necessary double to use findCloset human
        if (! getWorld()->findClosestHuman(this, unused))   //if no human to move to
            randomDirectionSelector();              //set random dir
    }
    
}


void SmartZombies::deathProtocol() {
    this->getWorld()->playSound(SOUND_ZOMBIE_DIE);
    this->getWorld()->increaseScore(2000);
}



// Vaccine Goodie functions
void Vaccine::onCollision(BaseActor *a) {
    if (getWorld()->addVaccine(a))
        this->beKilled();   //if overlapped by penelope, be destroyed
}

// Landmine Goodie functions

void LandmineGoodie::onCollision(BaseActor *a) {
    if (getWorld()->addLandmines(a))
        this->beKilled();   //if overlapped by penelope, be destroyed
}


// Landmine functions
void Landmine::onCollision(BaseActor *a) {
    if (m_safetyTicks <= 0)
    {   //if overlapped when it is dangerous, explode
        this->getWorld()->playSound(SOUND_LANDMINE_EXPLODE);
        this->getWorld()->createLandmineExplosion(getX(), getY());
        if (a->isAlive())
            a->beKilled();
        this->beKilled();
    }
}

void Landmine::differentRequirements() {
    if (m_safetyTicks > 0)
        m_safetyTicks--;
}


// GasCan Goodie functions
void GasCan::onCollision(BaseActor *a) {
    if (getWorld()->addFlames(a))
        this->beKilled();
}


// Projectiles functions
void Projectiles::differentRequirements() {
    //this->getWorld()->CollisionChecker(this);
    if ( this->isAlive())
    {
        lifespan--;
        if (lifespan <= 0)  //projectiles only last two ticks
            this->beKilled();
    }
}


// Pits functions
void Pits::onCollision(BaseActor *a) {
    a->beKilled();
}

void Pits::differentRequirements() {
    return;
}

// Walls functions

void Walls::doSomething() {
    return;
}

bool Walls::notBlock() {
    return false;
}

bool Walls::flameCannotOverlap() {
    return true;
}



// Exits functions

void Exits::onCollision(BaseActor *a) {
    this->getWorld()->playerExit(a); //try to let player exit
}


bool Exits::flameCannotOverlap() {
    return true;
}

void Exits::differentRequirements() {
    return;
}


// Flames functions

void Flames::onCollision(BaseActor *a) {
    if (this->isAlive())
    {
        if ( a->canBeKilled() )
            a->beKilled();
    }
}





//Vomit functions

void Vomit::onCollision(BaseActor *a) {
    getWorld()->infector(this, a);

}

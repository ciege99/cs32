#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"

class StudentWorld;
class GameWorld;
// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp
/*
 GraphObject(int imageID, double startX, double startY,
 int startDirection = 0, int depth = 0);
 
 
 */


class BaseActor : public GraphObject
{
public:
    BaseActor(int imageID, double startX, double startY, Direction dir , int depth, StudentWorld* world);

    
    virtual void doSomething() = 0;     // must be pure virtual, a bunch of different actions
    
    
    void setDead();
    virtual void beKilled();    //everybody dies the same, some have sounds
    bool isAlive();                 //all actors will use this the same
    
    
    
    //identifiers
    virtual bool canBeKilled();
    virtual bool canMove();
    virtual bool notBlock();  //used for walls, can't be touched at all
    virtual bool flameCannotOverlap();  //used for walls and exits
    virtual bool canBeInfected();
    virtual bool hasOverlapAction();
    StudentWorld* getWorld();   //accessor for StudentWorld pointer
    virtual int getMove();
    
    void setInfected();
    bool isInfected();
    void setIsInfectedFalse();
    
    virtual ~BaseActor() {}
    
private:
    bool m_alive;         //bool for whether actor is alive
    StudentWorld* m_world;
    bool m_isInfected;
    
    
};


//2nd layer of class structure

class MoveableActors : public BaseActor {
public:
    

    
    MoveableActors(int imageID, double startX, double startY, Direction dir, int depth, StudentWorld* world);
    
    int getTicks();
    void increaseTicks();
    void decreaseTicks();
    void setTicks(int n);
    void setTicksZero();
    bool tickManager();
    
    
    bool mover();
    virtual bool notBlock();
    virtual bool canMove();
    virtual void beKilled();
    virtual void deathProtocol() = 0;
    virtual int getMove();
    
    virtual ~MoveableActors() {}
    
private:
   
    int m_ticks;
    
};

class Environment : public BaseActor {
public:
    Environment(int imageID, double startX, double startY, Direction dir, int depth, StudentWorld* world);
    
    virtual void doSomething();
    virtual void onCollision(BaseActor *a) = 0;
    virtual bool hasOverlapAction();
    virtual void differentRequirements() = 0;
    
    virtual ~Environment() {}
    
private:
    
};

class Walls : public BaseActor {
public:
    Walls(double startX, double startY, StudentWorld *world);
    virtual void doSomething();
    virtual bool notBlock();
    virtual bool flameCannotOverlap();
};


//3rd layer of class structure

//moveables

class Humans : public MoveableActors {
public:
    Humans(int imageID, double startX, double startY, Direction dir, int depth, StudentWorld* world);

    
       // this will be reset in Penelope and Citizens class
    virtual bool canBeInfected();
    virtual void doSomething();
    virtual void differentHumanBehavior() = 0;
    bool commonHumanActions();
    
    int getInfectedTotal();
    void increaseInfectedTotal();
    void setHealthy();
    
    virtual ~Humans() {}
    
    
private:
    int m_infectedTotal;
};

class Zombies : public MoveableActors {
    
public:
    const int MOVE = 1;
    Zombies(double startX, double startY, Direction dir, int depth, StudentWorld* world);
    
    virtual void doSomething();
    
    void modifyPlanDist(int n);
    void setPlanDistZero();
    int getPlanDist();
    bool commonZombieActions();
    void randomDirectionSelector();
    void randomPlanDist();
    
    virtual ~Zombies() {}
    
    
private:
    int m_planDist;
    virtual void differentZombieActions() = 0;

};


//environment

class Goodies : public Environment {
    
public:
    Goodies(int imageID, double startX, double startY, Direction dir, int depth, StudentWorld *world);
    virtual void differentRequirements();
    
    virtual ~Goodies() {}
    
private:
    
};

class Permanents : public Environment {
    
public:
    
    Permanents(int imageID, double startX, double startY, Direction dir, int depth, StudentWorld *world);
    
    virtual bool canBeKilled(); //overwrite to false

    virtual ~Permanents() {}
private:
    
};



//4th layer of class structure

// penelope and citizens


class Penelope : public Humans {
    
public:
    Penelope(double startX, double startY, StudentWorld* world);
    
    const int MOVE = 4;   // number of pixels per move
    
    virtual void differentHumanBehavior();
    
    
    virtual void deathProtocol();
    
    //inventory functions
    void addVaccine();
    void addFlames();
    void addLandmines();
    
    //getters
    int getVaccines();
    int getFlames();
    int getLandmines();
    
private:
    int m_landmines;
    int m_vaccines;
    int m_flames;
    
    // actions
    void flamethrower();
    void placeLandmine();
    void useVaccine();

    
};

class Citizens : public Humans {
public:
    const int MOVE = 2;
    
    Citizens(double startX, double startY, StudentWorld* world);
    virtual void differentHumanBehavior();
    virtual void deathProtocol();
    void setSaved();
    virtual int getMove();

    
private:
    
    bool m_saved;
};


// zombies

class DumbZombies : public Zombies {
    
public:
    DumbZombies(double startX, double startY, StudentWorld* world);
    
    
    
private:
    virtual void deathProtocol();
    virtual void differentZombieActions();
};

class SmartZombies : public Zombies {
    
public:
    SmartZombies(double startX, double startY, StudentWorld* world);
    
    
    
private:
    virtual void deathProtocol();
    virtual void differentZombieActions();
};


// goodies

class Vaccine : public Goodies {
    
public:
    Vaccine(double startX, double startY, StudentWorld* world);
    virtual void onCollision(BaseActor *a);
    
private:
    
};

class GasCan : public Goodies {
    
public:
    GasCan(double startX, double startY, StudentWorld* world);
    virtual void onCollision(BaseActor *a);
private:
    
};

class LandmineGoodie : public Goodies {
    
public:
    LandmineGoodie(double startX, double startY, StudentWorld* world);
    virtual void onCollision(BaseActor *a);
private:
    
};

class Landmine : public Goodies {
    
public:
    Landmine(double startX, double startY, StudentWorld* world);
    virtual void onCollision(BaseActor *a);
    virtual void differentRequirements();
private:
    int m_safetyTicks;
    
};


// permanents

class Projectiles : public Permanents {
    
public:
    Projectiles(int imageID, double startX, double startY, Direction dir, int depth, StudentWorld* world);
    virtual void differentRequirements();
    
    virtual ~Projectiles() {}
    
private:
    int lifespan;
};

class Pits : public Permanents {
    
public:
    Pits(double startX, double startY, StudentWorld *world);
    virtual void onCollision(BaseActor *a);
    virtual void differentRequirements();
    
private:
    
};


class Exits : public Permanents {
    
public:
    Exits(double startX, double startY, StudentWorld *world);
    virtual void onCollision(BaseActor *a);
    virtual bool flameCannotOverlap();
    virtual void differentRequirements();
    
private:
    
};


// 5th layer (only projectiles)

class Flames : public Projectiles {
    
public:
    Flames(double startX, double startY, Direction dir, StudentWorld* world);
    virtual void onCollision(BaseActor *a);
    
private:
    
};

class Vomit : public Projectiles {
    
public:
    Vomit(double startX, double startY, StudentWorld* world);
    virtual void onCollision(BaseActor *a);
    
private:
    
    
};


#endif // ACTOR_H_

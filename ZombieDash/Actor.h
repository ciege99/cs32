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
    //virtual bool beOverlapped() = 0;
    
    virtual void onCollision(BaseActor *a) = 0;
    virtual void beKilled();    //this could actual just be normal or virtual, everybody dies the same
    bool isAlive();                 //static because all actors will use this the same
    virtual bool canOverlap();  //default is true
    StudentWorld* getWorld();   //accessor for StudentWorld pointer
    
private:
    bool m_alive;         //bool for whether actor is alive
    StudentWorld* m_world;
    
};


//2nd layer of class structure

class MoveableActors : public BaseActor {
public:
    
    MoveableActors(int imageID, double startX, double startY, Direction dir, int depth, StudentWorld* world);
    
    virtual void doSomething() = 0; // still pure virtual, specific to most derived class
    
private:
    
};

class Environment : public BaseActor {
public:
    Environment(int imageID, double startX, double startY, Direction dir, int depth, StudentWorld* world);
    
    virtual void doSomething() = 0;
    virtual void onCollision(BaseActor *a) = 0;
    
private:
    
};


//3rd layer of class structure

//moveables

class Humans : public MoveableActors {
public:
    Humans(int imageID, double startX, double startY, Direction dir, int depth, StudentWorld* world);
    
    
    int getInfectedTotal();                     //normal because all humans will be treated the same with infection
    bool isInfected();
    virtual bool isPlayer() = 0;        // this will be reset in Penelope and Citizens class
    virtual void doSomething();  //virtual because we will reassign so all humans have same funciton
    virtual void onCollision(BaseActor *a);
    
private:
    bool m_isInfected;        // false if not infected
    int m_infectedTotal;      // 0 if not infected, increase each tick if yes
};

class Zombies : public MoveableActors {
    
public:
    
private:
    
};


//environment

class Goodies : public Environment {
    
public:
    
private:
    
};

class Permanents : public Environment {
    
public:
    
    Permanents(int imageID, double startX, double startY, Direction dir, int depth, StudentWorld *world);
    
    virtual void onCollision(BaseActor *a) = 0; //make this pure virt to keep this an ABC
    virtual void doSomething();     //this will be set to return
    
private:
    
};



//4th layer of class structure

// penelope and citizens

/*
 GraphObject(int imageID, double startX, double startY, Direction dir = 0, int depth = 0, double size = 1.0)
 : m_imageID(imageID), m_x(startX), m_y(startY), m_destX(startX), m_destY(startY),
 m_animationNumber(0), m_direction(dir), m_depth(depth), m_size(size)
 {
 if (m_size <= 0)
 m_size = 1;
 
 getGraphObjects(m_depth).insert(this);
 }
 
 
 */

class Penelope : public Humans {
    
public:
    /*Penelope will have her graph objects initialized from level  class
     so the rest will be handled accordingly
     */
    Penelope(double startX, double startY, StudentWorld* world);
    virtual bool isPlayer();        //this will be set to return true
    //virtual void doSomething();
    
private:
    int m_landmines;
    int m_vaccines;
    int m_gasCans;

    
};

class Citizens : public Humans {
public:
    virtual bool isPlayer();        // this will be set to return false
    
private:
    
};


// zombies

class DumbZombies : public Zombies {
    
public:
    
private:
    
};

class SmartZombies : public Zombies {
    
public:
    
private:
    
};


// goodies

class Vaccine : public Goodies {
    
public:
    
private:
    
};

class GasCan : public Goodies {
    
public:
    
private:
    
};

class Landmine : public Goodies {
    
public:
    
private:
    
};


// permanents

class Projectiles : public Permanents {
    
public:
    
private:
    
};

class Pits : public Permanents {
    
public:
    
private:
    
};

class Walls : public Permanents {
    
public:
    Walls(double startX, double startY, StudentWorld *world);
    virtual void onCollision(BaseActor *a);
    virtual bool canOverlap();
    
private:
    
};

class Exits : public Permanents {
    
public:
    
private:
    
};


// 5th layer (only projectiles)

class Flames : public Projectiles {
    
public:
    
private:
    
};

class Vomit : public Projectiles {
    
public:
    
private:
    
    
};


#endif // ACTOR_H_

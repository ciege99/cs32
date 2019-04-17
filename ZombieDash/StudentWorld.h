#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "GameWorld.h"
#include "Actor.h"
#include <string>
#include <list>

class Penelope;
class BaseActor;

// Students:  Add code to this file, StudentWorld.cpp, Actor.h, and Actor.cpp

class StudentWorld : public GameWorld
{
public:
    StudentWorld(std::string assetPath);
    ~StudentWorld();
    virtual int init();
    virtual int move();
    virtual void cleanUp();
    
    
    //getters
    int getHumans();    //return num of citizens
    
    bool vomitDistance(BaseActor* z);
    bool blockMovement(double newX, double newY, BaseActor* a);
    bool overlap(double newX, double newY);
   
    //finders/distance
    bool findClosestHuman(BaseActor* a, double& distTo);
    double findDistPenelope(BaseActor *a);
    double findClosestZombie(double aX, double aY);
    double findEucidDistance(double aX, double aY, double bX, double bY);
    bool setDirectionToClosest(BaseActor *a, double closestX, double closestY);
    bool randomDirSwitch(BaseActor *a, double closestX, double closestY, int n);
    
    //validators
    bool validFlamePosition(double newX, double newY);
    bool validVomitPosition(double newX, double newY);
    bool validVomitMaker(double vomitX, double vomitY, double humanX, double humanY);
    //bool validCitizenMove(BaseActor *a);
    void posSetter(Direction dir, double origX, double origY, double& posX, double& posY);
    
    //game runner functinos
    void setLevelWin();      // set game to be won
    void setStats();

    //collision functions
    void CollisionChecker(Environment *a);
    //void CollisionCaller(Environment *a, BaseActor *b);
    void infector(BaseActor *vomit, BaseActor *a);
    
    //exit
    void playerExit(BaseActor* a);
    
    //killer
    void infectedCitizenProtocol(double startX, double startY);
    void decreaseNumHumans();
    
    //creators
    void createLandmine(double startX, double startY);
    void createLandmineExplosion(double startX, double startY);
    void createFlamethrower(double startX, double startY, Direction dir);
    bool createFlame(double startX, double startY, Direction dir);
    void chanceOfVaccine(Direction dir, double origX, double origY);
    
    //adders
    bool addVaccine(BaseActor *a);
    bool addLandmines(BaseActor *a);
    bool addFlames(BaseActor *a);

private:
    Penelope *character;
    std::list<BaseActor *> actors;

    int numHumans;
    int numZombies;
    bool levelWon;

};

#endif // STUDENTWORLD_H_

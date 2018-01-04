#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"

// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp
class StudentWorld;

//Actors class
class Actor : public GraphObject
{
public:
  //Constructor
  Actor(StudentWorld *object, int imageID, int startX, int startY,
         Direction dir, int depthArg);
  
  //Destructor
  virtual ~Actor();
  
  //get a live
  bool isALive() const;
  
  //set a live
  void setALive(bool arg);
  
  //Pure virtual function
  virtual void doSomething() = 0;

 // bool blockAnt() const;
  
  //get studentworld object
  StudentWorld* getWorld() const { return world; }
  
private:
  StudentWorld *world;
  bool aLive;
};

//Insect class
class Insect : public Actor
{
public:
  //Constructor
  Insect(StudentWorld *object, int imageID, int startX, int startY,
         Direction dir, int depth);
  
  //Destructor
  virtual ~Insect();
  
  //Pure virtual function
  virtual void doSomething() = 0;
  
  //get all of those private data members
  int getHitPoints() const;
  bool isPoisoned() const;
  bool isStunned() const;
  bool isBitten() const;
  bool isHungry() const;
  
  //set all of those private data members
  void setHitPoints(int arg);
  void setIsPoisoned(bool arg);
  void setIsStunned(bool arg);
  void setIsBitten(bool arg);
  void setIsHungry(bool arg);
  
private:
  int hitPoints;
  bool poisoned;
  bool stunned;
  bool bitten;
  bool hungry;
};

//Non insect class
class NonInsect : public Actor
{
public:
  //Constructor
  NonInsect(StudentWorld *object, int imageID, int startX, int startY,
            Direction dir, int depth);
  
  //Destructor
  virtual ~NonInsect();
  
  //Pure virtual function
  virtual void doSomething() = 0;
};

//Grass Hopper class
class GrassHopper : public Insect
{
public:
  //Constructor
  GrassHopper(StudentWorld *object, int imageID, int startX, int startY, Direction dir, int depth);
  
  //Destructor
  virtual ~GrassHopper();
  
  //Do something function for baby and adult grasshopper in common
  virtual void doSomething();
  
  //get distance for grassHopper
  int getDistance() const;
  int getTicksDelayed() const;
  
  //set distance for grassHopper
  void setDistance(int arg);
  void setTicksDelayed(int arg);
  
private:
  int distance;
  int ticksDelayed;
};

//Baby grass hopper class
class BabyGrassHopper : public GrassHopper
{
public:
  //Constructor
  BabyGrassHopper(StudentWorld *object, int startX, int startY);
  
  //Destructor
  virtual ~BabyGrassHopper();
  
  //Dosomething function for only baby grassHopper
  virtual void doSomething();
};

//Pebble class
class Pebble : public NonInsect
{
public:
  //Constructor
  Pebble(StudentWorld *object, int startX, int startY);
  
  //Destructor
  virtual ~Pebble();
  
  //Dosomething for pebble returns nothing since it is a pebble
  virtual void doSomething();
};

#endif // ACTOR_H_

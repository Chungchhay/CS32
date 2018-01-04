#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "GameWorld.h"
#include <string>
#include <vector>
#include "Actor.h"

class Actor;
class Compiler;

class StudentWorld : public GameWorld
{
public:
  StudentWorld(std::string assetDir);
  virtual ~StudentWorld();
  
  virtual int init();
  virtual int move();
  virtual void cleanUp();
  //int gettick();
  void setDisplayText();

  
  // Can an insect move to x,y?
  bool canMoveTo(int x, int y);
  
  // Add an actor to the world
  void addActor(Actor* a);
  
  // If an item that can be picked up to be eaten is at x,y, return a
  // pointer to it; otherwise, return a null pointer.  (Edible items are
  // only ever going be food.)
  Actor* getEdibleAt(int x, int y) const;
  
  // Get and set tick
  int getTick() const;
  void setTick(int arg);
  void updateTickCount();
  
  // If a pheromone of the indicated colony is at x,y, return a pointer
  // to it; otherwise, return a null pointer.
  Actor* getPheromoneAt(int x, int y, int colony);
  
  // Is an enemy of an ant of the indicated colony at x,y?
  bool isEnemyAt(int x, int y, int colony);
  
  // Is something dangerous to an ant of the indicated colony at x,y?
  bool isDangerAt(int x, int y, int colony) const;
  
  // Is the anthill of the indicated colony at x,y?
  bool isAntHillAt(int x, int y, int colony) const;
  
  // Bite an enemy of an ant of the indicated colony at me's location
  // (other than me; insects don't bite themselves).  Return true if an
  // enemy was bitten.
  bool biteEnemyAt(Actor* me, int colony, int biteDamage);
  
  // Poison all poisonable actors at x,y.
  bool poisonAllPoisonableAt(int x, int y);
  
  // Stun all stunnable actors at x,y.
  bool stunAllStunnableAt(int x, int y);
  
  // Record another ant birth for the indicated colony.
  void increaseScore(int colony);
  
  //Check if an actor is blocked by a pebble or not
  bool isBlocked(Actor *q);
  
  //Check if there a food in q location
  bool isFood(Actor *q);
  
  //Check if there a food in x and y location
  Actor *isFood(int x, int y);
  
  //Get the number of ants for each anthill
  //int getAntsNum(int colony);
  
  //Remove actors from simulator when they died
  void removeActorFromSimulator();
  
  bool isPool(int x, int y);
  
  bool isPoison(int x, int y);
  
private:
  std::vector<Actor *> ary[64][64];
  int tick;
};

#endif // STUDENTWORLD_H_

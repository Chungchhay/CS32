#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"
#include "Compiler.h"

class StudentWorld;

class Actor : public GraphObject
{
public:
  Actor(StudentWorld* world, int startX, int startY, Direction startDir, int imageID, int depth);
  
  virtual ~Actor();
  
  // Action to perform each tick.
  virtual void doSomething() = 0;
  
  // Is this actor dead?
  virtual bool isDead() const;
  void setDead(bool arg);
  
  // Cause this actor to be be bitten, suffering an amount of damage.
  virtual void getBitten(int amt);
  
  // Cause this actor to be be poisoned.
  virtual void getPoisoned();
  //virtual void setPoisoned(bool arg);
  
  // Cause this actor to be be stunned.
  virtual void getStunned();
  
  // Can this actor be picked up to be eaten?
  virtual bool isEdible() const;
  void setEdible(bool arg);
  
  // Is this actor detected by an ant as a pheromone?
  bool isPheromone() const;
  void setPheromon(bool arg);
  
  int getColonies() const;
  void setColonies(int arg);
  
  // Is this actor an enemy of an ant of the indicated colony?
  virtual bool isEnemy(int colony) const;
  
  // Is this actor detected as dangerous by an ant of the indicated colony?
  virtual bool isDangerous(int colony) const;
  
  // Is this actor the anthill of the indicated colony?
  virtual bool isAntHill(int colony) const;
  
  // Get this actor's world.
  StudentWorld* getWorld() const;
  void setWorld(StudentWorld *arg);
  
private:
  StudentWorld *world;
  bool dead;
  bool edible;
  bool pheromone;
  int colonies;
};

class Pebble : public Actor
{
public:
  Pebble(StudentWorld* sw, int startX, int startY);
  virtual void doSomething();
};

class EnergyHolder : public Actor
{
public:
  EnergyHolder(StudentWorld* sw, int startX, int startY, Direction startDir, int energy, int imageID, int depth);
  
  virtual bool isDead() const;
  // Get this actor's amount of energy (for a Pheromone, same as strength).
  int getEnergy() const;
  
  // Adjust this actor's amount of energy upward or downward.
  void updateEnergy(int amt);
  
  // Add an amount of food to this actor's location.
  void addFood(int amt);
  
  int pickupFood(int amt);
  
  // Have this actor pick up an amount of food and eat it.
  int pickupAndEatFood(int amt);
  
  // Does this actor become food when it dies?
  virtual bool becomesFoodUponDeath() const;
  
private:
  int hitPoints;
};

class Food : public EnergyHolder
{
public:
  Food(StudentWorld* sw, int startX, int startY, int energy);
  virtual void doSomething();
  virtual bool isEdible() const;
};

class AntHill : public EnergyHolder
{
public:
  AntHill(StudentWorld* sw, int startX, int startY, int colony, Compiler* program);
  virtual void doSomething();
  virtual bool isMyHill(int colony) const;
  
  int getColonies() const;
  void setColonies(int arg);
  
  Compiler *getProgram() const;
  void setProgram(Compiler *arg);
  
private:
  int setID(int colony);
  int colonies;
  Compiler *m_program;
};

class Pheromone : public EnergyHolder
{
public:
  Pheromone(StudentWorld* sw, int startX, int startY, int colony);
  virtual void doSomething();
  virtual bool isPheromone(int colony) const;
  
  // Increase the strength (i.e., energy) of this pheromone.
  void increaseStrength();
  
private:
  int pickImageID(int colony);
  int m_colony;
};

class TriggerableActor : public Actor
{
public:
  TriggerableActor(StudentWorld* sw, int x, int y, int imageID);
  virtual bool isDangerous(int colony) const;
};

class WaterPool : public TriggerableActor
{
public:
  WaterPool(StudentWorld* sw, int x, int y);
  virtual void doSomething();
};

class Poison : public TriggerableActor
{
public:
  Poison(StudentWorld* sw, int x, int y);
  virtual void doSomething();
};

class Insect : public EnergyHolder
{
public:
  Insect(StudentWorld* world, int startX, int startY, int energy, int imageID);
  virtual void doSomething();
  virtual void getBitten(int amt);
  virtual void getPoisoned();
  virtual void getStunned();
  virtual bool isEnemy(int colony);
  virtual bool becomesFoodUponDeath() const;
  void setStunZero();
  
  // Increase the number of ticks this insect will sleep by the indicated amount.
  void increaseSleepTicks(int amt);
  int getSleepTicks() const;
  bool getTicksDelayed() const;
  void setTicksDelayed(int arg);
  
  bool isStunned() const;
  void setStunned(bool arg);
  
  bool isPoisoned() const;
  void setPoisoned(bool arg);
  
private:
  int bitten;
  int a, b;
  bool stunned;
  int ticksDelayed;
  bool poisoned;
  
};

class Ant : public Insect
{
public:
  Ant(StudentWorld* sw, int startX, int startY, int colony, Compiler* program, int imageID);
  virtual void doSomething();
  virtual void getBitten(int amt);
  virtual void getPoisoned();
  virtual void getStunned();
  virtual void updateIC();
  virtual int getIC();
  virtual bool isEnemy(int colony) const;
  virtual bool moveForwardIfPossible();
  
private:
  int holdFood;
  Compiler *compile;
  int col;
  int counter;
  int dis;
  int bite;
  int m_ic;
  bool bitten;
  bool blocked;
};

class Grasshopper : public Insect
{
public:
  Grasshopper(StudentWorld* sw, int startX, int startY, int energy, int imageID);
  virtual void doSomething();
  int getDistance() const;
  void setDistance(int arg);
  
private:
  int distance;
};

class BabyGrasshopper : public Grasshopper
{
public:
  BabyGrasshopper(StudentWorld* sw, int startX, int startY);
  virtual bool isEnemy(int colony) const;
  virtual void doSomething();
  virtual void getPoisoned();
};

class AdultGrasshopper : public Grasshopper
{
public:
  AdultGrasshopper(StudentWorld* sw, int startX, int startY);
  virtual void getBitten(int amt);
  virtual void doSomething();
  virtual void getStunned();
};

#endif // ACTOR_H_
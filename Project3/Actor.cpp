#include "Actor.h"
#include "StudentWorld.h"

// students:  Add code to this file (if you wish), Actor.h, StudentWorld.h, and StudentWorld.cpp

//Actors class
//Constructor
Actor::Actor(StudentWorld *object, int imageID, int startX, int startY, Direction dir, int depthArg) :
GraphObject(imageID, startX, startY, right, depthArg)
{
  world = object;
}

//Destructor
Actor::~Actor()
{
  if (world != nullptr)
    delete  world;
}

//get a live
bool Actor::isALive() const {
  return aLive;
}

//set a live
void Actor::setALive(bool arg)
{
  aLive = arg;
}

//Insect class
//Constructor
Insect::Insect(StudentWorld *object, int imageID, int startX, int startY,
               Direction dir, int depth) :
Actor(object, imageID, startX, startY, dir, depth) { }

//Destructor
Insect::~Insect()
{
  
}

//get each member data
int Insect::getHitPoints() const
{
  return hitPoints;
}

bool Insect::isPoisoned() const
{
  return poisoned;
}

bool Insect::isStunned() const
{
  return stunned;
}

bool Insect::isBitten() const
{
  return bitten;
}

bool Insect::isHungry() const
{
  return hungry;
}

//Set each member data
void Insect::setHitPoints(int arg)
{
  hitPoints = arg;
}

void Insect::setIsPoisoned(bool arg)
{
  poisoned = arg;
}

void Insect::setIsStunned(bool arg)
{
  stunned = arg;
}

void Insect::setIsBitten(bool arg)
{
  bitten = arg;
}

void Insect::setIsHungry(bool arg)
{
  hungry = arg;
}

//Non Insect Class
//Constructor
NonInsect::NonInsect(StudentWorld *object, int imageID, int startX, int startY,
                     Direction dir, int depth) :
Actor(object, imageID, startX, startY, dir, depth) {}

NonInsect::~NonInsect()
{
  
}

// Grass Hopper class
//Constructor
GrassHopper::GrassHopper(StudentWorld *object, int imageID, int startX, int startY, Direction dir, int depth) :
Insect(object, imageID, startX, startY, dir, depth) { }

//Destructor
GrassHopper::~GrassHopper()
{
  
}

void GrassHopper::doSomething()
{
  return;
}

//get each member data
int GrassHopper::getDistance() const
{
  return distance;
}

int GrassHopper::getTicksDelayed() const
{
  return ticksDelayed;
}

//set each member
void GrassHopper::setDistance(int arg)
{
  distance = arg;
}

void GrassHopper::setTicksDelayed(int arg)
{
  ticksDelayed = arg;
}


// Baby Grass Hopper class
//Constructor
BabyGrassHopper::BabyGrassHopper(StudentWorld *object, int startX, int startY) :
GrassHopper(object, IID_BABY_GRASSHOPPER, startX, startY, Direction((rand() % 4) + 1), 0)
{
  //set hit points for baby grass function
  setHitPoints(500);
  
  //First tick, baby grass has to move
  setIsStunned(false);
  
  //Obviously, it should be alive
  setALive(true);
  
  //First tick, should not be poisoned
  setIsPoisoned(false);
  
  //First tick, should not be bitten
  setIsBitten(false);
  
  //set distance for baby grass function
  setDistance((rand() % 8) + 2);
  
  //set direction for the baby grass
  //setDirection(Direction (rand() % 4));
  
  //set visible
 // setVisible(true);
}

//Destructor
BabyGrassHopper::~BabyGrassHopper()
{
  
}

//Dosomething function for only baby grassHopper
void BabyGrassHopper::doSomething()
{
  //Decrement hitpoints
  setHitPoints(getHitPoints() - 1);
  
  //if their hitpoints is 0, it is dead
  if(getHitPoints() == 0) {
    setALive(false);
    return;
  }

  //if it get stunned
  if(isStunned()) {
    setTicksDelayed(getTicksDelayed() - 1);
    if(getTicksDelayed() == 0) {
      setIsStunned(false);
    }
    return;
  }
  
  if(getHitPoints() >= 1600) {
    setALive(false);
    return;
  }
  
  if(getDistance() == 0) {
    //Set a new random direction
    setDirection(Direction((rand() % 4) + 1));
    setDistance(rand() % (8) + 2);
  }
  
  //check if nect square it block
  if(!getWorld()->isBlocked(this)) {
    if (getDirection() == up)
    {
      GraphObject::moveTo(getX() - 1, getY());
    }
    else if (getDirection() == down)
    {
      GraphObject::moveTo(getX() + 1, getY());
    }
    else if (getDirection() == left)
    {
      GraphObject::moveTo(getX(), getY() - 1);
    }
    else if (getDirection() == right)
    {
      GraphObject::moveTo(getX(), getY() + 1);
    }
    setDistance(getDistance() - 1);
  }
  else
  {
    setDistance(0);
    setDirection(Direction((rand() % 4) + 1));
  }
  
  //Sleep for two ticks
  setTicksDelayed(2);
  setIsStunned(true);

}

// Pebble class
Pebble::Pebble(StudentWorld *object, int startX, int startY) :
NonInsect(object, IID_ROCK, startX, startY, right, 1)
{
  //set visible
  setVisible(true);
}

//Destructor
Pebble::~Pebble()
{
  
}

//Dosomething for pebble returns nothing since it is a pebble
void Pebble::doSomething()
{
  return;
}

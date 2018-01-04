#include "Actor.h"
#include "StudentWorld.h"
#include <cmath>
using namespace std;

// students:  Add code to this file (if you wish), Actor.h, StudentWorld.h, and StudentWorld.cpp

//Actors class
//Constructor
Actor::Actor(StudentWorld *object, int startX, int startY, Direction dir, int imageID, int depthArg) :
GraphObject(imageID, startX, startY, right, depthArg)
{
  world = object;
}

//Destructor
Actor::~Actor()
{

}

bool Actor::isDead() const
{
  return dead;
}

void Actor::setDead(bool arg)
{
  dead = arg;
}

void Actor::getBitten(int amt)
{
 
}

void Actor::getPoisoned() { }

void Actor::getStunned() { }

bool Actor::isEdible() const
{
  return edible;
}

void Actor::setEdible(bool arg)
{
  edible = arg;
}

bool Actor::isPheromone() const
{
  return pheromone;
}

void Actor::setPheromon(bool arg)
{
  pheromone = arg;
}

int Actor::getColonies() const
{
  return colonies;
}

void Actor::setColonies(int arg)
{
  colonies = arg;
}

bool Actor::isEnemy(int colony) const
{
  if (colony != colonies)
    return true;
  
  return false;
}

bool Actor::isDangerous(int colony) const
{
  if (isEnemy(colony))
    return true;
  
  return false;
}

bool Actor::isAntHill(int colony) const
{
  if (colony == colonies)
    return true;
  
  return false;
}

StudentWorld *Actor::getWorld() const
{
  return world;
}

void Actor::setWorld(StudentWorld *arg)
{
  world = arg;
}

//Pebble class
Pebble::Pebble(StudentWorld *sw, int startX, int startY) :
Actor(sw, startX, startY, right, IID_ROCK, 1)
{

}

//Dosomething for pebble returns nothing since it is a pebble
void Pebble::doSomething()
{
  return;
}

//EnergyHolder class
EnergyHolder::EnergyHolder(StudentWorld *sw, int startX, int startY, Direction startDir, int energy, int imageID, int depth) :
Actor(sw, startX, startY, startDir, imageID, depth)
{
  hitPoints = energy;
}

bool EnergyHolder::isDead() const
{
  return Actor::isDead();
}

int EnergyHolder::getEnergy() const
{
  return hitPoints;
}

void EnergyHolder::updateEnergy(int amt)
{
  hitPoints += amt;
}

void EnergyHolder::addFood(int amt)
{
  if (getWorld()->isFood(this))
  {
    Food *food = dynamic_cast<Food *>(getWorld()->isFood(getX(), getY()));
    if (food == nullptr)
      return;
    
    food->updateEnergy(amt);
  }
  else
  {
    getWorld()->addActor(new Food(getWorld(), getX(), getY(), amt));
  }
}

int EnergyHolder::pickupAndEatFood(int amt)
{
  Food* food = dynamic_cast<Food*>(getWorld()->getEdibleAt(getX(), getY()));
  if (food == nullptr)
    return -1;
  
  if (food->getEnergy() < amt)
  {
    updateEnergy(food->getEnergy());
    food->updateEnergy(-(food->getEnergy()));
    food->setDead(true);
    return food->getEnergy();
  }
  else
  {
    updateEnergy(amt);
    food->updateEnergy(-amt);
    return amt;
  }
}

int EnergyHolder::pickupFood(int amt)
{
  Food* food = dynamic_cast<Food*>(getWorld()->getEdibleAt(getX(), getY()));
  if (food->getEnergy() < amt)
  {
    food->updateEnergy(-(food->getEnergy()));
    food->setDead(true);
    return food->getEnergy();
  }
  else
    food->updateEnergy(-amt);
  return amt;
}

bool EnergyHolder::becomesFoodUponDeath() const 
{
  return false;
}

//Food class
Food::Food(StudentWorld *sw, int startX, int startY, int energy) :
EnergyHolder(sw, startX, startY, right, energy, IID_FOOD, 2)
{
  setEdible(true);
}

void Food::doSomething()
{
  return;
}

bool Food::isEdible() const
{
  return Actor::isEdible();
}

//AntHill class
AntHill::AntHill(StudentWorld *sw, int startX, int startY, int colony, Compiler *program) :
EnergyHolder(sw, startX, startY, right, 8999, IID_ANT_HILL, 2)
{
  colonies = colony;
  m_program = program;
  setWorld(sw);
}

void AntHill::doSomething()
{
  updateEnergy(-1);
  if (getEnergy() == 0)
  {
    setDead(true);
    return;
  }
  
  pickupAndEatFood(10000);
  
//  if(getWorld()->isFood(this))
//  {
//    Food *food = dynamic_cast<Food *>(getWorld()->isFood(getX(), getY()));
//    if (food == nullptr)
//      return;
//    
//    if (food->getEnergy() > 10000)
//    {
//      pickupAndEatFood(10000);
//      food->updateEnergy(-10000);
//    }
//    else
//    {
//      pickupAndEatFood(food->getEnergy());
//      food->updateEnergy(-(food->getEnergy()));
//      food->GraphObject::setVisible(false);
//    }
//  }
  
  if (getEnergy() > 2000)
  {
    getWorld()->addActor(new Ant(getWorld(), getX(), getY(), colonies, m_program, setID(colonies)));
    updateEnergy(-1500);
  }
}

int AntHill::setID(int colony)
{
  if (colony == 0)
    return IID_ANT_TYPE0;
  else if (colony == 1)
    return IID_ANT_TYPE1;
  else if (colony == 2)
    return IID_ANT_TYPE2;
  else if (colony == 3)
    return IID_ANT_TYPE3;
  
  return -1;
}

bool AntHill::isMyHill(int colony) const
{
  if (!isEnemy(colony))
    return true;
  
  return false;
}

int AntHill::getColonies() const
{
  return colonies;
}

void AntHill::setColonies(int arg)
{
  colonies = arg;
}

Compiler *AntHill::getProgram() const
{
  return m_program;
}

void AntHill::setProgram(Compiler *arg)
{
  m_program = arg;
}

//Pheromone class
Pheromone::Pheromone(StudentWorld *sw, int startX, int startY, int colony) :
EnergyHolder(sw, startX, startY, right, 256, pickImageID(colony), 2)
{
  m_colony = colony;
}

int Pheromone::pickImageID(int colony)
{
  if (colony == 0)
    return IID_PHEROMONE_TYPE0;
  
  if (colony == 1)
    return IID_PHEROMONE_TYPE1;
  
  if (colony == 2)
    return IID_PHEROMONE_TYPE2;
  
  if (colony == 3)
    return IID_PHEROMONE_TYPE3;
  
  return -1;
}

void Pheromone::doSomething()
{
  updateEnergy(-1);
  
  if (getEnergy() == 0)
    setDead(true);
  
}

bool Pheromone::isPheromone(int colony) const
{
  if (m_colony == colony)
    return true;
  
  return false;
}

void Pheromone::increaseStrength()
{
  if ((getEnergy() + 256) <= 768)
    updateEnergy(768 - getEnergy());
}

//TriggerbleActor class
TriggerableActor::TriggerableActor(StudentWorld *sw, int x, int y, int imageID) :
Actor(sw, x, y, right, imageID, 2)
{
  
}

bool TriggerableActor::isDangerous(int colony) const
{
  if (Actor::isDangerous(colony))
    return true;
  
  return false;
}

//WaterPool class
WaterPool::WaterPool(StudentWorld *sw, int x, int y) :
TriggerableActor(sw, x, y, IID_WATER_POOL)
{
  
}

void WaterPool::doSomething()
{
  getWorld()->stunAllStunnableAt(getX(), getY());
}

//Poison class
Poison::Poison(StudentWorld *sw, int x, int y) :
TriggerableActor(sw, x, y, IID_POISON)
{
  
}

void Poison::doSomething()
{
  getWorld()->poisonAllPoisonableAt(getX(), getY());
}


//Insect class
//Constructor
Insect::Insect(StudentWorld *world, int startX, int startY, int energy, int imageID) :
EnergyHolder(world, startX, startY, Direction((rand() % 4) + 1), energy, imageID, 1)
{
  stunned = false;
}

void Insect::doSomething()
{
  return;
}

void Insect::getBitten(int amt)
{
  updateEnergy(-amt);
}

void Insect::getPoisoned(){};

void Insect::getStunned()
{
  if (stunned == false)
  {
    stunned = true;
    increaseSleepTicks(2);
  }
}

void Insect::setStunZero()
{
  stunned = false;
}

bool Insect::isEnemy(int colony)
{
  if (Actor::isEnemy(colony))
    return true;
  
  return false;
}

void Insect::increaseSleepTicks(int amt)
{
  ticksDelayed += amt;
}

int Insect::getSleepTicks() const
{
  return ticksDelayed;
}

bool Insect::becomesFoodUponDeath() const
{
  getWorld()->addActor(new Food(getWorld(), getX(), getY(), 100));
  return true;
}

bool Insect::getTicksDelayed() const
{
  return ticksDelayed;
}

void Insect::setTicksDelayed(int arg)
{
  ticksDelayed = arg;
}

bool Insect::isStunned() const
{
  return stunned;
}

void Insect::setStunned(bool arg)
{
  stunned = arg;
}

//Ant class
Ant::Ant(StudentWorld *sw, int startX, int startY, int colony, Compiler* program, int imageID) :
Insect(sw, startX, startY, 1500, colony)
{
  GraphObject::setVisible(true);
  holdFood = 0;
  setStunned(false);
  setPoisoned(false);
  compile = program;
  col = colony;
  counter = 0;
  dis = randInt(0, 8) + 1;
  bite = false;
}

void Ant::updateIC() {
  m_ic = m_ic + 1;
}
int Ant::getIC() {
  return m_ic;
}

void Ant::doSomething()
{
  updateEnergy(-1);
  
  if (getEnergy() == 0)
  {
    if (getWorld()->isFood(this))
    {
      Food *food = dynamic_cast<Food *>(getWorld()->isFood(getX(), getY()));
      if (food == nullptr)
        return;
      
      food->updateEnergy(100);
    }
    else
    {
      getWorld()->addActor(new Food(getWorld(), getX(), getY(), 100));
    }
    
    setDead(true);
    return;
  }

  setTicksDelayed(1);
  
  if(!getWorld()->isBlocked(this))
  {
    if (getDirection() == up)
    {
      GraphObject::moveTo(getX(), getY() - 1);
    }
    else if (getDirection() == down)
    {
      GraphObject::moveTo(getX(), getY() + 1);
    }
    else if (getDirection() == left)
    {
      GraphObject::moveTo(getX() - 1, getY());
    }
    else if (getDirection() == right)
    {
      GraphObject::moveTo(getX() + 1, getY());
    }
  }
  else
  {
    setDirection(Direction((rand() % 4) + 1));
  }
  
   //Represents the command, used to access different operands
   Compiler::Command cm;
  
   
   compile->getCommand(m_ic, cm);
   
   if (!compile->getCommand(m_ic, cm))
     return; // error - no such instruction!
   
   switch (cm.opcode)
   {
     case Compiler::Opcode::invalid:
     case Compiler::Opcode::label:
       break;
     case (Compiler::Opcode::moveForward):
       if(!getWorld()->isBlocked(this)) {
         blocked = false;
         bitten = false;
       } else {
         blocked = true;
       }
       //Move the ant function
       ++m_ic; // advance to next instruction
       break;
     
     case Compiler::Opcode::generateRandomNumber:
       //int x = (rand() % stoi(cm.operand1));
       ++m_ic; // advance to next instruction
       break;
       
     case Compiler::Opcode::goto_command:
       // just set ic the specified position
       // in operand1
       m_ic = stoi(cm.operand1);
       break;
     case Compiler::Opcode::faceRandomDirection:
       GraphObject::setDirection(Direction((rand() % 4) + 1));
       break;
     case Compiler::Opcode::pickupFood:
       holdFood = pickupFood(400);
       break;
     case Compiler::Opcode::eatFood:
     {
       if (holdFood<100)
       {
         updateEnergy(getEnergy());
         holdFood = 0;
       }
       else
       {
         updateEnergy(100);
         holdFood -= 100;
       }
     }
       break;
     case Compiler::Opcode::dropFood:
       if (getWorld()->isFood(this))
       {
         Food *food = dynamic_cast<Food *>(getWorld()->isFood(getX(), getY()));
         if (food == nullptr)
           return;
         
         food->updateEnergy(holdFood);
       }
       else
       {
         getWorld()->addActor(new Food(getWorld(), getX(), getY(), 100));
       }
       holdFood = 0;
       break;
     case Compiler::emitPheromone:
       //Get pheromone object
       //Pheromone::increaseStrength();
       break;
     case Compiler::rotateClockwise:
     {
       int newDir = getDirection() + 1;
       if(newDir > 4) {
         newDir = 1;
       }
       setDirection(Direction(newDir));
       break;
     }
     case Compiler::Opcode::rotateCounterClockwise:
     {
       int nDir = getDirection() - 1;
       if(nDir < 1) {
         nDir = 4;
       }
       setDirection(Direction(nDir));
       break;
     }
     case Compiler::Opcode::bite:
       if(Actor::isEdible()) {
         getWorld()->biteEnemyAt(this, getColonies(), 15);
       }
       break;

       
     case Compiler::if_command:
       switch(stoi(cm.operand1)) {
         case Compiler::i_smell_danger_in_front_of_me: break;
         case Compiler::i_smell_pheromone_in_front_of_me: break;
         case Compiler::i_was_bit: break;
         case Compiler::i_am_carrying_food: break;
         case Compiler::i_am_hungry: break;
         case Compiler::i_am_standing_on_my_anthill: break;
         case Compiler::i_am_standing_on_food: break;
         case Compiler::i_am_standing_with_an_enemy: break;
         case Compiler::i_was_blocked_from_moving: break;
         case Compiler::last_random_number_was_zero: break;
       }
       break;
       
      }
}

void Ant::getBitten(int amt)
{
  updateEnergy(amt);
  if (getEnergy() <= 0)
    setDead(true);
}

void Ant::getPoisoned()
{
  updateEnergy(-150);
}

void Ant::getStunned() {};


bool Ant::isEnemy(int colony) const
{
  if (Actor::isEnemy(colony))
    return true;
  
  return false;
}

bool Ant::moveForwardIfPossible()
{
  return true;
}

// Grass Hopper class
//Constructor
Grasshopper::Grasshopper(StudentWorld *sw, int startX, int startY, int energy, int imageID) :
Insect(sw, startX, startY, energy, imageID) { }

void Grasshopper::doSomething()
{
  
}

int Grasshopper::getDistance() const
{
  return distance;
}

void Grasshopper::setDistance(int arg)
{
  distance = arg;
}

// Baby Grass Hopper class
//Constructor
BabyGrasshopper::BabyGrasshopper(StudentWorld *sw, int startX, int startY) :
Grasshopper(sw, startX, startY, 500, IID_BABY_GRASSHOPPER)
{
  setStunned(false);
}

bool BabyGrasshopper::isEnemy(int colony) const
{
  if (Actor::isEnemy(colony))
    return true;
  
  return false;
}

void BabyGrasshopper::getPoisoned()
{
  updateEnergy(-150);
}

void BabyGrasshopper::doSomething()
{
  //Decrement hitpoints
  updateEnergy(-1);
  
  //if their hitpoints is 0, it is dead
  if(getEnergy() == 0)
  {
    //If there is an existing food, upate it, else create new one
    if (getWorld()->isFood(this))
    {
      Food *food = dynamic_cast<Food *>(getWorld()->isFood(getX(), getY()));
      if (food == nullptr)
        return;
      
      food->updateEnergy(100);
    }
    else
    {
      getWorld()->addActor(new Food(getWorld(), getX(), getY(), 100));
    }
    
    Actor::setDead(true);
    return;
  }
  
  
  if (getEnergy() > 1600)
  {
    Actor::setDead(true);
    
    if (getWorld()->isFood(this))
    {
      Food *food = dynamic_cast<Food *>(getWorld()->isFood(getX(), getY()));
      if (food == nullptr)
        return;
      
      food->updateEnergy(100);
    }
    else
    {
      getWorld()->addActor(new Food(getWorld(), getX(), getY(), 100));
    }

    getWorld()->addActor(new AdultGrasshopper(getWorld(), getX(), getY()));
    return;
  }
  
//  //if it get stunned
//  if (getWorld()->isPool(getX(), getY()))
//  {
//    if (getWorld()->stunAllStunnableAt(getX(), getY()))
//    {
//      //Insect::getStunned();
//      setTicksDelayed(getTicksDelayed() - 1);
//      if(getTicksDelayed() == 0) {
//        setStunned(false);
//      }
//    }
//    return;
//  }
//  
//  if (getWorld()->isPoison(getX(), getY()))
//  {
//    if (getWorld()->poisonAllPoisonableAt(getX(), getY()))
//    {
//      updateEnergy(-150);
//      if (getEnergy() <= 0)
//      {
//        setDead(true);
//        return;
//      }
//    }
//  }
  
  if(getDistance() == 0)
  {
    //Set a new random direction
    setDirection(Direction((rand() % 4) + 1));
    setDistance(rand() % (8) + 2);
  }
  
  
  if(getWorld()->isFood(this))
  {
    Food *food = dynamic_cast<Food *>(getWorld()->isFood(getX(), getY()));
    if (food == nullptr)
      return;
    
    if (food->getEnergy() > 200)
    {
      pickupAndEatFood(200);
      food->updateEnergy(-200);
    }
    else
    {
      pickupAndEatFood(food->getEnergy());
      food->updateEnergy(-(food->getEnergy()));
      food->GraphObject::setVisible(false);
    }
    
    int temp = randInt(0,1);
    if (temp == 0)
      setTicksDelayed(2);
  }
  
  
  //check if nect square it block
  if(!getWorld()->isBlocked(this))
  {
    if (getDirection() == up)
    {
      GraphObject::moveTo(getX(), getY() - 1);
    }
    else if (getDirection() == down)
    {
      GraphObject::moveTo(getX(), getY() + 1);
    }
    else if (getDirection() == left)
    {
      GraphObject::moveTo(getX() - 1, getY());
    }
    else if (getDirection() == right)
    {
      GraphObject::moveTo(getX() + 1, getY());
    }
    
    setDistance(getDistance() - 1);
  }
  else
  {
    setDistance(0);
    setDirection(Direction((rand() % 4) + 1));
  }
  
  setTicksDelayed(2);
  setStunned(true);
}

bool Insect::isPoisoned() const
{
  return poisoned;
}

void Insect::setPoisoned(bool arg)
{
  poisoned = arg;
}

//AdultGrasshopper class
AdultGrasshopper::AdultGrasshopper(StudentWorld *sw, int startX, int startY) :
Grasshopper(sw, startX, startY, 1600, IID_ADULT_GRASSHOPPER){}

void AdultGrasshopper::getBitten(int amt)
{
  
}
void AdultGrasshopper::getStunned(){};
void AdultGrasshopper::doSomething()
{
  //Decrement hitpoints
  updateEnergy(-1);
  
  //if their hitpoints is 0, it is dead
  if(getEnergy() == 0)
  {
    //If there is an existing food, upate it, else create new one
    if (getWorld()->isFood(this))
    {
      Food *food = dynamic_cast<Food *>(getWorld()->isFood(getX(), getY()));
      if (food == nullptr)
        return;
      
      food->updateEnergy(100);
    }
    else
    {
      getWorld()->addActor(new Food(getWorld(), getX(), getY(), 100));
    }
    
    Actor::setDead(true);
    return;
  }
  
  if (getSleepTicks() == 0)
    setTicksDelayed(2);
  else
  {
    setTicksDelayed(getSleepTicks()-1);
    return;
  }
  
//  //if it get stunned
//  if (getWorld()->isPool(getX(), getY()))
//  {
//    if (getWorld()->stunAllStunnableAt(getX(), getY()))
//    {
//      //Insect::getStunned();
//      setTicksDelayed(getTicksDelayed() - 1);
//      if(getTicksDelayed() == 0) {
//        setStunned(false);
//      }
//    }
//    return;
//  }
//  
//  if (getWorld()->isPoison(getX(), getY()))
//  {
//    if (getWorld()->poisonAllPoisonableAt(getX(), getY()))
//    {
//      updateEnergy(-150);
//      if (getEnergy() <= 0)
//      {
//        setDead(true);
//        return;
//      }
//    }
//  }
  
  if(getDistance() == 0)
  {
    setDirection(Direction((rand() % 4) + 1));
    setDistance(rand() % (8) + 2);
  }
  
  int random = randInt(0,3);
  if (random == 0)
  {
    getWorld()->biteEnemyAt(this, getColonies(), 50);
    return;
  }
  
  
  if(getWorld()->isFood(this))
  {
    Food *food = dynamic_cast<Food *>(getWorld()->isFood(getX(), getY()));
    if (food == nullptr)
      return;
    
    if (food->getEnergy() > 200)
    {
      pickupAndEatFood(200);
      food->updateEnergy(-200);
    }
    else
    {
      pickupAndEatFood(food->getEnergy());
      food->updateEnergy(-(food->getEnergy()));
      food->GraphObject::setVisible(false);
    }
    setTicksDelayed(2);
  }
  
  //check if nect square it block
  if(!getWorld()->isBlocked(this))
  {
    if (getDirection() == up)
    {
      GraphObject::moveTo(getX(), getY() - 1);
    }
    else if (getDirection() == down)
    {
      GraphObject::moveTo(getX(), getY() + 1);
    }
    else if (getDirection() == left)
    {
      GraphObject::moveTo(getX() - 1, getY());
    }
    else if (getDirection() == right)
    {
      GraphObject::moveTo(getX() + 1, getY());
    }
    
    setDistance(getDistance() - 1);
  }
  else
  {
    setDistance(0);
    setDirection(Direction((rand() % 4) + 1));
  }
  
  setTicksDelayed(2);
  setStunned(true);
}

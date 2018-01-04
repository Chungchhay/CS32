#include "StudentWorld.h"
#include "Field.h"
#include "GraphObject.h"
#include "Actor.h"
#include <string>
#include <iostream>
#include <sstream>
#include <iomanip>

//#include <sstream>  // defines the type std::ostringstream
//#include <iomanip>  // defines the manipulator setw
using namespace std;

GameWorld* createStudentWorld(string assetDir)
{
  return new StudentWorld(assetDir);
}

// Students:  Add code to this file (if you wish), StudentWorld.h, Actor.h and Actor.cpp

StudentWorld::StudentWorld(string assetDir) :
GameWorld(assetDir), tick(0)
{

}

StudentWorld::~StudentWorld()
{
  cleanUp(); //Call cleanup to clean the memory
}

//Initialize the field
int StudentWorld::init()
{
  tick = 0;
  Field f;
  std::string fieldFile = getFieldFilename();
  std::string error;
  
  Compiler *compilerForEntrant0, *compilerForEntrant1,
           *compilerForEntrant2, *compilerForEntrant3;
  
  vector<string> fileNames = getFilenamesOfAntPrograms();
  
  compilerForEntrant0 = new Compiler;
  compilerForEntrant1 = new Compiler;
  compilerForEntrant2 = new Compiler;
  compilerForEntrant3 = new Compiler;
  string error1;
  
  if (! compilerForEntrant0->compile(fileNames[0], error1))
  {
    setError(fileNames[0] + " " + error1);
    return GWSTATUS_LEVEL_ERROR;
  }
  
  AntHill *ah0, *ah1, *ah2, *ah3;
  
  if (f.loadField(fieldFile, error) != Field::LoadResult::load_success)
  {
    setError(fieldFile + " " + error);
    return false; // something bad happened!
  }
  
  for (int i = 0; i < VIEW_HEIGHT; i++)
  {
    for (int j = 0; j < VIEW_WIDTH; j++)
    {
      Field::FieldItem item = f.getContentsOf(i, j);
      switch (item)
      {//empty, anthill0, anthill1, anthill2, anthill3, food, grasshopper, water, rock, poison
        case Field::empty:
          break;
        case Field::anthill0:
          ah0 = new AntHill(this, i, j, 0, compilerForEntrant0);
          ary[i][j].push_back(ah0);
          break;
        case Field::anthill1:
          ah1 = new AntHill(this, i, j, 1, compilerForEntrant1);
          ary[i][j].push_back(ah1);
          break;
        case Field::anthill2:
          ah2 = new AntHill(this, i, j, 2, compilerForEntrant2);
          ary[i][j].push_back(ah2);
          break;
        case Field::anthill3:
          ah3 = new AntHill(this, i, j, 3, compilerForEntrant3);
          ary[i][j].push_back(ah3);
          break;
        case Field::food:
          ary[i][j].push_back(new Food(this, i, j, 6000));
          break;
        case Field::grasshopper:
          ary[i][j].push_back(new BabyGrasshopper(this, i, j));
          break;
        case Field::water:
          ary[i][j].push_back(new WaterPool(this, i, j));
          break;
        case Field::rock:
          ary[i][j].push_back(new Pebble(this, i, j));
          break;
        case Field::poison:
          ary[i][j].push_back(new Poison(this, i, j));
          break;
      }
    }
  }
  
  return GWSTATUS_CONTINUE_GAME;
}

//Move function when the main function to move other actors
int StudentWorld::move()
{
  updateTickCount();
  //setDisplayText();
  
  //if (tick > 1000)
  if (tick > 2000)
    return GWSTATUS_NO_WINNER;
  
  setGameStatText(to_string(tick));
  
  for (int i = 0; i < VIEW_HEIGHT; i++)
  {
    for (int j = 0; j < VIEW_WIDTH; j++)
    {
      for (int k = 0; k < ary[i][j].size(); k++)
      {
        ary[i][j][k]->doSomething();
      }
    }
  }
  
  
  for (int i = 0; i < VIEW_HEIGHT; i++)
  {
    for (int j = 0; j < VIEW_WIDTH; j++)
    {
      for (int k = 0; k < ary[i][j].size(); k++)
      {
        if (ary[i][j][k]->getX() == i && ary[i][j][k]->getY() == j)
          continue;
        else if (ary[i][j][k]->getX() == (i-1) && ary[i][j][k]->getY() == j)
        {
          ary[i-1][j].push_back(ary[i][j][k]);
          ary[i][j].erase(ary[i][j].begin() + k);
        }
        else if (ary[i][j][k]->getX() == (i+1) && ary[i][j][k]->getY() == j)
        {
          ary[i+1][j].push_back(ary[i][j][k]);
          ary[i][j].erase(ary[i][j].begin() + k);
        }
        else if (ary[i][j][k]->getX() == i && ary[i][j][k]->getY() == (j-1))
        {
          ary[i][j-1].push_back(ary[i][j][k]);
          ary[i][j].erase(ary[i][j].begin() + k);
        }
        else if (ary[i][j][k]->getX() == i && ary[i][j][k]->getY() == (j+1))
        {
          ary[i][j+1].push_back(ary[i][j][k]);
          ary[i][j].erase(ary[i][j].begin() + k);
        }
      }
    }
  }
  int num0 = 0;
  int num1 = 0;
  int num2 = 0;
  int num3 = 0;
  for (int i = 0; i < VIEW_HEIGHT; i++)
  {
    for (int j = 0; j < VIEW_WIDTH; j++)
    {
      for (int k = 0; k < ary[i][j].size(); k++)
      {
        if (ary[i][j][k]->getID() == IID_ANT_TYPE0)
          num0++;
        else if (ary[i][j][k]->getID() == IID_ANT_TYPE1)
          num1++;
        else if (ary[i][j][k]->getID() == IID_ANT_TYPE2)
          num2++;
        else if (ary[i][j][k]->getID() == IID_ANT_TYPE3)
          num3++;
      }
    }
  }
  ostringstream oss;
		
  oss.fill('0');
  oss << "Ticks: " << setw(2) << tick ;
  oss.fill('0');
  oss << "  AmyAnt: " << setw(2) << num0;
  oss.fill('0');
  oss << "  BillyAnt: " << setw(2) << num1;
  oss.fill('0');
  oss << "  SuzieAnt: " << setw(2) << num2;
  oss.fill('0');
  oss << "  IgorAnt: " << setw(2) << num3;
  setGameStatText(oss.str());
  
  removeActorFromSimulator();
  
  
  return GWSTATUS_CONTINUE_GAME;
}

//Delocate the memory
void StudentWorld::cleanUp()
{
  for (int i = 0; i < VIEW_HEIGHT; i++)
  {
    for (int j = 0; j < VIEW_WIDTH; j++)
    {
      for (vector<Actor*>::iterator it = ary[i][j].begin(); it != ary[i][j].end(); it++)
      {
        delete (*it);
        it = ary[i][j].erase(it);
        if (ary[i][j].empty())
          break;
      }
    }
  }
}

bool StudentWorld::canMoveTo(int x, int y)
{
  return true;
}

void StudentWorld::addActor(Actor *a)
{
  ary[a->getX()][a->getY()].push_back(a);
}
/*
Actor* StudentWorld::getEdibleAt(int x, int y) const
{
  
}*/

//get the number of the tick
int StudentWorld::getTick() const
{
  return tick;
}

//set the number of the tick
void StudentWorld::setTick(int arg)
{
  tick = arg;
}

void StudentWorld::updateTickCount()
{
  tick++;
}

//int StudentWorld::getAntsNum(int colony)
//{
//  for (int i = 0; i < VIEW_HEIGHT; i++)
//  {
//    for (int j = 0; j < VIEW_WIDTH; j++)
//    {
//      for (int k = 0; k < ary[i][j].size(); k++)
//      {
//        if (ary[i][j][k]->getID() == IID_ANT_HILL)
//        {
//          return ary[i][j][k]->getc
//        }
//      }
//    }
//  }
//}

Actor* StudentWorld::getPheromoneAt(int x, int y, int colony)
{
  Actor* ptr = nullptr;
		if (!ary[x][y].empty())
    {
      for (vector<Actor*>::iterator it = ary[x][y].begin(); it != ary[x][y].end(); it++)
        if ((*it)->isPheromone())
        {
          Pheromone* p = dynamic_cast<Pheromone*>(*it);
          if (p->isPheromone(colony))
            ptr = p;
        }
    }
		return ptr;
}

bool StudentWorld::isEnemyAt(int x, int y, int colony)
{
  if (!ary[x][y].empty())
  {
    for (vector<Actor*>::iterator it = ary[x][y].begin(); it != ary[x][y].end(); it++)
      return (*it)->isEnemy(colony);
  }
  return false;
}

bool StudentWorld::isDangerAt(int x, int y, int colony) const
{
  return true;
}

bool StudentWorld::isAntHillAt(int x, int y, int colony) const
{
  return true;
}

bool StudentWorld::biteEnemyAt(Actor *me, int colony, int biteDamage)
{
  bool temp = false;
  if (!ary[me->getX()][me->getY()].empty())
  {
    for (vector<Actor *>::iterator it = ary[me->getX()][me->getY()].begin();
         it != ary[me->getX()][me->getY()].end(); it++)
    {
      if ((*it)->isEnemy(colony))
      {
        temp = true;
        (*it)->getBitten(biteDamage);
        return temp;
      }
    }
  }
  return temp;
}

bool StudentWorld::poisonAllPoisonableAt(int x, int y)
{
  for (vector<Actor *>::iterator it = ary[x][y].begin(); it != ary[x][y].end(); it++)
  {
      (*it)->getPoisoned();
      return true;
  }
  
  return false;
}

bool StudentWorld::stunAllStunnableAt(int x, int y)
{
  for (vector<Actor *>::iterator it = ary[x][y].begin(); it != ary[x][y].end(); it++)
  {
    if ((*it)->getID() == IID_ADULT_GRASSHOPPER || (*it)->getID() == IID_BABY_GRASSHOPPER || (*it)->getID() == IID_ANT_TYPE0 || (*it)->getID() == IID_ANT_TYPE1 || (*it)->getID() == IID_ANT_TYPE2 || (*it)->getID() == IID_ANT_TYPE3) {
      (*it)->getStunned();
      return true;
    }
  }

  return false;
}

void StudentWorld::increaseScore(int colony)
{
  
}

//Check if the next move is pebble or not
bool StudentWorld::isBlocked(Actor* q)
{
  int x = q->getX();
  int y = q->getY();
  
  //Check 4 direction
  switch(q->getDirection()) {
    case GraphObject::up:
      if (!ary[x][y - 1].empty())
      {
        for (vector<Actor*>::iterator it = ary[x][y - 1].begin(); it != ary[x][y - 1].end(); it++)
        {
          if ((*it)->getID() == IID_ROCK)
            return true;
        }
      }
      break;
    case GraphObject::right:
      if (!ary[x + 1][y].empty())
      {
        for (vector<Actor*>::iterator it = ary[x + 1][y].begin(); it != ary[x + 1][y].end(); it++)
        {
          if ((*it)->getID() == IID_ROCK)
            return true;
        }
      }
      break;
    case GraphObject::down:
      if (!ary[x][y + 1].empty())
      {
        for (vector<Actor*>::iterator it = ary[x][y + 1].begin(); it != ary[x][y + 1].end(); it++)
        {
          if ((*it)->getID() == IID_ROCK)
            return true;
        }
      }
      break;
    case GraphObject::left:
      if (!ary[x - 1][y].empty())
      {
        for (vector<Actor*>::iterator it = ary[x - 1][y].begin(); it != ary[x - 1][y].end(); it++)
        {
          if ((*it)->getID() == IID_ROCK)
            return true;
        }
      }
      break;
  }
  
  return false;
}

bool StudentWorld::isFood(Actor *q)
{
  for (vector<Actor*>::iterator it = ary[q->getX()][q->getY()].begin(); it != ary[q->getX()][q->getY()].end(); it++)
  {
    if ((*it)->getID() == IID_FOOD)
      return true;
  }
  
  return false;
}

Actor *StudentWorld::getEdibleAt(int x, int y) const
{
  for (vector<Actor*>::const_iterator it = ary[x][y].cbegin(); it != ary[x][y].cend(); it++) {
    if ((*it)->getID() == IID_FOOD)
      return (*it);
  
  }
  
  return nullptr;
}

Actor *StudentWorld::isFood(int x, int y)
{
  for (vector<Actor*>::iterator it = ary[x][y].begin(); it != ary[x][y].end(); it++)
  {
    if ((*it)->getID() == IID_FOOD)
      return (*it);
  }
  
  return nullptr;
}

void StudentWorld::removeActorFromSimulator()
{
  for (int i = 0; i < VIEW_HEIGHT; i++)
  {
    for (int j = 0; j < VIEW_WIDTH; j++)
    {
      for (int k = 0; k < ary[i][j].size(); k++)
      {
        if (ary[i][j][k]->isDead() == true && ary[i][j][k]->getID() != IID_ROCK)
        {
          delete ary[i][j][k];
          ary[i][j].erase(ary[i][j].begin() + k);
        }
      }
    }
  }
}

bool StudentWorld::isPool(int x, int y)
{
  for (vector<Actor*>::iterator it = ary[x][y].begin(); it != ary[x][y].end(); it++)
  {
    if ((*it)->getID() == IID_WATER_POOL)
      return true;
  }
  
  return false;
}

bool StudentWorld::isPoison(int x, int y)
{
  for (vector<Actor*>::iterator it = ary[x][y].begin(); it != ary[x][y].end(); it++)
  {
    if ((*it)->getID() == IID_POISON)
      return true;
  }
  
  return false;
}

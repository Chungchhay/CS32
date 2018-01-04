#include "StudentWorld.h"
#include "Field.h"
#include "GraphObject.h"
#include <string>
#include <iostream>
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
  Field f;
  std::string fieldFile = getFieldFilename();
  std::string error;
  
  if (f.loadField(fieldFile, error) != Field::LoadResult::load_success)
  {
    setError(fieldFile + " " + error);
    return false; // something bad happened!
  }
  
  for (int i = 0; i < VIEW_HEIGHT; i++)
  {
    for (int j = 0; j < VIEW_WIDTH; j++)
    {
      Field::FieldItem item = f.getContentsOf(j, i);
      switch (item)
      {//empty, anthill0, anthill1, anthill2, anthill3, food, grasshopper, water, rock, poison
        case Field::empty:
          break;
        case Field::anthill0:
          break;
        case Field::anthill1:
          break;
        case Field::anthill2:
          break;
        case Field::anthill3:
          break;
        case Field::food:
          break;
        case Field::grasshopper:
          ary[i][j].push_back(new BabyGrassHopper(this, i, j));
          break;
        case Field::water:
          break;
        case Field::rock:
          ary[i][j].push_back(new Pebble(this, i, j));
          break;
        case Field::poison:
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
  
  if (tick > 2000)
    return GWSTATUS_NO_WINNER;
  
  setGameStatText(std::to_string(tick));
  
  for (int i = 0; i < VIEW_HEIGHT; i++)
  {
    for (int j = 0; j < VIEW_WIDTH; j++)
    {
      for (std::list<Actor*>::iterator it = ary[i][j].begin(); it != ary[i][j].end(); it++)
      {
        (*it)->doSomething();
      }
    }
  }
  return GWSTATUS_CONTINUE_GAME;
}

//Delocate the memory
void StudentWorld::cleanUp()
{
  for (int i = 0; i < VIEW_HEIGHT; i++)
  {
    for (int j = 0; j < VIEW_WIDTH; j++)
    {
      for (std::list<Actor*>::iterator it = ary[i][j].begin(); it != ary[i][j].end(); it++)
      {
        it = ary[i][j].erase(it);
        if (ary[i][j].empty())
          break;
      }
    }
  }
}

//Check if the next move is pebble or not
bool StudentWorld::isBlocked(Actor* q) {
  int x = q->getX();
  int y = q->getY();
  
  //Check 4 direction
  switch(q->getDirection()) {
    case GraphObject::up:
      if (!ary[x - 1][y].empty())
      {
        for (list<Actor*>::iterator it = ary[x - 1][y].begin(); it != ary[x - 1][y].end(); it++)
        {
          if ((*it)->getID() == IID_ROCK)
            return true;
        }
      }
      break;
    case GraphObject::right:
      if (!ary[x][y + 1].empty())
      {
        for (list<Actor*>::iterator it = ary[x][y + 1].begin(); it != ary[x][y + 1].end(); it++)
        {
          if ((*it)->getID() == IID_ROCK)
            return true;
        }
      }
      break;
    case GraphObject::down:
      if (!ary[x + 1][y].empty())
      {
        for (list<Actor*>::iterator it = ary[x + 1][y].begin(); it != ary[x + 1][y].end(); it++)
        {
          if ((*it)->getID() == IID_ROCK)
            return true;
        }
      }
      break;
    case GraphObject::left:
      if (!ary[x][y - 1].empty())
      {
        for (list<Actor*>::iterator it = ary[x][y - 1].begin(); it != ary[x][y - 1].end(); it++)
        {
          if ((*it)->getID() == IID_ROCK)
            return true;
        }
      }
      break;
  }
  return false;
}

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

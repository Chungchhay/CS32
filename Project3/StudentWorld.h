#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "GameWorld.h"
#include "GameController.h"
#include "SoundFX.h"
#include "Field.h"
#include <string>
#include <map>
#include <vector>
#include "Actor.h"
#include <iostream>
#include <list>

// Students:  Add code to this file, StudentWorld.cpp, Actor.h, and Actor.cpp

class StudentWorld : public GameWorld
{
public:
  StudentWorld(std::string assetDir);
  ~StudentWorld();

  virtual int init();
  virtual int move();
  virtual void cleanUp();
  bool isBlocked(Actor* q);
  
  int getTick() const;
  void setTick(int arg);
  void updateTickCount();
  
private:
  std::list<Actor*> ary[64][64];
  int tick;
};



#endif // STUDENTWORLD_H_

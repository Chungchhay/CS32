//
//  Game.h
//  Project1
//
//  Created by chungchhay kuoch on 1/10/17.
//  Copyright © 2017 chungchhay kuoch. All rights reserved.
//

#ifndef Game_h
#define Game_h

#include <string>

class Arena;

class Game
{
public:
  // Constructor/destructor
  Game(int rows, int cols, int nRats);
  ~Game();
  
  // Mutators
  void play();
  int computeDanger(const Arena& a, int r, int c);
  bool decodeDirection(char ch, int& dir);
  bool recommendMove(const Arena& a, int r, int c, int& bestDir);
  
private:
  Arena* m_arena;
  
  // Helper functions
  std::string takePlayerTurn();
};
#endif /* Game_h */
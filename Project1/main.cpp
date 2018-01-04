//
//  main.cpp
//  Project1
//
//  Created by chungchhay kuoch on 1/10/17.
//  Copyright © 2017 chungchhay kuoch. All rights reserved.
//

#include "Game.h"
#include "Arena.h"
#include "History.h"
#include "Player.h"
#include "Rat.h"
#include "globals.h"

#include <iostream>
using namespace std;

int main()
{
  // Create a game
  // Use this instead to create a mini-game:   Game g(3, 5, 2);
  Game g(10, 12, 40);
  
  // Play the game
  g.play();
  
}
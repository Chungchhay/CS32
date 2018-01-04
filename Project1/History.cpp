//
//  History.c
//  Project1
//
//  Created by chungchhay kuoch on 1/10/17.
//  Copyright © 2017 chungchhay kuoch. All rights reserved.
//

#include "History.h"
#include "globals.h"

#include <iostream>
using namespace std;

History::History(int nRows, int nCols) {
  row = nRows;
  col = nCols;
  
  for (int r = 0; r < row; r++)
    for (int c = 0; c < col; c++)
      history[r][c] = '.';
}

History::~History() {
  
}

int History::rows() const {
  return row;
}

int History::cols() const {
  return col;
}

bool History::record(int r, int c) {
  if (!(r >= 1  &&  r <= row  &&  c >= 1  &&  c <= col))
    return false;
  
  // Fill displayGrid with dots (empty)
  if (history[r - 1][c - 1] == 'Z')
    history[r - 1][c - 1] = 'Z';
  else
  {
    if (history[r - 1][c - 1] == '.')
      history[r - 1][c - 1] = 'A';
    else
      history[r - 1][c - 1] += 1;
  }
  
  return true;
}

void History::display() const {
  //Clear screen
  clearScreen();
  
  //Draw grid
  for (int r = 0; r < row; r++)
  {
    for (int c = 0; c < col; c++)
      cout << history[r][c];
    cout << endl;
  }
  cout << endl;
}

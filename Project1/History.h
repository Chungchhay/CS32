//
//  History.h
//  Project1
//
//  Created by chungchhay kuoch on 1/10/17.
//  Copyright © 2017 chungchhay kuoch. All rights reserved.
//

#ifndef History_h
#define History_h

class History
{
public:
  History(int nRows, int nCols);
  ~History();
  
  int rows() const;
  int cols() const;
  bool record(int r, int c);
  void display() const;
  
private:
  int row;
  int col;
  
  char history[20][20];
};

#endif /* History_h */

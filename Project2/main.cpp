/** 
 * Program Name: Project2
 * Written By:   Chungchhay Kuoch
 * Date:         01 25 2017
 */

#include "Sequence.h"
#include <iostream>
#include <cassert>
using namespace std;

int main()
{
  //default constructor
  Sequence s;
  //for insert sequence with 2 parameter
  assert(s.insert(0, "Two"));//first node
  assert(s.insert(0, "One"));// first node become second and this become first
  assert(s.insert(2, "Zero"));// last node
  
  //check size
  assert(s.size() == 3);
  
  //for insert sequence with 1 parameter
  assert(s.insert("Apple") == 0);//this will insert at the head node
  assert(s.insert("Zara") == s.size() - 2);//this will insert before tail node
  
  //for erase sequence
  assert(s.erase(0));//erase the first position Apple
  assert(s.erase(1));//erase the second position Two
  assert(s.size() == 3); //delete 2 nodes so size becomes 3
  assert(s.erase(0));//erase the first position
  assert(s.erase(0));//erase the first position
  assert(s.erase(0));//erase the first position
  assert(s.size() == 0); // after deleting 3 nodes size becomes 0
  
  assert(s.insert(0, "Two"));//first node
  assert(s.insert(0, "One"));// first node become second and this become first
  assert(s.remove("Two") == 1);//Two in at position 1
  assert(s.remove("nothing") == 0); //nothing to remove
  
  ItemType x;
  //for get value in the sequence
  assert(s.get(0, x) && x == "One");//check first node equal to One
  
  s.set(0, "newOne");
  assert(s.get(0, x) && x == "newOne");//set the newOne to the first node
  assert(s.size() == 1); //size is 1 at this point
  
  assert(s.find("newOne") == 0);//check if the first position is equal to newOne
  assert(s.insert(1, "newTwo"));
         
  Sequence s1;
  assert(s1.insert(0, "A"));//First node
  assert(s1.insert(1, "B"));//Second node
  s.swap(s1);
  
  // for swap value in the sequence
  assert(s.find("A") == 0);//after swaping check if s contains A and B
  assert(s.find("B") == 1);
  assert(s1.find("newOne") == 0);//after swaping check if s1 contains newOne and newTwo
  assert(s1.find("newTwo") == 1);
  
  // for assigned operator sequence
  s = s1;
  assert(s.find("newOne") == 0);//after assigning s1 to s, s should contain
                                // newOne and newTwo
  assert(s.find("newTwo") == 1);
  assert(s1.find("newOne") == 0);//s1 should stay the same
  assert(s1.find("newTwo") == 1);

  // for subsequence function
  assert(subsequence(s, s1) == 0);
  
  Sequence s2;
  assert(s2.insert(0, "Apple"));
  assert(s2.insert(1, "Banana"));
  assert(s2.insert(2, "Carrot"));
  // for interleave function
  Sequence result;
  interleave(s1, s2, result);
  assert(result.find("newOne") == 0); //result at position 0 should contain newOne
  assert(result.find("Apple") == 1);//result at position 1 should contain Apple
  assert(result.find("newTwo") == 2);//result at position 2 should contain newTwo
  assert(result.find("Banana") == 3);//result at position 3 should contain Banana
  assert(result.find("Carrot") == 4);//result at position 4 should contain Carrot
  
  // for subsequence function
  assert(subsequence(s1, s2) == -1);
  
  return 0;
}
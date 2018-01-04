/**
 * Program Name: Sequence.h
 * Written By:   Chungchhay Kuoch
 * Date:         01 25 2017
 */

#ifndef Sequence_h
#define Sequence_h
#include <string>
typedef std::string ItemType;

class Sequence
{
public:
  Sequence();
  //initial Node head to null pointer
  
  Sequence(const Sequence& arg);
  //Copy an existing sequence to another sequence
  
  ~Sequence();
  //Free the node memory
  
  bool empty() const;
  //return true if the sequence is empty, false if not
  
  int size() const;
  //return the size of the sequence
  
  bool insert(int pos, const ItemType &value);
  //insert at position pos, if sucessful, return true. False otherwise
  
  int insert(const ItemType &value);
  //insert a value <= position p
  
  bool erase(int pos);
  //erase a node at a given position
  
  int remove(const ItemType &value);
  //remove the node(s) and return the number of removed items
  
  bool get(int pos, ItemType &value) const;
  //get the node's value at a given position
  
  bool set(int pos, const ItemType &value);
  //set the node's value at a given position
  
  int find(const ItemType &value) const;
  //find a node's value equal to value and return its position
  
  void swap(Sequence &other);
  //swap 2 sequences
  
  Sequence &operator=(const Sequence &arg);
  //assigned the left existing sequence into another existing
  //sequence on the right
  
private:
  struct Node
  {
    ItemType value;
    Node *previous;
    Node *next;
  };
  
  Node *head;
  Node *tail;
  
  void addToFront(const ItemType &value);
  void addToRear(const ItemType &value);
  void addAtThisPosition(int pos, const ItemType &value);
  void deleteFront();
  void deleteRear();
  void deleteAtThisPosition(int pos);
};

int subsequence(const Sequence &seq1, const Sequence &seq2);
//if seq2 is a consecutive of seq1 it will return the earliest position
void interleave(const Sequence &seq1, const Sequence &seq2, Sequence &result);
//print first element of seq1 then first element of seq2 then continue to
//second element of seq1 and so on

#endif /* Sequence_h */

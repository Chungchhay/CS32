/**
 * Program Name: Sequence.cpp
 * Written By:   Chungchhay Kuoch
 * Date:         01 25 2017
 */

#include "Sequence.h"
// Create an empty sequence
Sequence::Sequence() : head(nullptr), tail(nullptr)
{

}

// Copy constructor. First, I have to initial head to nullptr
Sequence::Sequence(const Sequence &arg) : head(nullptr)
{
  Node *p = arg.head;
  int currPos = 0;

  // Start looping to the sequence arg while it is not empty
  // I add each value of arg to the copy of arg with a position currPos
  // increasing every time we add one value in it
  while (p != nullptr)
  {
    addAtThisPosition(currPos, p->value);
    currPos++;
    p = p->next;
  }
}

//Free the node memory
Sequence::~Sequence()
{
  // Check while the header is not empty, keep deleting it by
  // storing head to p and delete p and let head equals to head's next
  while (!empty())
  {
    Node *p = head;
    head = head->next;
    delete p;
  }
}

// Return true if the sequence is empty, otherwise false.
bool Sequence::empty() const
{
  return (head == nullptr) ? true : false;
}

// Return the number of items in the sequence.
int Sequence::size() const
{
  int count = 0;
  Node *p = head;
  
  // Checking if p is not null, increase the count
  // and return count after p hits nullptr
  while (p != nullptr)
  {
    count++;
    p = p->next;
  }
  
  return count;
}

//insert at position pos, if sucessful, return true. False otherwise
bool Sequence::insert(int pos, const ItemType &value)
{
  // Check if the pos is bigger than size, I can't add a new value
  // Pos has to be less than or equal to size
  if (pos > size() || pos < 0)
    return false;
  
  // Now I know that pos is less than or equal to size, so I add that value
  // at the given pos
  addAtThisPosition(pos, value);
  return true;
}

//insert a value <= position p
int Sequence::insert(const ItemType &value)
{
  Node *p = head;
  int currPos = 0;
  
  // Check if size equals to 0 and value <= head' value, I do not have to use
  // any loop. I'm just immediately adding the value to the front of the sequence
  if (size() == 0 || value <= p->value)
    addAtThisPosition(currPos, value);
  else
  {
    // Loop through the sequence to see if value less than or equal to each element
    // in the sequence. If it is, break the loop, and add the value at the position
    // currPos
    while (p != nullptr)
    {
      if (value <= p->value)
        break;
      
      currPos++;
      p = p->next;
    }
  
    addAtThisPosition(currPos, value);
  }
  
  // return the position where I have added
  return currPos;
}

//erase a node at a given position
bool Sequence::erase(int pos)
{
  // if size is empty or given position is bigger or equal to size, I can't erase it
  // because in order to erase any value in the sequence, pos has to be less than size
  // And pos cannot be negative, the nodes start with index of 0
  if (size() == 0 || pos >= size() || pos < 0)
    return false;

  // When pos is valid, I deleted the node at the given pos and return true
  deleteAtThisPosition(pos);
  return true;
}

//remove the node(s) and return the number of removed items
int Sequence::remove(const ItemType &value)
{
  int count = 0;
  Node *p = head;
  int currPos = 0;
  
  // Loop through all the values if the sequence to see how many nodes' value
  // have matched the given value
  while (p != nullptr)
  {
    // Check to see if it is matching or not
    if (p->value == value)
    {
      // if it is matching, I deleted the value at the current position
      deleteAtThisPosition(currPos);
      // After deleting it, I want to check the same position if it is equal
      // the value or not, because this is position replaced by a new value now
      // The reason why decrease it because after this if statement, it will add 1
      // to currPos back, so I can check at the same position
      currPos--;
      count++;
    }
    
    p = p->next;
    currPos++;
  }
  
  return count;
}

//get the node's value at a given position
bool Sequence::get(int pos, ItemType &value) const
{
  // Check if pos is valid or not, if it is not, do not do any with value and return false
  // if it is valid, go get value at pos in the sequence and store it in value
  if (size() >= 0 && pos < size() && pos >= 0)
  {
    Node *p = head;
    for (int i = 0; i < pos; i++)
      p = p->next;
    
    value = p->value;
    return true;
  }
  
  return false;
}

//set the node's value at a given position
bool Sequence::set(int pos, const ItemType &value)
{
  // Check if pos is valid or not, if it is not, do not do any with value of the sequence
  // and return false. if it is valid, go set value into the sequence
  if (size() >= 0 && pos < size() && pos >= 0)
  {
    Node *p = head;
    for (int i = 0; i < pos; i++)
      p = p->next;
    
    p->value = value;
    return true;
  }
  
  return false;
}

//find a node's value equal to value and return its position
int Sequence::find(const ItemType &value) const
{
  Node *p = head;
  int currPos = 0;
  // Loop through everything in the sequence, if the value in the sequence matches the
  // value we are looking for, return the position of it by returning currPos
  while (p != nullptr)
  {
    if (p->value == value)
      return currPos;
    
    p = p->next;
    currPos++;
  }
  
  return -1;
}

//swap 2 sequences
void Sequence::swap(Sequence &other)
{
  // Swap the address of the head node with the address of another head node
  Node *temp = head;
  head = other.head;
  other.head = temp;
}

//assigned the left existing sequence into another existing
//sequence on the right
Sequence &Sequence::operator=(const Sequence &arg)
{
  // In order to assign the sequence, delete the assigned sequence first
  while (!empty())
  {
    Node *p = head;
    head = head->next;
    delete p;
  }
  
  // Then do the same thing as I did in copy constructor
  Node *p = arg.head;
  int currPos = 0;
  
  while (p != nullptr)
  {
    addAtThisPosition(currPos, p->value);
    currPos++;
    p = p->next;
  }
  
  // And return the object of the sequence
  return *this;
}

// Add a node to the front of the sequence
void Sequence::addToFront(const ItemType &value)
{
  Node *p = new Node;
  p->previous = nullptr;
  p->value = value;
  p->next = head;
  
  // Check it the sequence is empty, if it is not empty,
  // set the head's previous points to p
  // and store p to head
  // if it is empty, head and tail are holding the same address
  // because I store p into tail and p into head
  if (!empty())
    head->previous = p;
  else
    tail = p;
  
  head = p;
}

// add a node to the last of the sequence
void Sequence::addToRear(const ItemType &value)
{
  Node *p = new Node;
  p->previous = tail;
  p->value = value;
  p->next = nullptr;
  tail->next = p;
  tail = p;
}

// add a node at the position pos with a value given
void Sequence::addAtThisPosition(int pos, const ItemType &value)
{
  // if pos equals to 0, it will call add to front function
  // if pos equals to size, it will call add to rear function
  if (pos == 0)
    addToFront(value);
  else if (pos == size())
    addToRear(value);
  else
  {
    // Now I am secured that I am in the middle of the sequence
    // So I can find the position to add by running a for loop
    Node *p = head;
    for (int i = 1; i < pos; i++)
      p = p->next;
  
    Node *n = new Node;
    n->previous = p;
    n->value = value;
    n->next = p->next;
    p->next->previous = n;
    p->next = n;
  }
}

// delete a node in the front of the sequence
void Sequence::deleteFront()
{

  Node *p = head;
  head = head->next;
  delete p;
  // Check if the sequence is not empty, do the previous to nullptr,
  // because the second node becomes the first node and I want the
  // first node previous to be nullptr
  if (!empty())
    head->previous = nullptr;
}

// Delete the last node
void Sequence::deleteRear()
{
  Node *p = tail;
  tail = tail->previous;
  tail->next = nullptr;
  delete p;
}

// delete node at position pos
void Sequence::deleteAtThisPosition(int pos)
{
  // delete the front of the sequence if position is 0 and size is 1
  // delete the end of the sequence if position is size - 1 because
  // position is always less than size by 1
  if (pos == 0 || size() == 1)
    deleteFront();
  else if (pos == size() - 1)
    deleteRear();
  else
  {
    // Loop through the position where I want to delete
    Node *p = head;
    for (int i = 1; i < pos; i++)
      p = p->next;
  
    Node *n = p->next;
    p->next = n->next;
    n->next->previous = p;
    delete n;
  }
}

//if seq2 is a consecutive of seq1 it will return the earliest position
int subsequence(const Sequence &seq1, const Sequence &seq2)
{
  int currPos1 = 0;
  int currPos2 = 0;
  int size1 = seq1.size();
  int size2 = seq2.size();
  int k = -1;
  
  // If seq1's size is smaller than seq2's size, return k and
  // do not run this loop
  while (size1 >= size2 && size2 != 0)
  {
    ItemType value1;
    ItemType value2;
    seq1.get(currPos1, value1);
    seq2.get(currPos2, value2);
    
    // Check if the value1 is equal to value2
    if (value1 == value2)
    {
      // if it is equal, let's start taking the first position of
      // consecutive sequence and stores in k
      if (currPos2 == 0)
        k = currPos1;
      
      // currPos2 is increasing because I want to check each element
      // in the sequence
      // size2-- to check if everything matches size2 will be 0, and I want
      // to stop it because I know that I already have all of the consecutive
      // numbers from seq2
      currPos2++;
      size2--;
    }
    else
    {
      // if 2 values are not equal, let currPos2 and size2 be initial values
      k = -1;
      currPos2 = 0;
      size2 = seq2.size();
    }
    
    size1--;
    currPos1++;
  }
  
  return k;
}

//print first element of seq1 then first element of seq2 then continue to
//second element of seq1 and so on
void interleave(const Sequence &seq1, const Sequence &seq2, Sequence &result)
{
  // Check if seq1 and seq2 are empty, return nothing
  if (seq1.empty() && seq2.empty())
    return;
  
  // Check if seq1 is empty, assigned seq2 to result
  if (seq1.empty())
    result = seq2;
  // Check if seq2 is empty, assigned seq1 to result
  else if (seq2.empty())
    result = seq1;
  else
  {
    if (&seq1 == &seq2)
    {
      // if those 3 sequences point to the same spot, return nothing
      if (&seq1 == &result && &seq2 == &result)
        return;
      
      // otherwise, if seq1 and seq2 (Aliasing), store either seq1 or seq2 to result
      result = seq1;
      return;
    }
    else
    {
      Sequence temp;
      int currPosResult = 0;
      int currPos1 = 0;
      int currPos2 = 0;
      
      // break the loop when both currPos reach their last node of sequence
      while (currPos1 < seq1.size() || currPos2 < seq2.size())
      {
        if (currPos1 < seq1.size())
        {
          ItemType value;
          seq1.get(currPos1, value);
          temp.insert(currPosResult, value);
          currPos1++;
          currPosResult++;
          
        }
        
        if (currPos2 < seq2.size())
        {
          ItemType value;
          seq2.get(currPos2, value);
          temp.insert(currPosResult, value);
          currPos2++;
          currPosResult++;
        }
      }
      
      result = temp;
    }
  }
}
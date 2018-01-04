// MyMap.h

// Skeleton for the MyMap class template.  You must implement the first six
// member functions.
#ifndef MYMAP_H
#define MYMAP_H

#include <iostream>
using namespace std;

template<typename KeyType, typename ValueType>

class MyMap
{
public:
	MyMap()
  {
    root = nullptr;
  }
  
	~MyMap()
  {
    clear();
  }
  
	void clear()
  {
    clearR(root);
  }

  //I used in order to count the size of the BST
  int size() const
  {
    return sizeR(root);
  }
        
	void associate(const KeyType& key, const ValueType& value)
  {
    if (root == nullptr)
    {
      root = new BST(key, value);
      return;
    }
    
    BST *curr = root;
    
    while (1)
    {
      if (curr->keyVal == key)
      {
        curr->val = value;
        return;
      }
      
      if (key < curr->keyVal)
      {
        if (curr->left != nullptr)
          curr = curr->left;
        else
        {
          curr->left = new BST(key, value);
          return;
        }
      }
      else if (key > curr->keyVal)
      {
        if (curr->right != nullptr)
          curr = curr->right;
        else
        {
          curr->right = new BST(key, value);
          return;
        }
      }
    }
  }

	  // for a map that can't be modified, return a pointer to const ValueType
	const ValueType* find(const KeyType& key) const
  {
    BST *curr = root;
    
    while (curr != nullptr)
    {
      if (curr->keyVal == key)
        return &curr->val;
      else if (key < curr->keyVal)
        curr = curr->left;
      else
        curr = curr->right;
    }
    
    return nullptr;
  }

	  // for a modifiable map, return a pointer to modifiable ValueType
	ValueType* find(const KeyType& key)
	{
		return const_cast<ValueType*>(const_cast<const MyMap*>(this)->find(key));
	}

	  // C++11 syntax for preventing copying and assignment
	MyMap(const MyMap&) = delete;
	MyMap& operator=(const MyMap&) = delete;
  
private:
  struct BST
  {
    BST *left;
    BST *right;
    KeyType keyVal;
    ValueType val;
    
    BST(KeyType key, ValueType value)
    {
      keyVal = key;
      val = value;
      left = nullptr;
      right = nullptr;
    }
  };
  BST *root;
  
  //Recursive to all the node in the tree
  void clearR(BST *curr)
  {
    if (curr == nullptr)
      return;
    
    clearR(curr->left);
    clearR(curr->right);
    delete curr;
  }
  
  int sizeR(BST *curr) const
  {
    if (curr == nullptr)
      return 0;
    else
      return(sizeR(curr->left) + 1 + sizeR(curr->right));
  }
};

#endif

#ifndef ASSIGN2_LINKEDLIST_H
#define ASSIGN2_LINKEDLIST_H

#include "Node.h"
#include <vector>
#include <iostream>

class LinkedList {
public:
  LinkedList();
  LinkedList(LinkedList &other);
  ~LinkedList();
  void push(Node* node);
  void pop();
  void swap(Node* nodeA, Node* nodeB);
  void randomInsert(Node* node);
  void insertAt(int index, Node* node);
    /* takes a list to shuffle and returns a new list, with components of passed list but shuffled*/
  void shuffle();  
  void remove(int index);
  // GETTERS
  Node* getHead();
  void setHead(Node* node);
  Node* getNode(int index);
  int size();
  void print();

protected:
  Node* head = nullptr;
};

#endif // ASSIGN2_LINKEDLIST_H

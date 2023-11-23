
#ifndef ASSIGN2_NODE_H
#define ASSIGN2_NODE_H
#include <iostream>
#include "Tile.h"

class Node {
public:
   // can used this constructor with isert
   Node(Tile* tile, Node* next);
   Node(Tile* tile); // when we are adding to the front there is no next node to add;
   Node(Node& other);
   ~Node();
   Tile* tile;
   Node* next = nullptr;
   Node* prev = nullptr;
};

#endif // ASSIGN2_NODE_H

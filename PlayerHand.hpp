#ifndef PLAYERHAND_H
#define PLAYERHAND_H
#include "LinkedList.hpp"
#include "Tile.h"
#include "TileCodes.h"
#include "Node.h"
#include <iostream>

class PlayerHand : public LinkedList {
public:
    PlayerHand();
    ~PlayerHand();
    void print(std::ostream& file);
    void add(Node* node); //sorted
    bool tileExistsInHand(Tile* tile);
    void removeNode(Node* node); 
};
#endif
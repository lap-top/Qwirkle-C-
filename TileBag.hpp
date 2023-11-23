#ifndef TILEBAG_H
#define TILEBAG_H
#include "LinkedList.hpp"
#include "Tile.h"
#include "TileCodes.h"
#include "Node.h"

class TileBag : public LinkedList{
    public:
        TileBag();
        ~TileBag();
        void fillBag();
        void print(std::ostream& file);
};
#endif
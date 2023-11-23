#ifndef BOARD
#define BOARD
#define BOARD_SIZE 6
#define BOARD_ROW 6
#define BOARD_COLUMN 6
#include <vector>
#include "Node.h"
#include <map>
#include "General.hpp"
#include "Tile.h"
#include "TileCodes.h"
#include "LinkedList.hpp"
#include "Player.hpp"
#include "TileBag.hpp"

class Board {
    public:
        Board();
        ~Board();
        Board(std::vector<std::vector<Tile*>> load);
        void print();
        int place(Tile* tile, vec2d pos);
        Tile* getTile(int x, int y);
        bool hasPosition(vec2d pos);
        bool isEmpty(vec2d pos); 
    private:
        bool firstMoveFlag = false;
        int scoreTraverseRow(Tile *tile, vec2d pos);
        int scoreTraverseCol(Tile *tile, vec2d pos);
        // char indexToAlpha;
        std::vector<std::vector<Tile*> > board;
        bool validMove(Tile* tile, vec2d pos);
        bool invalidMoveFlag = false;
};

#endif
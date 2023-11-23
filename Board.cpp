#include "Board.hpp"
#include <iostream>

#define QWIRKLE 5

Board::Board() {
    for (int i = 0; i < BOARD_SIZE; i++) {
        std::vector<Tile *> temp;
        for (int j = 0; j < BOARD_SIZE; j++) {
            temp.push_back(nullptr);
        }
        board.push_back(temp);
    }
}

Board::~Board() {
    for (int i = 0; i < BOARD_SIZE; i++) {
        for(int j = 0; j < BOARD_SIZE; j++) {
            delete board[i][j];
            board[i][j] = nullptr;
        }
    }
}

Board::Board(std::vector<std::vector<Tile*>>  load) {
    firstMoveFlag = true;
    board = load;
}

Tile* Board::getTile(int x, int y) {
    Tile* result = nullptr;
    if (x <= BOARD_SIZE || y <= BOARD_SIZE || 
        x >= 0  || y >= 0) {

        result = board[x][y];
    }  
    return result;
}

void Board::print() {

    // Draw Top
    std::cout << "  ";
    for(int i= 0; i < BOARD_SIZE; i++) {
        std::cout << " " << i << " ";
    } 
    std::cout << std::endl;

    // Horizontal Line
    std::cout << "  ";
    for(int i= 0; i < BOARD_SIZE; i++) {
         std::cout << "---";
    }
    std::cout << std::endl;

    // Main Board
    for (int row = 0; row < BOARD_SIZE; row++) {
        char temp = 65 + row;
        std::cout << temp << " |";
        for (int col = 0; col < BOARD_SIZE; col++) {
            if (board[row][col] == nullptr) {
                std::cout << "  |";
            } else {
                Colour colour = board[row][col]->getColour();
                Shape shape = board[row][col]->getShape();
                std::cout << colour << shape << "|";
            }
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

bool Board::isEmpty(vec2d pos) {
    return (board[pos.row][pos.col] == nullptr);
}

// If it's the same shape or colour it's valid and we continue
// there may be a logical error in this part, will this catch all cases???
bool Board::validMove(Tile* tile, vec2d pos) {
    return ((board[pos.row][pos.col]->getColour() == tile->colour && board[pos.row][pos.col]->getShape() != tile->shape)
    || (board[pos.row][pos.col]->getColour() != tile->colour && board[pos.row][pos.col]->getShape() == tile->shape));
}

int Board::scoreTraverseCol(Tile *tile, vec2d pos) {
    int score = 0;
    int current = pos.col - 1;
    while (invalidMoveFlag == false && current >= 0 && !isEmpty({pos.row, current})) {
        if (!validMove(tile, {pos.row, current})) {
                invalidMoveFlag = true;
        }
        score++;
        current--;
    }
       

    current = pos.col + 1;

    while (invalidMoveFlag == false && current < BOARD_SIZE && !isEmpty({pos.row, current})) {
        if (!validMove(tile, {pos.row, current})) {
                invalidMoveFlag = true;
        }
        score++;
        current++;
    }
        


    if (score == QWIRKLE) {
        score+=(QWIRKLE+1);
        std::cout << "QWIRKLE!!!" << std::endl;
    }
    return score;
}

int Board::scoreTraverseRow(Tile *tile, vec2d pos) {
    int score = 0;
    int current = pos.row - 1;
    while (invalidMoveFlag == false && current >= 0 && !isEmpty({current, pos.col})) {
            if (!validMove(tile, {current, pos.col})) {
                invalidMoveFlag = true;
            }
            score++;
            current--;
    }
    
    current = pos.row + 1;

    while (invalidMoveFlag == false && current < BOARD_SIZE && !isEmpty({current, pos.col})) {
        if (!validMove(tile, {current, pos.col})) {
            invalidMoveFlag = true;
        }
        score++;
        current++;
    }
    


    if (score == QWIRKLE) {
        score+=(QWIRKLE+1);
        std::cout << "QWIRKLE!!!" << std::endl;
    } 
    return score;
}

int Board::place(Tile* tile, vec2d pos) {
    int score = 0;
    int scoreRow = scoreTraverseRow(tile, pos);
    int scoreCol = scoreTraverseCol(tile, pos);

    if (!invalidMoveFlag) {
        if(scoreRow > 0 && scoreCol > 0) {
            score+=2;
            board[pos.row][pos.col] = tile;
        } else if (firstMoveFlag == false) { // scoreTraverse will return 0 on first move;
            firstMoveFlag = true;
            score = 1;
            board[pos.row][pos.col] = tile;
        } else if ((scoreRow == 0 && scoreCol != 0) || (scoreRow != 0 && scoreCol == 0)) {
            score++;
            board[pos.row][pos.col] = tile;
        }

        score = score + scoreRow + scoreCol;
    } else {
        invalidMoveFlag = false;
        score = 0;
    }

    return score;
}

bool Board::hasPosition(vec2d pos) {
    return (0 <= pos.col && 
            pos.col <= BOARD_SIZE &&
            0 <= pos.row && 
            pos.row <= BOARD_SIZE);
}

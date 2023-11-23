#ifndef GENERAL_H
#define GENERAL_H
#define EXIT_PROGRAM -1
#define EXIT_TO_MENU 0
#include <map>
#include <iostream>
// PROGRAM CONSTANTS // 
#define PLAYERS 2 // Amount of players
#define INVALID_NAME "-"
#define HAND_SIZE 6
struct vec2d {
    int row; int col;
};

const std::map<char, int> aToIndex = { 
{'A',0}, {'B',1}, {'C',2}, {'D',3}, {'E',4}, {'F',5}, 
{'G',6}, {'H',7}, {'I',8}, {'J',9}, {'K',10}, {'L',11}, 
{'M',12}, {'N',13}, {'O',14}, {'P',15}, {'Q',16}, {'R',17}, 
{'S',18}, {'T',19}, {'U',20}, {'V',21}, {'W',22}, {'X',23}, 
{'Y',24}, {'Z',25}, 
};

#endif
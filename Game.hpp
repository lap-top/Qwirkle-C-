#ifndef GAME_H
#define GAME_H

#include "General.hpp"
#include "TileCodes.h"
#include <iostream>
#include "TileBag.hpp"
#include "PlayerHand.hpp"
#include "Board.hpp"
#include "LinkedList.hpp"
#include "Player.hpp"
#include "Menu.hpp"
#include <iostream>
#include <iterator>

class Game {
    public:
        Game(Player* players[]);
        Game(Player* players[], Board* board, Player* currPlayer, TileBag* bag);
        ~Game();
        int runGame();
        Board* getBoard();
        TileBag* getBag();
        void setBag(TileBag* bag);
    private:
        inline void printMenu();
        TileBag* bag;
        Board* board;
        Player** players;
        Player* currPlayer;
        bool proceedProgram;
        bool areHandsEmpty();
        std::string getWord(int start, char input[20]);
        std::string getNextArg(std::string& input);
         std::vector<std::string> getArguments(std::string inputStr);
        void switchCurrPlayer();
        void saveGame(std::string fileName);
        void fillHand(PlayerHand* hand);
        int getRowInt(char ch);
        void insideGameErrorMsg(std::string error);
        
};

#endif
#ifndef MENU_H
#define MENU_H
#include "General.hpp"
#include "Player.hpp"
#include "LinkedList.hpp"
#include <map>
#include "TileCodes.h"
#include <iostream>
#include <fstream>
#include "Game.hpp"
#include "PlayerHand.hpp"
#include "TileBag.hpp"

class Menu {
  typedef void (Menu::*menuFunc)(void);
    public:
      Menu();
      ~Menu();
    private:
      std::string name[4] = {"Scott Norris", "Ledy Ledy", "Victoria Kokurin", "Sofya Filippova"};
      std::string id[4] = {"s3716716", "s3409664", "s3851213", "s3848979"};
      // Struct for menu map
      struct Option {
        char const * name;
        menuFunc func;
      };
      // variables

      std::map<std::string, Option> options;
      bool proceedProgram = true;
      std::string input = " ";
      Player* players[2];

    
      // Menu Functions
      void menuLoop();
      void initMenuFuncs();
      void initGameFuncs();
      #define CALL_MEMBER_FN(object,ptrToMember)  ((object).*(ptrToMember))
      void printMenu();
      void invoke();  

      // Option functions
      void newGame();
      void loadGame();
      void credits();
      void quit();
      // void debug();   // Debug method -> will remove at end
      // helper functions
      std::string validName(std::string name);
      std::string playerNameMenu();
      bool isFileExist(std::string fileName);
    
};

#endif
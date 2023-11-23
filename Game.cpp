#include "Game.hpp"
#include <iostream>
#include <fstream>

#define QUIT "quit"
#define SAVE "save"
#define PLACE "place"
#define REPLACE "replace"
#define TILE_PLACE_ERR "tile place error"
#define FORMAT_ERR "format error"
#define MOVE_ERR "move error"
#define TILE_REPLACE_ERR "tile replace error"
#define FILE_NAME_ERR "file name error"

Game::Game(Player* players[]) {
    this->players = players;
    board = new Board();
    bag = new TileBag();
    currPlayer = this->players[0];

    for(int i = 0; i < PLAYERS; i++) {
        fillHand(players[i]->getHand());
    }
}

Game::~Game() { 
  delete board; 
  delete bag; 
  for(int i = 0; i < PLAYERS; i++) { 
    delete players[i]; 
  } 
}

Game::Game(Player *players[], Board *board, Player *currPlayer, TileBag *bag) {
    this->players = players;
    this->board = board;
    this->currPlayer = currPlayer;
    this->bag = bag;
}

inline void Game::printMenu() {
 std::cout << currPlayer->getName() << ", it's your turn" << std::endl;
    for (int i = 0; i < PLAYERS; i++) {
        std::cout << "Score for " + players[i]->getName() + ": ";
        std::cout << players[i]->getScore() << std::endl;
    }
    
    board->print();

    std::cout << "Your hand is" << std::endl;
    currPlayer->getHand()->print(std::cout);
    std::cout << std::endl;

    std::cout << "Game Menu Options" << std::endl;
    std::cout << "-----------------" << std::endl;
    std::cout << PLACE << "\n" << REPLACE << "\n" << SAVE << "\n" << QUIT << std::endl;
    std::cout << "-----------------" << std::endl;
}

int Game::runGame() {
    char input[20];
    int exitCode = EXIT_TO_MENU;
    std::cin.getline(input, 20);     // TODO: this is to clear the input buffer, however the teacher said its a little shitty way to do it.
    proceedProgram = true;
    while (areHandsEmpty() == false && bag->size() > 0 && proceedProgram == true && !std::cin.eof()) {
        printMenu();
        std::cin.getline(input, 20);
        std::vector<std::string> args = getArguments((std::string) input);
        PlayerHand* hand = currPlayer->getHand();

        if (args.size() > 0) {
            if(args[0] == QUIT) {
              proceedProgram = false;
              exitCode = EXIT_PROGRAM;
            } else if(args[0] == SAVE && args.size() > 1) {
              saveGame(args[1]);
            } else if(args[0] == PLACE && args.size() > 2 && args[1].size() > 1 && args[3].size() > 1) {
                if (args[2] == "at") { 
                    // Argument parsing
                    Colour colour = args[1][0];
                    Shape shape = atoi(&args[1][1]);
                    Tile* tile = new Tile(colour, shape);
                    char row = args[3][0];
                    int col = atoi(&args[3][1]);
                // change here
                vec2d pos = {getRowInt(row), col};            
                if (hand->tileExistsInHand(tile) && board->hasPosition(pos)) {
                    int score = board->place(tile, pos);
                    if (score > 0) {
                        Node* inputTileNode = new Node(tile);
                        hand->removeNode(inputTileNode);
                        fillHand(hand);
                        currPlayer->addScore(score);
                        switchCurrPlayer();
                    } else {
                        insideGameErrorMsg(MOVE_ERR);
                        delete tile;
                    }
                } else {
                  insideGameErrorMsg(TILE_PLACE_ERR);
                  delete tile;
              }
            } else {
            insideGameErrorMsg(FORMAT_ERR);
            } 
          } else if(args[0] == REPLACE && args.size() > 1 && args[1].size() > 1) {
                Colour colour = args[1][0];
                Shape shape = atoi(&args[1][1]);
                Tile* tile = new Tile(colour, shape);

                if(hand->tileExistsInHand(tile)) {
                    Node* inputTileNode = new Node(tile);
                    hand->removeNode(inputTileNode);
                    bag->randomInsert(inputTileNode);
                    fillHand(hand);
                } else {
                  insideGameErrorMsg(TILE_REPLACE_ERR);
                }
                switchCurrPlayer();
              } 
            else {
                std::cout << "Unknown Function" << std::endl;
            }
        }
    }

    std::cout << "Game over" << std::endl;
    for (int i = 0; i < PLAYERS; i++) {
        std::string name = players[i]->getName();
        int score = players[i]->getScore();
        std::cout << "Score for " + name + ": " << score << std::endl;
    }
    return exitCode;
}

bool Game::areHandsEmpty() {
    for (int i = 0; i < PLAYERS; i++) {
        Player *player = players[i];
        int size = player->getHand()->size() ;
        if (size == 0) {
            return true;
        }
    }
    return false;
}

Board *Game::getBoard() {
    return board;
}


std::vector<std::string> Game::getArguments(std::string input) {
    std::vector<std::string> args;
    while (input.size() > 0) {
        std::string arg;
        int i = 0;
        for (i = 0; input[i] != ' ' && input[i] != '\0'; i++) {
            arg += (input[i]);
        }
        args.push_back(arg);
        if (input[i] == ' ') i++;
        input = input.substr(i, input.size());
    }
    return args;
}

void Game::switchCurrPlayer() {
    if (currPlayer == players[0]) {
        currPlayer = players[1];
    } else {
        currPlayer = players[0];
    }
}

void Game::saveGame(std::string fileName) {
    std::ofstream file(fileName);

    if (file.is_open()) {
        //save each player's name, score and hand
        for (int i = 0; i < PLAYERS; i++) {
            std::string name = players[i]->getName();
            int score = players[i]->getScore();
            PlayerHand* hand = players[i]->getHand();

            file << name << "\n";
            file << score << "\n";
            hand->print(file);

        }
        //save board shape
        file << BOARD_ROW << "," << BOARD_COLUMN << "\n";

        //save board state
        for (int row = 0; row < BOARD_ROW; row++) {
            for (int col = 0; col < BOARD_COLUMN; col++) {
                Tile* tile = board->getTile(row,col);
                if(tile == nullptr) {

                }
                else {
                  int ascii_offset = 65;
                    Colour colour = tile->getColour();
                    Shape shape = tile->getShape();
                    char row_char = row + ascii_offset;

                    file << colour << shape << "@" << row_char << col << ", ";
                }  
            }
        }
        file << "\n";

        //save tile bag contents
        bag->print(file);
        
        //save current player's name
        file << currPlayer->getName();
        file.close();
    }
    std::cout << "Game has been saved successfully." << std::endl;
}

TileBag *Game::getBag() {
    return this->bag;
}

void Game::setBag(TileBag *bag) {
    this->bag = bag;
}

void Game::fillHand(PlayerHand* hand) {
    int handSize = hand->size(); 
    while (bag->size() != 0 && handSize < HAND_SIZE) {
        Node* node = new Node(bag->getHead()->tile); 

        // TODO: this add method returns a segmentation fault, when the hand size is 0.
        hand->add(node);
        bag->pop();
        handSize++;
    }
}


int Game::getRowInt(char c) {
    int result = -1;
    if (std::isalpha(c) ) {
        result = aToIndex.at(std::toupper(c));
    }
    return result;  
}

void Game::insideGameErrorMsg(std::string error) {
  std::cout << "-----------------" << std::endl;
  std::cout << "ERROR - TRY AGAIN" << std::endl;
  std::cout << "-----------------" << std::endl;
  std::cout << "--- MAKE SURE ---\n" << std::endl;
  if (error == TILE_PLACE_ERR) {
    std::cout << " - make sure your input is of the format:" << "\n" 
              << "place [tile colour][tile shape] at [existing board letter][existing board number]" << "\n" << std::endl;
    std::cout << "- your tile exists in your hand" << std::endl; 
    std::cout << "\n" << "- you are not replacing an existing tile. Make sure the spot on the board you're trying to fill is empty " << "\n" << std::endl;
    std::cout << "----------------------------------------------------" << std::endl;
  } else if (error == TILE_REPLACE_ERR) {
    std::cout << " - make sure your input is of the format:" << "\n" 
              << "replace [tile colour][tile shape]" << "\n" << std::endl;
    std::cout << "- your tile exists in your hand" << std::endl; 
  } else if (error == FORMAT_ERR) {
    std::cout << "\n" << " - make sure your input is of the format:" << "\n" 
    << "place [tile colour][tile shape] at [existing board letter][existing board number]" << "\n" << std::endl;
  } else if (error == MOVE_ERR) {
    std::cout << "- you're playing a valid move" << std::endl;
  } else if(error == FILE_NAME_ERR){
      std::cout << "- you use a valid filename" << std::endl;
  } else {
    std::cout << "- you evaluate your move" << std::endl;
  }
std::cout<<std::endl;
}

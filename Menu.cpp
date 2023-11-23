#include "Menu.hpp"

#define EMAIL_DOMAIN "@student.rmit.edu.au"

Menu::Menu() {
    initMenuFuncs();
    menuLoop();
    std::string name[4];
    std::string id[4];
}

Menu::~Menu() {
  
}

#define CALL_MEMBER(object, ptrToMember, key) ((object)->*(ptrToMember.at(key).func))
void Menu::invoke() {
    if (options.count(input) > 0) {
        // Call the mapped function
        CALL_MEMBER(this, options, input)
        ();
    }
    else {
        std::cout << "Incorrect Input" << std::endl;
    }
}

void Menu::printMenu() {
    std::cout << "Menu" << std::endl
              << "----" << std::endl;
    for (const auto &item : options) {
        std::cout << item.first << ". " << item.second.name << std::endl;
    }
    std::cout << "> ";
}


//initialise menu
void Menu::initMenuFuncs()
{
    options = {
        {"1", {"New Game", &Menu::newGame}},
        {"2", {"Load Game", &Menu::loadGame}},
        {"3", {"Credits", &Menu::credits}},
        {"4", {"Quit", &Menu::quit}}
    };
}

void Menu::menuLoop() {
    std::cout << "Welcome to Qwirkle!" << std::endl
              << "-------------------" << std::endl;
    while (proceedProgram && !std::cin.eof()) {
        printMenu();
        std::cin >> input;
        invoke();
    }
}

/*** MENU OPTIONS ***/
void Menu::newGame()
{
    std::cout << "Starting a New Game" << std::endl;
    std::string playerNames[2];
    for (int i = 0; i < PLAYERS; i++) {
        std::cout << "Enter a name for player " << i + 1 << " (alphabetical characters only)" << std::endl
                  << "> ";
        std::string name = playerNameMenu();
        players[i] = new Player(i, name, 0);
    }

    std::cout << std::endl;
    std::cout << "Let's Play!" << std::endl;

    Game* game = new Game(players);

    if (game->runGame() == EXIT_PROGRAM) {
        this->quit();
    }
    delete game;

}

//check if file is valid
bool Menu::isFileExist(std::string fileName) {
    bool result;
    std::ifstream file;
    file.open(fileName);
    if (file) {
        result = true;
    }
    else {
        result = false;
    }
    file.close();
    return result;
}

void Menu::loadGame() {

    std::string fileName;
    std::cout << "Enter the filename from which load a game \n> ";
    std::cin >> fileName;

    if (isFileExist(fileName) == true) {
        // open file
        std::ifstream file;
        file.open(fileName);

        std::string message;
        int line_counter = 0;
        int index = 0;
        std::string message_array[10];

        // read file
        while (!file.eof()) {
            std::getline(file, message);
            message_array[index] = message;
            line_counter++;
            index++;
        }

        //Load player's id, name and score
        Player *player1 = new Player(1, message_array[0], stoi(message_array[1]));
        Player *player2 = new Player(2, message_array[3], stoi(message_array[4]));
        players[0] = player1;
        players[1] = player2;

        //Load hands for each player
        std::string hands[2] = {message_array[2], message_array[5]};
        Colour colour = 'N';
        Shape shape = 0;

        for (int i = 0; i < PLAYERS; i++) {
            //convert string into c-style string
            char *handCstring;
            handCstring = &(hands[i])[0];
            PlayerHand *hand = new PlayerHand();

            for (unsigned int j = 0; j < hands[i].length() ; j++) {
                //check if the even index of the handCstring[] is an alphabet
                if (isalpha(handCstring[j])) {
                    colour = handCstring[j];
                }
                //check if the odd index of the handCstring[] is a digit
                else if (isdigit(handCstring[j])) {
                    shape = handCstring[j] - '0';
                    hand->push(new Node(new Tile(colour, shape)));
                }
                players[i]->setHand(hand);
            }
        }

        //Load board shape (but do we need this though since we always know that it is 6x6)
        std::string board_shape = message_array[6];

        //Load board state

        std::string boardString = message_array[7];
        char *boardCstring;
        boardCstring = &boardString[0];

        char row = '$';
        int col;
        vec2d pos;

        // init the board;
        std::vector<std::vector<Tile *> > boardState;
        for (int i = 0; i < BOARD_SIZE; i++) {
            std::vector<Tile *> temp;
            for (int j = 0; j < BOARD_SIZE; j++) {
                temp.push_back(nullptr);
            }
            boardState.push_back(temp);
        }
        for (unsigned int i = 0; i < boardString.length(); i++)
        {
            //extract just the letter
            int ascii_offset = 65;
            int length_line = 7;
            if (isalpha(boardCstring[i])) {
                if (i % length_line == 0) {
                    colour = boardCstring[i];
                }
                else if (i % length_line == 3) {
                    row = boardCstring[i];
                }
            }
            else if (isdigit(boardCstring[i]))
            {
                if (i % length_line == 1) {
                    shape = atoi(&boardCstring[i]);
                }
                else if (i % length_line == 4) {
                    col = atoi(&boardCstring[i]);
                    pos = {(row - ascii_offset), col};
                    boardState[pos.row][pos.col] = new Tile(colour, shape);
                }
            }
        }
        Board *board = new Board(boardState);

        // Load Bag Contents
        std::string bagString = message_array[8];
        char *bagCstring;
        bagCstring = &bagString[0];

        TileBag *bag = new TileBag();
        for (unsigned int i = 0; i < bagString.length(); i++) {
            if (isalpha(bagCstring[i])) {
                colour = bagCstring[i];
            }
            if (isdigit(bagCstring[i])) {
                shape = bagCstring[i] - '0';
                Tile *tile = new Tile(colour, shape);
                bag->push(new Node(tile));
            }
        }

        //Load current player's name
        std::string currPlayerName = message_array[9];
        Player *currPlayer;
        if (currPlayerName == player1->getName()) {
            currPlayer = player1;
        }
        else {
            currPlayer = player2;
        }

        Game *game = new Game(players, board, currPlayer, bag);
        
        if (game->runGame() == EXIT_PROGRAM) {
            this->quit();
        }
        file.close();
        delete game;
    }
    else if (std::cin.eof()) {
        quit();
    }
    else if (isFileExist(fileName) == false) {
        std::cout << "File does not exist! Please try again!" << std::endl;
        loadGame();
    }
}

void Menu::credits() {
    std::cout << "--------------------------------" << std::endl;
    std::cout << "THANKS FOR PLAYING QWIRKLE WITH US" << std::endl;

    std::cout << "the makers of: "
              << "\n"
              << std::endl;

    for (int i = 0; i < 4; i++) {
        std::cout << "Name: " << name[i] << std::endl;
        std::cout << "Student ID: " << id[i] << std::endl;
        std::cout << "Email: " << id[i] << EMAIL_DOMAIN << std::endl;
        std::cout << std::endl;
    }
    std::cout << "-------------------------------" << std::endl;
}

void Menu::quit() {
    std::cout << "Goodbye" << std::endl;
    proceedProgram = false;
}

/*** HELPER FUNCTIONS FOR OPTIONS ***/
std::string Menu::validName(std::string name)
{
    bool isInvalid = false;
    for (int c = 0; c < (int)name.length() && !isInvalid; c++) {
        if (std::isalpha(name[c])) { // is it alphabetical character
            if (!std::isupper(name[c])) {
                name[c] = std::toupper(name[c]);
            }
        }
        else {
            name = INVALID_NAME;
            isInvalid = true;
        }
    }
    return name;
}

std::string Menu::playerNameMenu() {
    std::string name;
    name = INVALID_NAME;
    while (name == INVALID_NAME) {
        std::cin >> name;
        name = validName(name);
    };
    return name;
}

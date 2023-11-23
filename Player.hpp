#ifndef PLAYER_H
#define PLAYER_H
#include <string>
#include "LinkedList.hpp"
#include "PlayerHand.hpp"

class Player {
    public:
        Player();
        ~Player();
        Player(int id, std::string name, int score);
        
        bool move();
        PlayerHand* getHand();
        std::string getName();
        int getScore();
        void addScore(int score);
        void setHand(PlayerHand* hand);

    private:
        int id;
        std::string name;
        int score;
        PlayerHand* hand;
};
#endif
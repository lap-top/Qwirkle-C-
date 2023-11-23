#include "Player.hpp"
#include <iostream>

Player::Player(int id, std::string name, int score) {
    this->name = name;
    this->score = score;
    this->id = id;
    hand = new PlayerHand();
}

Player::~Player() { 
  delete hand; 
}

bool Player::move() {
    return false;
}

PlayerHand* Player::getHand() {
    return hand;
}

void Player::setHand(PlayerHand* hand) {
    this->hand = hand;
}

std::string Player::getName() {
    return name;
}

int Player::getScore() {
    return score;
}
void Player::addScore(int score) {
    this->score +=score;
}

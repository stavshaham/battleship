#include "Player.h"

Player::Player(string name) {
    this->name = name;
    this->board = new Board();
}

Board &Player::getBoard() {
    return *this->board;
}

Player::~Player() {
    delete this->board;
}

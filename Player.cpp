//
// Created by Stav Shaham on 11/2/26.
//

#include "Player.h"

Player::Player(string name) {
    this->name = name;
    this->board = new Board();
}

Board &Player::getBoard() {
    return *this->board;
}

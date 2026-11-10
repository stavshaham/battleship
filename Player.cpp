// Implements the common functionality for Battleship players.
#include "Player.h"

// Creates a player and dynamically allocates the player's board.
Player::Player(string name) {
    this->name = name;
    this->board = new Board();
}

// Returns the board belonging to this player.
Board &Player::getBoard() {
    return *this->board;
}

// Releases the dynamically allocated board.
Player::~Player() {
    delete this->board;
}

// Declares the human-controlled player for the Battleship game.
#ifndef BATTLESHIP_HUMANPLAYER_H
#define BATTLESHIP_HUMANPLAYER_H
#include "Player.h"

// Represents a player who enters attack coordinates through the keyboard.
class HumanPlayer : public Player {
public:
    // Creates a human player with the specified name.
    HumanPlayer(string name);

    // Reads and performs one attack entered by the human player.
    void makeMove(Board& opponentBoard) override;
};

#endif //BATTLESHIP_HUMANPLAYER_H
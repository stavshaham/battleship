// Declares the computer-controlled player for the Battleship game.
#ifndef BATTLESHIP_AIPLAYER_H
#define BATTLESHIP_AIPLAYER_H
#include "Player.h"

// Represents a player whose moves are selected randomly by the program.
class AIPlayer : public Player {
public:
    // Creates an AI player with the specified name.
    AIPlayer(string name);

    // Makes one random attack on the opponent's board.
    void makeMove(Board& opponentBoard) override;
};


#endif //BATTLESHIP_AIPLAYER_H

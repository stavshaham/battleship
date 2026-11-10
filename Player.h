// Declares the base class shared by human and AI players.
#ifndef BATTLESHIP_PLAYER_H
#define BATTLESHIP_PLAYER_H
#include <string>

#include "Board.h"

using namespace std;

// Stores the common name and board used by every type of player.
class Player {
private:
    string name;
    Board *board;

public:
    // Creates a player with the specified name and a new board.
    Player(string name);

    // Makes a move against the opponent's board.
    virtual void makeMove(Board& opponentBoard) = 0;

    // Returns this player's board.
    Board& getBoard();

    // Releases the board owned by this player.
    virtual ~Player();
};

#endif //BATTLESHIP_PLAYER_H

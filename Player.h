#ifndef BATTLESHIP_PLAYER_H
#define BATTLESHIP_PLAYER_H
#include <string>

#include "Board.h"

using namespace std;

class Player {
private:
    string name;
    Board *board;

public:
    Player(string name);
    virtual void makeMove() = 0;
    Board& getBoard();
};

#endif //BATTLESHIP_PLAYER_H

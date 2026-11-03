#ifndef BATTLESHIP_AIPLAYER_H
#define BATTLESHIP_AIPLAYER_H
#include "Player.h"


class AIPlayer : public Player {
public:
    AIPlayer(string name);
    void makeMove(Board& opponentBoard) override;
};


#endif //BATTLESHIP_AIPLAYER_H

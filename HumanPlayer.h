//
// Created by Stav Shaham on 11/2/26.
//

#ifndef BATTLESHIP_HUMANPLAYER_H
#define BATTLESHIP_HUMANPLAYER_H
#include "Player.h"


class HumanPlayer : public Player {
public:
    HumanPlayer(string name);
    void makeMove(Board& opponentBoard) override;
};


#endif //BATTLESHIP_HUMANPLAYER_H

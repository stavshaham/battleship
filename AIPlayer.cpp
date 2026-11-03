#include <iostream>
#include "Board.h"
#include "AIPlayer.h"

void AIPlayer::makeMove(Board& opponentBoard) {
    bool moveCompleted = false;

    while (!moveCompleted) {
        int row = rand() % SIZE;
        int col = rand() % SIZE;

        if (opponentBoard.validAttack(row, col)) {
            bool hit = opponentBoard.recordAttack(row, col);

            if (hit) {
                std::cout << "AI hit your ship!\n";
            } else {
                std::cout << "AI missed.\n";
            }

            moveCompleted = true;
        }
    }
}
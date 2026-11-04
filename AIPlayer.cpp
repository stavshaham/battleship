#include <iostream>
#include "Board.h"
#include "AIPlayer.h"

using namespace std;

AIPlayer::AIPlayer(string name) : Player(name) {}

void AIPlayer::makeMove(Board& opponentBoard) {
    bool moveCompleted = false;

    while (!moveCompleted) {
        int row = rand() % SIZE;
        int col = rand() % SIZE;

        if (opponentBoard.validAttack(row, col)) {
            bool hit = opponentBoard.recordAttack(row, col);

            if (hit) {
                cout << "AI hit your ship!\n";
            } else {
                cout << "AI missed.\n";
            }

            moveCompleted = true;
        }
    }
}

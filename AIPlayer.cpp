#include <iostream>
#include "Board.h"
#include "AIPlayer.h"

using namespace std;

const std::string RESET = "\033[0m";
const std::string RED = "\033[31m"; // For hits (X)
const std::string YELLOW = "\033[33m"; // For misses (O)

AIPlayer::AIPlayer(string name) : Player(name) {}

void AIPlayer::makeMove(Board& opponentBoard) {
    bool moveCompleted = false;

    while (!moveCompleted) {
        int row = rand() % SIZE;
        int col = rand() % SIZE;

        if (opponentBoard.validAttack(row, col)) {
            bool hit = opponentBoard.recordAttack(row, col);

            if (hit) {
                cout << "AI "<< RED <<"hit your ship!\n";
                cout << RESET << ' ';
            } else {
                cout << "AI "<< YELLOW <<"missed.\n";
                cout << RESET << ' ';
            }

            moveCompleted = true;
        }
    }
}

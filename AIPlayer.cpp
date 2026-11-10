// Implements the computer-controlled Battleship player.
#include <iostream>
#include "Board.h"
#include "AIPlayer.h"

using namespace std;

const string RESET = "\033[0m";
const string RED = "\033[31m"; // For hits (X)
const string YELLOW = "\033[33m"; // For misses (O)

// Creates an AI player and initializes the inherited Player portion.
AIPlayer::AIPlayer(string name) : Player(name) {}

// Chooses a random valid coordinate and attacks the opponent's board.
void AIPlayer::makeMove(Board& opponentBoard) {
    bool moveCompleted = false;

    while (!moveCompleted) {
        int row = rand() % SIZE;
        int col = rand() % SIZE;

        if (opponentBoard.validAttack(row, col)) {
            bool hit = opponentBoard.recordAttack(row, col);

            if (hit) {
                cout << "AI "<< RED <<"hit your ship!" << endl;
                cout << RESET << ' ';
            } else {
                cout << "AI "<< YELLOW <<"missed." << endl;
                cout << RESET << ' ';
            }

            moveCompleted = true;
        }
    }
}

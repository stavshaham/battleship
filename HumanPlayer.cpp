#include "HumanPlayer.h"
#include <iostream>

using namespace std;

void HumanPlayer::makeMove(Board& opponentBoard) {
    bool moveCompleted = false;

    while (!moveCompleted) {
        char rowLetter;
        int col;

        cout << "Enter an attack coordinate, such as A 3: ";
        cin >> rowLetter >> col;

        rowLetter = toupper(rowLetter);
        int row = rowLetter - 'A';

        if (!opponentBoard.validAttack(row, col)) {
            cout << "Invalid move. Try again.\n";
        } else {
            bool hit = opponentBoard.recordAttack(row, col);

            if (hit) {
                cout << "Hit!\n";
            } else {
                cout << "Miss!\n";
            }

            moveCompleted = true;
        }
    }
}
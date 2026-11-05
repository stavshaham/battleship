#include "HumanPlayer.h"
#include <iostream>
#include <cctype>
#include <climits>

using namespace std;

const std::string RESET = "\033[0m";
const std::string RED = "\033[31m"; // For hits (X)
const std::string YELLOW = "\033[33m"; // For misses (O)


HumanPlayer::HumanPlayer(string name) : Player(name) {}

void HumanPlayer::makeMove(Board& opponentBoard) {
    bool moveCompleted = false;

    while (!moveCompleted) {
        char rowLetter;
        int col;

        cout << "Enter an attack coordinate, such as A 3: ";

        if (!(cin >> rowLetter >> col)) {
            if (cin.eof()) {
                cout << "\nInput stream closed. Exiting game.\n";
                return;
            }

            cin.clear();
            cin.ignore(INT_MAX, '\n');

            cout << "Invalid input. Enter a letter and a number.\n";
            continue; // Goes back to the beginning of the loop
        }

        rowLetter = toupper(rowLetter);
        int row = rowLetter - 'A';

        if (!opponentBoard.validAttack(row, col)) {
            cout << "Invalid move. Try again.\n";
        } else {
            bool hit = opponentBoard.recordAttack(row, col);

            if (hit) {
                cout << RED<<"Hit!\n";
                cout << RESET << ' ';
            } else {
                cout << YELLOW<<"Miss!\n";
                cout << RESET << ' ';
            }

            moveCompleted = true;
        }
    }
}

#include "HumanPlayer.h"
#include <iostream>
#include <climits>

using namespace std;

const string RESET = "\033[0m";
const string RED = "\033[31m"; // For hits (X)
const string YELLOW = "\033[33m"; // For misses (O)

// Creates a human player and initializes the inherited Player portion.
HumanPlayer::HumanPlayer(string name) : Player(name) {}

// Reads an attack coordinate, validates it, and records the attack.
void HumanPlayer::makeMove(Board& opponentBoard) {
    bool moveCompleted = false;

    while (!moveCompleted) {
        char rowLetter;
        int col;

        cout << "Enter an attack coordinate, such as A 3: ";

        if (!(cin >> rowLetter >> col)) {
            if (cin.eof()) {
                cout << endl << "Input stream closed. Exiting game." << endl;
                return;
            }

            cin.clear();
            cin.ignore(INT_MAX, '\n');

            cout << "Invalid input. Enter a letter and a number." << endl;
            continue; // Goes back to the beginning of the loop
        }

        rowLetter = toupper(rowLetter);
        int row = rowLetter - 'A';

        if (!opponentBoard.validAttack(row, col)) {
            cout << "Invalid move. Try again." << endl;
        } else {
            bool hit = opponentBoard.recordAttack(row, col);

            if (hit) {
                cout << RED<<"Hit!" << endl;
                cout << RESET << ' ';
            } else {
                cout << YELLOW<<"Miss!" << endl;
                cout << RESET << ' ';
            }

            moveCompleted = true;
        }
    }
}

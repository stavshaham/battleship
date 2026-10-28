#include <iostream>
#include "Board.h"

using namespace std;

// Prints a short message saying whether an edge case worked
void report(const string& action, bool result) {
    cout << action << ": " << (result ? "yes" : "no") << '\n';
}

int main() {
    Board board;

    cout << "=== Empty board ===\n";
    cout << board << '\n';

    // Test cases
    cout << "=== Placing ships ===\n";
    report("Place carrier (5) at A0, horizontal",
           board.placeShip(0, 0, 5, Orientation::Horizontal));

    // These should all fail
    report("Place battleship (4) at A8, horizontal (off the board)",
           board.placeShip(0, 8, 4, Orientation::Horizontal));
    report("Place cruiser (3) at A2, vertical (overlaps carrier)",
           board.placeShip(0, 2, 3, Orientation::Vertical));
    report("Place a second carrier (5) at J0 (none left)",
           board.placeShip(9, 0, 5, Orientation::Horizontal));
    report("Place a ship of length 7 (invalid size)",
           board.placeShip(5, 5, 7, Orientation::Horizontal));

    // The rest of the fleet
    report("Place battleship (4) at C3, vertical",
           board.placeShip(2, 3, 4, Orientation::Vertical));
    report("Place cruiser (3) at H1, horizontal",
           board.placeShip(7, 1, 3, Orientation::Horizontal));
    report("Place submarine (3) at E7, vertical",
           board.placeShip(4, 7, 3, Orientation::Vertical));
    report("Place destroyer (2) at J8, horizontal",
           board.placeShip(9, 8, 2, Orientation::Horizontal));

    report("All ships placed?", board.allShipsPlaced());
    cout << '\n' << board << '\n';

    cout << "=== Attacks ===\n";
    report("Attack A2 (hit?)", board.recordAttack(0, 2));
    report("Attack F0 (hit?)", board.recordAttack(5, 0));
    report("Attack A2 again (hit?)", board.recordAttack(0, 2));
    report("Attack outside the board (hit?)", board.recordAttack(12, 3));
    report("All ships sunk?", board.allSunk());
    cout << '\n' << board << '\n';

    cout << "=== Attacking every cell ===\n";
    for (int r = 0; r < SIZE; r++) {
        for (int c = 0; c < SIZE; c++) {
            board.recordAttack(r, c);
        }
    }
    report("All ships sunk?", board.allSunk());
    cout << '\n' << board << '\n';

    return 0;
}
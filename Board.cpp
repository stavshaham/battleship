// Prints the board while hiding unhit ships.
#include "Board.h"
#include <iostream>
#include <string>

using namespace std;

const string RESET = "\033[0m";
const string BLUE = "\033[34m"; // For ocean water (~)
const string RED = "\033[31m"; // For hits (X)
const string GREEN = "\033[32m"; // For your own healthy ships
const string YELLOW = "\033[33m"; // For misses (O)

// Creates a board whose cells all initially contain water.
Board::Board() {
    for (int r = 0; r < SIZE; r++) {
        for (int c = 0; c < SIZE; c++) {
            grid[r][c] = CellType::Water;
        }
    }
}

// Checks whether the specified row and column are within the board.
bool Board::inBounds(int row, int col) const {
    return row >= 0 && row < SIZE && col >= 0 && col < SIZE;
}

// Returns the remaining-ship counter associated with a ship length.
// Returns a pointer to the counter for ships of this length, or nullptr if invalid
int* Board::remainingFor(int length) {
    switch (length) {
        case 5: return &shipsOfFive;
        case 4: return &shipsOfFour;
        case 3: return &shipsOfThree;
        case 2: return &shipsOfTwo;
        default: return nullptr;
    }
}

// Checks whether every cell required by a ship is available.
bool Board::canPlace(int row, int col, int length, Orientation dir) const {
    for (int i = 0; i < length; i++) {
        int r = row + (dir == Orientation::Vertical ? i : 0);
        int c = col + (dir == Orientation::Horizontal ? i : 0);
        if (!inBounds(r, c) || grid[r][c] != CellType::Water) {
            return false;
        }
    }
    return true;
}

// Places a ship and decreases the remaining count for its length.
bool Board::placeShip(int row, int col, int length, Orientation dir) { 
    //Check whether this ship length is valid
    int* remaining = remainingFor(length);

    if (remaining == nullptr || *remaining <= 0) {
        return false;
    }

    //Check whether the ship fits and does not overlap
    if (!canPlace(row, col, length, dir)) {
        return false;
    }

    //Place the ship
    for (int i = 0; i < length; i++) {
        int r = row;
        int c = col;

        if (dir == Orientation::Horizontal) {
            c += i;
        } else {
            r += i;
        }

        grid[r][c] = CellType::Ship;
    }

    //Update the number of ships remaining to place
    (*remaining)--;

    return true;
}

// Randomly places the five ships in the standard fleet.
// Randomly choosing ship place direction
void Board::randomlyPlaceFleet() {
    int shipLengths[] = {5, 4, 3, 3, 2};

    for (int i = 0; i < 5; i++) {
        bool placed = false;

        while (!placed) {
            int row = rand() % SIZE;
            int col = rand() % SIZE;

            int direction = rand() % 2;

            Orientation dir;

            if (direction == 0) {
                dir = Orientation::Horizontal;
            } else {
                dir = Orientation::Vertical;
            }

            placed = placeShip(row, col, shipLengths[i], dir);
        }
    }
}

// Records a hit or miss at the requested coordinate.
// Returns true on a hit, false on a miss, repeat shot, or out-of-bounds shot
bool Board::recordAttack(int row, int col) {
    if (!inBounds(row, col)) return false;

    CellType& cell = grid[row][col];
    if (cell == CellType::Ship) {
        cell = CellType::Hit;
        return true;
    }
    if (cell == CellType::Water) {
        cell = CellType::Miss;
    }
    return false;
}

// Reports whether all required ships have been placed.
bool Board::allShipsPlaced() const {
    return shipsOfFive + shipsOfFour + shipsOfThree + shipsOfTwo == 0;
}

// Reports whether every ship cell has been hit.
bool Board::allSunk() const {
    for (int r = 0; r < SIZE; r++) {
        for (int c = 0; c < SIZE; c++) {
            if (grid[r][c] == CellType::Ship) return false;
        }
    }
    return true;
}

// Prints the border used around a board display.
void printBorder(ostream& os) {
    os << "  +";

    for (int i = 0; i < SIZE * 2 + 1; i++) {
        os << '-';
    }

    os << "+" << endl;
}

// Checks whether a coordinate contains an un attacked water or ship cell.
bool Board::validAttack(int row, int col) const {
    if (!inBounds(row, col)) {
        return false;
    }

    return grid[row][col] == CellType::Water ||
           grid[row][col] == CellType::Ship;
}

// Prints the board with the option to reveal or hide ships.
void Board::printBoard(ostream& output, bool showShips) const {
    output << "    ";

    for (int col = 0; col < SIZE; col++) {
        output << col << ' ';
    }

    output << endl;

    printBorder(output);

    for (int row = 0; row < SIZE; row++) {
        char rowLetter = 'A' + row;

        output << rowLetter << " | ";

        for (int col = 0; col < SIZE; col++) {
            switch (grid[row][col]) {
                case CellType::Water:
                    output << BLUE << '~';
                    break;

                case CellType::Ship:
                    if (showShips) {
                        output << GREEN << 'S';
                    } else {
                        output << BLUE << '~';
                    }
                    break;

                case CellType::Hit:
                    output << RED << 'X';
                    break;

                case CellType::Miss:
                    output << YELLOW << 'O';
                    break;
            }

            output << RESET << ' ';
        }

        output << "|" << endl;
    }

    printBorder(output);
}

// Prints a version of the board that hides unhit ships.
void Board::printHidden(ostream& output) const {
    printBoard(output, false);
}

// Prints the complete board through the stream insertion operator.
ostream& operator<<(ostream& output, const Board& board) {
    board.printBoard(output, true);
    return output;
}
#include "Board.h"
#include <iostream>
#include <cstdlib>

using namespace std;

const std::string RESET = "\033[0m";
const std::string BLUE = "\033[34m"; // For ocean water (~)
const std::string RED = "\033[31m"; // For hits (X)
const std::string GREEN = "\033[32m"; // For your own healthy ships
const std::string YELLOW = "\033[33m"; // For misses (O)

Board::Board() {
    for (int r = 0; r < SIZE; r++) {
        for (int c = 0; c < SIZE; c++) {
            grid[r][c] = CellType::Water;
        }
    }
}

bool Board::inBounds(int row, int col) const {
    return row >= 0 && row < SIZE && col >= 0 && col < SIZE;
}

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

bool Board::placeShip(int row, int col, int length, Orientation dir) { //CHANGED
    // Check whether this ship length is valid
    int* remaining = remainingFor(length);

    if (remaining == nullptr || *remaining <= 0) {
        return false;
    }

    // Check whether the ship fits and does not overlap
    if (!canPlace(row, col, length, dir)) {
        return false;
    }

    // Place the ship
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

    // Update the number of ships remaining to place
    (*remaining)--;

    return true;
}

void Board::randomlyPlaceFleet() { //ADDED FUNCTION 
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

bool Board::allShipsPlaced() const {
    return shipsOfFive + shipsOfFour + shipsOfThree + shipsOfTwo == 0;
}

bool Board::allSunk() const {
    for (int r = 0; r < SIZE; r++) {
        for (int c = 0; c < SIZE; c++) {
            if (grid[r][c] == CellType::Ship) return false;
        }
    }
    return true;
}

void printBorder(ostream& os) {
    os << "  +";

    for (int i = 0; i < SIZE * 2 + 1; i++) {
        os << '-';
    }

    os << "+\n";
}

ostream& operator<<(ostream& os, const Board& board) {
    // Column numbers
    os << "    ";
    for (int c = 0; c < SIZE; c++) {
        os << c << ' ';
    }
    os << '\n';

    printBorder(os);

    for (int r = 0; r < SIZE; r++) {
        char letter = 'A' + r;
        os << letter << " | ";
        for (int c = 0; c < SIZE; c++) {
            switch (board.grid[r][c]) {
                case CellType::Water:
                    os << BLUE   << '~';
                    break;
                case CellType::Ship:
                    os << GREEN  << 'S';
                    break;
                case CellType::Hit:
                    os << RED    << 'X';
                    break;
                case CellType::Miss:
                    os << YELLOW << 'O';
                    break;
            }

            os << RESET << ' ';
        }
        os << "|\n";
    }

    printBorder(os);
    return os;
}

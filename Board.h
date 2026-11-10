// Declares the Battleship board and its ship and attack operations.

#ifndef BATTLESHIP_BOARD_H
#define BATTLESHIP_BOARD_H
#define SIZE 10

#include <iosfwd>
#include "CellType.h"
#include "Orientation.h"

using namespace std;

// Represents a 10-by-10 Battleship board.
class Board {
private:
    CellType grid[SIZE][SIZE];
    int shipsOfFive = 1;
    int shipsOfFour = 1;
    int shipsOfThree = 2;
    int shipsOfTwo = 1;

    // Checks whether a coordinate is inside the board.
    bool inBounds(int row, int col) const;

    // Checks whether a ship can fit without leaving the board or overlapping.
    bool canPlace(int row, int col, int length, Orientation dir) const;

    // Returns the counter for the requested ship length.
    int* remainingFor(int length);

    // Prints the board while optionally showing ships.
    void printBoard(ostream& output, bool showShips) const;

public:
    // Creates a board initialized with water cells.
    Board();

    // Places a ship if the requested location and length are valid.
    bool placeShip(int row, int col, int length, Orientation dir);

    // Records an attack and returns whether it hit a ship.
    bool recordAttack(int row, int col);

    // Reports whether all ships have been placed.
    bool allShipsPlaced() const;

    // Reports whether no unhit ships remain.
    bool allSunk() const;

    // Randomly places the standard fleet on the board.
    void randomlyPlaceFleet();

    // Reports whether a coordinate can be attacked.
    bool validAttack(int row, int col) const;

    // Prints the visible board using the stream insertion operator.
    friend ostream& operator<<(ostream& os, const Board& board);

    // Prints the board while hiding unhit ships.
    void printHidden(ostream& output) const;
};

#endif //BATTLESHIP_BOARD_H
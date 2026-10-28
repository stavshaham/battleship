#ifndef BATTLESHIP_BOARD_H
#define BATTLESHIP_BOARD_H
#define SIZE 10
#include <iosfwd>
#include "CellType.h"
#include "Orientation.h"

class Board {
private:
    CellType grid[SIZE][SIZE];
    int shipsOfFive = 1;
    int shipsOfFour = 1;
    int shipsOfThree = 2;
    int shipsOfTwo = 1;

    bool inBounds(int row, int col) const;
    bool canPlace(int row, int col, int length, Orientation dir) const;
    int* remainingFor(int length);

public:
    Board();
    bool placeShip(int row, int col, int length, Orientation dir);
    bool recordAttack(int row, int col);
    bool allShipsPlaced() const;
    bool allSunk() const;
    friend std::ostream& operator<<(std::ostream& os, const Board& board);
};

#endif //BATTLESHIP_BOARD_H
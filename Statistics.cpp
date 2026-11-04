#include "Statistics.h"
#include <fstream>
#include <iostream>

Statistics::Statistics(const std::string& fileName)
    : gamesPlayed(0),
      wins(0),
      losses(0),
      fileName(fileName) {
}

void Statistics::load() {
    std::ifstream inputFile(fileName);

    if (inputFile) {
        inputFile >> gamesPlayed >> wins >> losses;
    }
}

bool Statistics::save() const {
    std::ofstream outputFile(fileName);

    if (!outputFile) {
        return false;
    }

    outputFile << gamesPlayed << '\n';
    outputFile << wins << '\n';
    outputFile << losses << '\n';

    return true;
}

void Statistics::recordWin() {
    gamesPlayed++;
    wins++;
}

void Statistics::recordLoss() {
    gamesPlayed++;
    losses++;
}

void Statistics::display(std::ostream& output) const {
    output << "\n=== Statistics ===\n";
    output << "Games played: " << gamesPlayed << '\n';
    output << "Wins: " << wins << '\n';
    output << "Losses: " << losses << '\n';
}
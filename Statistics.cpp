// Implements loading, saving, updating, and displaying game statistics.
#include "Statistics.h"
#include <fstream>
#include <iostream>

// Creates an empty statistics record associated with a file.
Statistics::Statistics(const string& fileName) : gamesPlayed(0), wins(0), losses(0), fileName(fileName) {}

// Loads games played, wins, and losses from the statistics file.
void Statistics::load() {
    ifstream inputFile(this->fileName);

    if (inputFile) {
        inputFile >> this->gamesPlayed >> this->wins >> this->losses;
    }
}

// Saves the current statistics values to the statistics file.
bool Statistics::save() const {
    ofstream outputFile(this->fileName);

    if (!outputFile) {
        return false;
    }

    outputFile << this->gamesPlayed << endl;
    outputFile << this->wins << endl;
    outputFile << this->losses << endl;

    return true;
}

// Increments the games played and wins counters.
void Statistics::recordWin() {
    this->gamesPlayed++;
    this->wins++;
}

// Increments the games played and losses counters.
void Statistics::recordLoss() {
    this->gamesPlayed++;
    this->losses++;
}

// Displays the current statistics using the supplied output stream.
void Statistics::display(ostream& output) const {
    output << endl << "=== Statistics ===" << endl;
    output << "Games played: " << this->gamesPlayed << endl;
    output << "Wins: " << this->wins << endl;
    output << "Losses: " << this->losses << endl;
}
// Declares the statistics record used to track a player's game results.
#ifndef BATTLESHIP_STATISTICS_H
#define BATTLESHIP_STATISTICS_H

#include <iosfwd>
#include <string>

using namespace std;

// Stores games played, wins, losses, and the file used for persistence.
class Statistics {
private:
    int gamesPlayed;
    int wins;
    int losses;
    string fileName;

public:
    // Creates a statistics record using the specified file.
    Statistics(const string& fileName = "stats.txt");

    // Loads statistics from the record file.
    void load();

    // Saves statistics to the record file and reports success or failure.
    bool save() const;

    // Records one completed game as a win.
    void recordWin();

    // Records one completed game as a loss.
    void recordLoss();

    // Prints the current statistics to the supplied output stream.
    void display(ostream& output) const;
};

#endif //BATTLESHIP_STATISTICS_H

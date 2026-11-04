#ifndef BATTLESHIP_STATISTICS_H
#define BATTLESHIP_STATISTICS_H

#include <iosfwd>
#include <string>

using namespace std;

class Statistics {
private:
    int gamesPlayed;
    int wins;
    int losses;
    string fileName;

public:
    Statistics(const string& fileName = "stats.txt");

    void load();
    bool save() const;

    void recordWin();
    void recordLoss();

    void display(std::ostream& output) const;
};

#endif //BATTLESHIP_STATISTICS_H

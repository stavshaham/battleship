#include <iostream>
#include <cstdlib>
#include <ctime>
#include <climits>
#include <sstream>
#include <iomanip>
#include <vector>
#include <string>
#include <algorithm>
#include "Board.h"
#include "Statistics.h"
#include "HumanPlayer.h"
#include "AIPlayer.h"

using namespace std;

const std::string RESET = "\033[0m";
const std::string BLUE = "\033[34m";
const std::string PINK ="\033[95m";
const string BROWN = "\033[38;5;130m";
const string WHITE = "\033[37m";

void displayTitle() {
    cout<< PINK <<"__        __   _                            _ "<<endl;
    cout<<"\\ \\      / /__| | ___ ___  _ __ ___   ___  | |_ ___ "<<endl;
    cout<<" \\ \\ /\\ / / _ \\ |/ __/ _ \\| '_ ` _ \\ / _ \\ | __/ _ \\ "<<endl;
    cout<<"  \\ V  V /  __/ | (_| (_) | | | | | |  __/ | || (_) |"<<endl;
    cout<<" __\\_/\\_/ \\___|_|\\___\\___/|_| |_|_|_|\\___|  \\__\\___/ "<<endl;
    cout<<"| __ )  __ _| |_| |_| | ___  ___| |__ (_)_ __   "<<endl;
    cout<<"|  _ \\ / _` | __| __| |/ _ \\//__| '_ \\| | '_ \\ "<<endl;
    cout<<"| |_) | (_| | |_| |_| |  __/\\__ \\ | | | | |_) |"<<endl;
    cout<<"|____/ \\__,_|\\__|\\__|_|\\___||___/_| |_|_| .__/"<<endl;
    cout<<"                                        |_| "<<endl;
    cout << RESET << ' ';

    cout <<BROWN << "                 |    |    |                         \n";
    cout <<WHITE<< "                )_)  )_)  )_)                        \n";
    cout << "               )___))___))___)                       \n";
    cout <<WHITE<< "              )____)____)_____)"<<BROWN<<"\\                    \n";
    cout << "            _____|____|____|____\\\\__                \n";
    cout <<BLUE<< "   ---------"<<BROWN<<"\\                   /"<<BLUE<<"---------           \n";
    cout <<BLUE << "     ^^^^^ ^^^^^^^^^^^^^^^^^^^^^                     \n";
    cout << "       ^^^^      ^^^^     ^^^^^^                     \n\n";
    cout << RESET << ' ';
}

void displayMenu() {
    cout << "\n==== Main Menu ==== " << endl;
    cout << "1. Player Against AI" << endl;
    cout << "2. Player Against Another Player" << endl;
    cout << "3. View Statistics" << endl;
    cout << "4. Exit" << endl;
    cout << "Choose an option: " << endl;
}


void displayBoardsSideBySide(Board& boardOne, bool hiddenOne,
                             string titleOne,
                             Board& boardTwo, bool hiddenTwo,
                             string titleTwo) {

    // Capture the first board
    ostringstream outputOne;

    if (hiddenOne) {
        boardOne.printHidden(outputOne);
    } else {
        outputOne << boardOne;
    }

    // Capture the second board
    ostringstream outputTwo;

    if (hiddenTwo) {
        boardTwo.printHidden(outputTwo);
    } else {
        outputTwo << boardTwo;
    }

    // Convert captured output into input streams
    istringstream inputOne(outputOne.str());
    istringstream inputTwo(outputTwo.str());

    string lineOne;
    string lineTwo;

    // Print titles
    cout << "\n" << titleOne << "                 " << titleTwo << endl;

    // Print both boards side by side
    while (true) {

        bool hasFirst = static_cast<bool>(getline(inputOne, lineOne));
        bool hasSecond = static_cast<bool>(getline(inputTwo, lineTwo));

        if (!hasFirst && !hasSecond) {
            break;
        }

        cout << left << lineOne << "          " << lineTwo << endl;
    }
}
int playGame(Player& playerOne, Player& playerTwo, bool showPlayerTwoBoard) {
    playerOne.getBoard().randomlyPlaceFleet();
    playerTwo.getBoard().randomlyPlaceFleet();

    int winner = 0;

    while (winner == 0) {

        // Display Player 1's boards side by side
        displayBoardsSideBySide(
            playerOne.getBoard(), false, "Player 1's Board",
            playerTwo.getBoard(), true, "Player 1's Attack Board"
        );

        cout << "\nPlayer 1's turn.\n";
        playerOne.makeMove(playerTwo.getBoard());

        if (playerTwo.getBoard().allSunk()) {
            winner = 1;
        } 
        else {

            // Display Player 2's boards side by side
            if (showPlayerTwoBoard) {

                displayBoardsSideBySide(
                    playerTwo.getBoard(), false, "Player 2's Board",
                    playerOne.getBoard(), true, "Player 2's Attack Board"
                );
            }

            cout << "\nPlayer 2's turn.\n";
            playerTwo.makeMove(playerOne.getBoard());

            // Show Player 2's attacks against Player 1
            if (!showPlayerTwoBoard) {
                cout << "\nPlayer 2's Attack Board\n";
                playerOne.getBoard().printHidden(cout);
            }

            if (playerOne.getBoard().allSunk()) {
                winner = 2;
            }
        }
    }

    cout << "\nPlayer " << winner << " wins!\n";
    return winner;
}

void updateStatistics(Statistics& statistics, int winner) {
    if (winner == 1) {
        statistics.recordWin();
    } else {
        statistics.recordLoss();
    }

    if (!statistics.save()) {
        cout << "Could not save statistics.\n";
    } else {
        cout << "Statistics saved.\n";
    }
}

int main() {
    int choice;

    //Seed the random number generator
    srand(time(NULL));

    // Loading stats
    Statistics statistics;
    statistics.load();

    //Display screen 
    displayTitle();
    displayMenu();

    cin >> choice;

    // Checking cin is valid
    while (!cin) {
        cin.clear();
        cin.ignore(INT_MAX, '\n');
        cout << "Please enter a number.\n";
        cin >> choice;
    }

    while (choice) {
        int winner = 0;
        switch (choice) {
            // Adding a scope to avoid variables jumping from case to case
            case 1: {
                HumanPlayer human("Player");
                AIPlayer ai("Computer");

                winner = playGame(human, ai, false);
                updateStatistics(statistics, winner);
                break;
            }

            case 2: {
                HumanPlayer playerOne("Player 1");
                HumanPlayer playerTwo("Player 2");

                winner = playGame(playerOne, playerTwo, true);
                updateStatistics(statistics, winner);
                break;
            }

            case 3: {
                statistics.display(cout);
                break;
            }

            case 4:
                cout << "\nExiting the game." << endl;
                return 0;
                break;

            default:
                cout << "Invalid choice." << endl;
                break;
        }

        displayMenu();
        cin >> choice;

        // Checking cin is valid
        while (!cin) {
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            cout << "Please enter a number.\n";
            cin >> choice;
        }
    }

    return 0;
}

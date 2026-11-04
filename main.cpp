#include <iostream>
#include <cstdlib>
#include <ctime>
#include <climits>
#include "Board.h"
#include "Statistics.h"
#include "HumanPlayer.h"
#include "AIPlayer.h"

using namespace std;

void displayTitle() {
    cout<<"__        __   _                            _ "<<endl;
    cout<<"\\ \\      / /__| | ___ ___  _ __ ___   ___  | |_ ___ "<<endl;
    cout<<" \\ \\ /\\ / / _ \\ |/ __/ _ \\| '_ ` _ \\ / _ \\ | __/ _ \\ "<<endl;
    cout<<"  \\ V  V /  __/ | (_| (_) | | | | | |  __/ | || (_) |"<<endl;
    cout<<" __\\_/\\_/ \\___|_|\\___\\___/|_| |_|_|_|\\___|  \\__\\___/ "<<endl;
    cout<<"| __ )  __ _| |_| |_| | ___  ___| |__ (_)_ __   "<<endl;
    cout<<"|  _ \\ / _` | __| __| |/ _ \\//__| '_ \\| | '_ \\ "<<endl;
    cout<<"| |_) | (_| | |_| |_| |  __/\\__ \\ | | | | |_) |"<<endl;
    cout<<"|____/ \\__,_|\\__|\\__|_|\\___||___/_| |_|_| .__/"<<endl;
    cout<<"                                        |_| "<<endl;

    cout << "                 |    |    |                         \n";
    cout << "                )_)  )_)  )_)                        \n";
    cout << "               )___))___))___)                       \n";
    cout << "              )____)____)_____)\\                    \n";
    cout << "            _____|____|____|____\\\\__                \n";
    cout << "   ---------\\                   /---------           \n";
    cout << "     ^^^^^ ^^^^^^^^^^^^^^^^^^^^^                     \n";
    cout << "       ^^^^      ^^^^     ^^^^^^                     \n\n";
}

void displayMenu() {
    cout << "==== Main Menu ==== " << endl;
    cout << "1. Player Against AI" << endl;
    cout << "2. Player Against Another Player" << endl;
    cout << "3. View Statistics" << endl;
    cout << "4. Exit" << endl;
    cout << "Choose an option: " << endl;
}

int playGame(Player& playerOne, Player& playerTwo, bool showPlayerTwoBoard) {
    playerOne.getBoard().randomlyPlaceFleet();
    playerTwo.getBoard().randomlyPlaceFleet();

    int winner = 0;

    while (winner == 0) {
        // Show Player 1's own board
        cout << "\n=== Player 1's Board ===\n";
        cout << playerOne.getBoard();

        // Show Player 1's attacks on Player 2's board
        cout << "\n=== Player 1's Attack Board ===\n";
        playerTwo.getBoard().printHidden(cout);

        cout << "\nPlayer 1's turn.\n";
        playerOne.makeMove(playerTwo.getBoard());

        if (playerTwo.getBoard().allSunk()) {
            winner = 1;
        } else {
            // Show Player 2's own board only in human-versus-human mode
            if (showPlayerTwoBoard) {
                cout << "\n=== Player 2's Board ===\n";
                cout << playerTwo.getBoard();
            }

            cout << "\nPlayer 2's turn.\n";
            playerTwo.makeMove(playerOne.getBoard());

            // Show Player 2's attacks on Player 1's board
            cout << "\n=== Player 2's Attack Board ===\n";
            playerOne.getBoard().printHidden(cout);

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

    while (choice != 4) {
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
                cout << "Exiting the game." << endl;
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

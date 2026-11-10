// Runs the Battleship game, account menu, game modes, and statistics display.
#include <iostream>
#include <climits>
#include <sstream>
#include <vector>
#include <string>
#include "Board.h"
#include "Statistics.h"
#include "HumanPlayer.h"
#include "AIPlayer.h"
#include "UserManager.h"

using namespace std;

const string RESET = "\033[0m";
const string BLUE = "\033[34m";
const string PINK = "\033[95m";
const string BROWN = "\033[38;5;130m";
const string WHITE = "\033[37m";

// Displays the colored Battleship title and decorative ship artwork.
void displayTitle() {
    cout << PINK << "__        __   _                            _ " << endl;
    cout << "\\ \\      / /__| | ___ ___  _ __ ___   ___  | |_ ___ " << endl;
    cout << " \\ \\ /\\ / / _ \\ |/ __/ _ \\| '_ ` _ \\ / _ \\ | __/ _ \\ " << endl;
    cout << "  \\ V  V /  __/ | (_| (_) | | | | | |  __/ | || (_) |" << endl;
    cout << " __\\_/\\_/ \\___|_|\\___\\___/|_| |_|_|_|\\___|  \\__\\___/ " << endl;
    cout << "| __ )  __ _| |_| |_| | ___  ___| |__ (_)_ __   " << endl;
    cout << "|  _ \\ / _` | __| __| |/ _ \\//__| '_ \\| | '_ \\ " << endl;
    cout << "| |_) | (_| | |_| |_| |  __/\\__ \\ | | | | |_) |" << endl;
    cout << "|____/ \\__,_|\\__|\\__|_|\\___||___/_| |_|_| .__/" << endl;
    cout << "                                        |_| " << endl;
    cout << RESET << ' ';

    cout << BROWN << "                 |    |    |                         " << endl;
    cout << WHITE << "                )_)  )_)  )_)                        " << endl;
    cout << "               )___))___))___)                       " << endl;
    cout << WHITE << "              )____)____)_____)"
         << BROWN << "\\                    \n";
    cout << "            _____|____|____|____\\\\__                " << endl;
    cout << BLUE << "   ---------" << BROWN << "\\                   /"
         << BLUE << "---------           \n";
    cout << BLUE << "     ^^^^^ ^^^^^^^^^^^^^^^^^^^^^                     " << endl;
    cout << "       ^^^^      ^^^^     ^^^^^^                     " << endl << endl;
    cout << RESET << ' ';
}

// Displays the available game and statistics menu options.
void displayMenu() {
    cout << endl << "==== Main Menu ==== " << endl;
    cout << "1. Player Against AI" << endl;
    cout << "2. Player Against Another Player" << endl;
    cout << "3. View Statistics" << endl;
    cout << "4. Exit" << endl;
    cout << "Choose an option: " << endl;
}

// Captures two board displays and prints them next to each other.
void displayBoardsSideBySide(Board& boardOne, bool hiddenOne, string titleOne, Board& boardTwo, bool hiddenTwo, string titleTwo) {

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
    cout << endl << titleOne << "                 " << titleTwo << endl;

    // Print both boards side by side
    bool hasFirst = true;
    bool hasSecond = true;

    while (hasFirst || hasSecond) {
        hasFirst = static_cast<bool>(getline(inputOne, lineOne));
        hasSecond = static_cast<bool>(getline(inputTwo, lineTwo));

        if (hasFirst || hasSecond) {
            cout << left << (hasFirst ? lineOne : "") << "          " << (hasSecond ? lineTwo : "") << endl;
        }
    }
}

// Runs a complete game between two players and returns the winning player number.
int playGame(Player& playerOne, Player& playerTwo, bool showPlayerTwoBoard) {
    playerOne.getBoard().randomlyPlaceFleet();
    playerTwo.getBoard().randomlyPlaceFleet();

    int winner = 0;

    while (winner == 0) {

        // Display Player 1's boards side by side
        displayBoardsSideBySide(playerOne.getBoard(), false, "Player 1's Board",playerTwo.getBoard(), true, "Player 1's Attack Board");

        cout << endl << "Player 1's turn." << endl;
        playerOne.makeMove(playerTwo.getBoard());

        if (playerTwo.getBoard().allSunk()) {
            winner = 1;
        }
        else {

            // Display Player 2's boards side by side
            if (showPlayerTwoBoard) {
                displayBoardsSideBySide(playerTwo.getBoard(), false, "Player 2's Board",playerOne.getBoard(), true, "Player 2's Attack Board");
            }

            cout << endl << "Player 2's turn." << endl;
            playerTwo.makeMove(playerOne.getBoard());

            // Show Player 2's attacks against Player 1
            if (!showPlayerTwoBoard) {
                cout << endl << "Player 2's Attack Board" << endl;
                playerOne.getBoard().printHidden(cout);
            }

            if (playerOne.getBoard().allSunk()) {
                winner = 2;
            }
        }
    }

    cout << endl << "Player " << winner << " wins!" << endl;
    return winner;
}

// Updates and saves the current user's statistics after a completed game.
void updateStatistics(Statistics& statistics, int winner) {
    if (winner == 1) {
        statistics.recordWin();
    } else {
        statistics.recordLoss();
    }

    if (!statistics.save()) {
        cout << "Could not save statistics." << endl;
    } else {
        cout << "Statistics saved." << endl;
    }
}

// Repeatedly offers registration or login until a user successfully logs in.
User& loginOrRegister(UserManager& userManager) {
    int choice = 0;
    bool loginSuccessful = false;
    User* loggedInUser = nullptr;

    do {
        cout << endl << "=== Account Menu ===" << endl;
        cout << "1. Register" << endl;
        cout << "2. Login" << endl;
        cout << "Choose an option: ";

        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            cout << "Invalid choice." << endl;
            continue;
        }

        try {
            if (choice == 1) {
                string username;
                string password;

                cout << "Create a username: ";
                cin >> username;

                cout << "Create a password: ";
                cin >> password;

                userManager.registerUser(username, password);

                cout << "Registration successful." << endl;
            }
            else if (choice == 2) {
                string username;
                string password;

                cout << "Username: ";
                cin >> username;

                cout << "Password: ";
                cin >> password;

                User& user = userManager.login(username, password);

                cout << "Login successful. Welcome, " << user.getUsername() << "!" << endl;

                loggedInUser = &user;
                loginSuccessful = true;
            }
            else {
                cout << "Invalid choice." << endl;
            }
        }
        catch (const runtime_error& error) {
            cout << "Error: " << error.what() << endl;
        }

    } while (!loginSuccessful);

    return *loggedInUser;
}

// Loads the account, starts the selected game mode, and manages the main menu.
int main() {
    int choice;

    UserManager userManager;
    User* currentUser = nullptr;

    try {
        userManager.loadUsers();
        currentUser = &loginOrRegister(userManager);
    }
    catch (const runtime_error& error) {
        cout << "Fatal error: " << error.what() << endl;
        return 1;
    }

    // Seed the random number generator
    srand(time(NULL));

    // Load statistics for the logged-in user
    string statisticsFile = "statistics_" + currentUser->getUsername() + ".txt";

    Statistics statistics(statisticsFile);
    statistics.load();

    // Display screen
    displayTitle();
    displayMenu();

    cin >> choice;

    // Checking cin is valid
    while (!cin) {
        cin.clear();
        cin.ignore(INT_MAX, '\n');
        cout << "Please enter a number." << endl;
        cin >> choice;
    }

    while (choice) {
        int winner = 0;

        switch (choice) {
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
                cout << endl << "Exiting the game." << endl;
                return 0;

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
            cout << "Please enter a number." << endl;
            cin >> choice;
        }
    }

    return 0;
}
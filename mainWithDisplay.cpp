#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Board.h"

using namespace std;

int main() { //CHANGED 
    // Seed the random number generator
    srand(static_cast<unsigned int>(time(0)));

    //Display screen 
    
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


    // Create the board
    Board board;

    // Randomly place all five ships
    board.randomlyPlaceFleet();

    // Display the board
    cout << "=== Random Battleship Board ===\n";
    cout << board << endl;

    // Check whether all ships were placed
    cout << "All ships placed: ";

    if (board.allShipsPlaced()) {
        cout << "Yes\n";
    } else {
        cout << "No\n";
    }

    return 0;
}

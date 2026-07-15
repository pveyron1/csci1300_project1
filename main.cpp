#include <iostream>
#include <thread>
#include <chrono>
#include "Game.h"

using namespace std;

int main()
{
    cout << "Bundle Game" << endl;
   cout << "Press Enter to start:";
   cin.get();

   for (int i = 0; i < 3; i++)
{
    this_thread::sleep_for(chrono::milliseconds(100));
}


cout << "\nWelcome to bundle game! " << endl;
cout << "To complete the game, you must collect all items for The Final Bundle" << endl;
cout << "and donate them to the Community Center." << endl;
cout << "You can always check what you still need to collect by visitng the community center" << endl;
cout << "Make sure to talk to Lewis, he knows the lay of the land." << endl;
cout << "Be careful though, you only have one week to complete the final bundle." << endl;
cout << "Good luck!" << endl;

cout << "\nPress Enter to continue:" << endl;


cin.get();
cout << "Loading..." << endl;
cout << "\n" << endl;
for (int i = 0; i < 3; i++)
{
    this_thread::sleep_for(chrono::milliseconds(500));
}


    Game game;

    game.start();

    return 0;
}
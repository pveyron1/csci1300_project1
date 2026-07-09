#include "Game.h"
#include <iostream>

using namespace std;

Game::Game()
{
    running = true;
    day = 1;

    // npcs
    villagers[0].setName("Lewis");
    villagers[0].setDialogue("Welcome to Stardew Valley!");
    villagers[0].setQuest("Collect one Parsnip.");

    villagers[1].setName("Robin");
    villagers[1].setDialogue("Need anything built?");
    villagers[1].setQuest("Gather 10 Wood.");

    // places
    locations[0].setName("Farm");
    locations[0].setDescription("Your home and crops.");
    locations[0].setUnlocked(true);

    locations[1].setName("Town");
    locations[1].setDescription("Meet the townspeople.");
    locations[1].setUnlocked(true);

    locations[2].setName("Beach");
    locations[2].setDescription("Catch fish.");
    locations[2].setUnlocked(true);

    locations[3].setName("Mine");
    locations[3].setDescription("Find ores.");
    locations[3].setUnlocked(false);

    locations[4].setName("Community Center");
    locations[4].setDescription("Donate bundle items.");
    locations[4].setUnlocked(true);
}

void Game::start()
{
    cout << "=====================================" << endl;
    cout << " Welcome to Bundle Game!" << endl;
    cout << "=====================================" << endl;

    gameLoop();
}

void Game::displayMenu()
{
    cout << "\n=====================================" << endl;
    cout << "Day " << day << endl;

    player.displayStats();

    cout << "Current Location: "
         << locations[player.getLocation()].getName() << endl;

    cout << "\nMenu"<< endl;
    cout << "1. Talk to Lewis"<< endl;
    cout << "2. Talk to Robin"<< endl;
    cout << "3. View Inventory"<< endl;
    cout << "4. View Current Location"<< endl;
    cout << "5. End Day"<< endl;
    cout << "6. Quit"<< endl;
}

void Game::gameLoop()
{
    int choice;

    while(running)
    {
        displayMenu();

        cout << "Choice: ";
        cin >> choice;

        switch(choice)
        {
        case 1:
            villagers[0].talk();
            break;

        case 2:
            villagers[1].talk();
            break;

        case 3:
            player.getInventory().displayInventory();
            break;

        case 4:
            locations[player.getLocation()].displayLocation();
            break;

        case 5:
            day++;
            cout << "A new day begins..."<< endl;;
            break;

        case 6:
            running = false;
            cout << "Thanks for playing!"<< endl;
            break;

        default:
            cout << "Invalid choice." << endl;
        }
    }
}
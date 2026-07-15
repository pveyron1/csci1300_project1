#include "Game.h"
#include <iostream>
#include <thread>
#include <chrono>
#include <limits>
#include <fstream>
#include <string>

using namespace std;

Game::Game()
{
    running = true;
    day = 1;

    // npcs
    villagers[0].setName("Lewis the Mayor");
    villagers[0].setDialogue("Welcome to Stardew Valley!");
    villagers[0].setQuest("Collect one Parsnip.");

    villagers[1].setName("Robin the Carpenter");
    villagers[1].setDialogue("Need anything built?");
    villagers[1].setQuest("Gather 10 Wood. The community center is doing some ridiculous renevations.");

    villagers[2].setName("Willy the Angler");
    villagers[2].setDialogue("Use my rod to catch ");
    villagers[2].setQuest("Gather 10 Wood.");

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
    locations[3].setDescription("Find and mine ores.");
    locations[3].setUnlocked(false);

    locations[4].setName("Community Center");
    locations[4].setDescription("Donate bundle items.");
    locations[4].setUnlocked(true);

    willyTalkCount = 0;
    fishQuestComplete = false;

    fishDonated = false;
    cropDonated = false;
    mineralDonated = false;
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
    cout << "1. Talk to Lewis" << endl;
    cout << "2. Explore Current Location" << endl;
    cout << "3. Take the bus to a new location" << endl;
    cout << "4. View Inventory" << endl;
    cout << "5. View Map" << endl;
    cout << "6. End Day" << endl;
    cout << "7. Quit" << endl;
}
bool Game::bundleComplete()
{
    return cropDonated &&
           fishDonated &&
           mineralDonated;
}

void Game::gameLoop()
{
    int choice;
    int movesUsed = 0;

    while (running)
    {
        displayMenu();

        cout << "Moves left today: " << 3 - movesUsed << endl;
        cout << "Choice: ";
        cin >> choice;

switch (choice)
{
    case 1:
        talkToLewis();
    break;

    case 2:
        if (locationAction())
        {
            movesUsed++;
        }
        break;

    case 3:
        if (travel())
        {
            movesUsed++;
        }
        break;

    case 4:
        player.getInventory().displayInventory();
        break;

    case 5:
        locations[player.getLocation()].displayLocation();
        displayMap();
        break;

    case 6:
        day++;
        movesUsed = 0;
        cout << "A new day begins..." << endl;
        break;

    case 7:
        running = false;
        cout << "Thanks for playing!" << endl;
        break;

    default:
        cout << "Invalid choice." << endl;
}

        if (movesUsed >= 3)
        {
            day++;
            movesUsed = 0;

            cout << "You used all 3 moves for the day." << endl;
            cout << "A new day begins..." << endl;
        }

        if (bundleComplete())
        {
            typeMessage("Lewis: Thank you so much! You complleted the final bundle!");
            typeMessage("You have saved Pelican Town!");
            typeMessage("Thanks for playing!");

            running = false;
        }
        else if (day > 7)
        {
            typeMessage("Lewis: Thanks for the help, but");
            typeMessage("you did not complete the bundle in time. :(");
            typeMessage("Thanks for playing!");
            
            running = false;
        }
    }
}
bool Game::travel()
{
    int locationChoice;

    cout << "Where would you like to travel?" << endl;

    for (int i = 0; i < 5; i++)
    {
        cout << i + 1 << ". " << locations[i].getName();

        if (!locations[i].isUnlocked())
        {
            cout << " - Locked";
        }

        if (i == player.getLocation())
        {
            cout << " - Current Location";
        }

        cout << endl;
    }

    cout << "Choice: ";
    cin >> locationChoice;

    int newLocation = locationChoice - 1;

    if (newLocation < 0 || newLocation >= 5)
    {
        cout << "\nInvalid location." << endl;
        pauseGame();
        return false;
    }

    if (!locations[newLocation].isUnlocked())
    {
        cout << "\nThat location is locked. Complete quests to unlock!" << endl;
        pauseGame();
        return false;
    }

    if (newLocation == player.getLocation())
    {
        cout << "\nYou are already there." << endl;
        pauseGame();
        return false;
    }

    player.setLocation(newLocation);

    cout << "\nYou traveled to "
         << locations[newLocation].getName()
         << "." << endl;
    pauseGame();
    return true;
}
void Game::talkToLewis()
{
    if (willyTalkCount == 0)
    {
        typeMessage("Lewis: Welcome to Pelican Town, I heard you're here to help us");
        typeMessage("complete the Final Bundle! Come to me for help if you need help with anything!");
        typeMessage("Willy at the Beach was looking for someone to help him.");
        typeMessage("You should pay him a visit.");

        pauseGame();
    }
    else if (!fishQuestComplete)
    {
        typeMessage("Lewis: Have you caught that fish for the Community Center yet?");
        typeMessage("Willy gave you a fishing rod, so head back to the Beach.");
        pauseGame();
    }
    else
    {
        typeMessage("Lewis: Excellent work on the fish bundle!");
        typeMessage("There are still more items to collect.");
        typeMessage("Keep exploring the valley and talking to the villagers.");
        pauseGame();
    }
}
bool Game::locationAction()
{
    int currentLocation = player.getLocation();

    if (currentLocation == 0)
    {
        cout << "You are at the Farm." << endl;
        cout << "Farm actions will go here." << endl;
        return false;
    }
    else if (currentLocation == 1)
    {
        cout << "You are in Town." << endl;
        cout << "Town actions will go here." << endl;
        return false;
    }
    else if (currentLocation == 2)
    {
        return beachAction();
    }
    else if (currentLocation == 3)
    {
        cout << "You are at the Mines." << endl;
        cout << "Mine actions will go here." << endl;
        return false;
    }
    else if (currentLocation == 4)
    {
        return communityCenterAction();
    }

    return false;
}
bool Game::beachAction()
{
    int choice;

    cout << "You are at the Beach." << endl;
    cout << "1. Talk to Willy" << endl;
    cout << "2. Go Fishing" << endl;
    cout << "Choice: ";
    cin >> choice;

    if (choice == 1)
    {
        talkToWilly();
        return false;
    }
    else if (choice == 2)
    {
        if (!player.getInventory().hasItem("Fishing Rod"))
        {
            cout << "You do not have a fishing rod." << endl;
            cout << "Find Willy! He'll be able to help!" << endl;
            pauseGame();
            return false;

            
        }

        cout << "You cast your fishing rod into the ocean." << endl;
        cout << "You caught a Sunfish!" << endl;

        Item sunfish("Sunfish", "Fish");
        player.getInventory().addItem(sunfish);

        fishQuestComplete = true;

       pauseGame();

        return true;
    }

    cout << "Invalid choice." << endl;
    pauseGame();
    return false;
}


void Game::talkToWilly()
{
    if (willyTalkCount == 0)
    {
        typeMessage("Willy: Ahoy! You must be the new farmer.");
        typeMessage("The Community Center still needs a fish.");
        typeMessage("Take this fishing rod and see what you can catch.");

        Item fishingRod("Fishing Rod", "Tool");
        player.getInventory().addItem(fishingRod);

        cout << "\nFishing Rod added to your inventory!" << endl;

        willyTalkCount++;

        pauseGame();
    }
    else if (fishQuestComplete)
    {
        typeMessage("Willy: That's a fine fish you caught!");
        typeMessage("You should take it to the Community Center.");

        pauseGame();

        willyTalkCount++;
    }
    else {
    int dialogueNumber = willyTalkCount % 3;

    if (dialogueNumber == 1)
    {
        typeMessage("Willy: Haven't caught anything yet?");
        typeMessage("Try casting near the end of the dock.");

        pauseGame();
    }
    else if (dialogueNumber == 2)
    {
        typeMessage("Willy: No luck yet?");
        typeMessage("Fishing takes patience. Keep trying.");

        pauseGame();
    }
    else
    {
        typeMessage("Willy: That rod should help you catch something.");
        typeMessage("The Community Center is counting on you.");

        pauseGame();
    }

    willyTalkCount++;
}
}
void Game::typeMessage(string message)
{
    for (int i = 0; i < message.length(); i++)
    {
        cout << message[i] << flush;
        this_thread::sleep_for(chrono::milliseconds(30));
    }

    cout << endl;
}
void Game::pauseGame()
{
    cout << endl;
    cout << "Press Enter to continue...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

bool Game::communityCenterAction()
{
    int choice;

    cout << "You are at the Community Center." << endl;
    cout << "1. Talk to the Junimo" << endl;
    cout << "2. Check Remaining Bundle Items" << endl;
    cout << "3. Donate Item(s)" << endl;
    cout << "Choice: ";
    cin >> choice;

    if (choice == 1)
    {
        talkAtCommunityCenter();
        return true;
    }
    else if (choice == 2)
    {
        displayBundleProgress();

        return false;
    }
    else if (choice == 3)
    {
        return donateBundleItems();
    }

    cout << "Invalid choice." << endl;
    pauseGame();
    return false;

}
void Game::talkAtCommunityCenter()
{
    if (bundleComplete())
    {
        typeMessage("Junimo: You completed the final bundle!");
        typeMessage("The Community Center can finally be restored.");
        pauseGame();
    }
    else
    {
        typeMessage("Junimo: The final bundle is not complete yet.");
        typeMessage("Bring us the remaining items before the season ends.");
        pauseGame();
    }
}
void Game::displayBundleProgress()
{
    cout << "==============================" << endl;
    cout << "Final Bundle Progress" << endl;
    cout << "==============================" << endl;

    if (cropDonated)
    {
        cout << "Crop: Donated" << endl;
    }
    else
    {
        cout << "Crop: Still Needed" << endl;
    }

    if (fishDonated)
    {
        cout << "Fish: Donated" << endl;
    }
    else
    {
        cout << "Fish: Still Needed" << endl;
    }

    if (mineralDonated)
    {
        cout << "Mineral: Donated" << endl;
    }
    else
    {
        cout << "Mineral: Still Needed" << endl;
    }
    pauseGame();
}
bool Game::donateBundleItems()

{
    bool donatedSomething = false;

    if (!cropDonated &&
        player.getInventory().hasItem("Parsnip"))
    {
        cropDonated = true;
        donatedSomething = true;

        cout << "You donated a Parsnip. Thank you so much! One step closer!" << endl;
        pauseGame();
    }

    if (!fishDonated &&
        player.getInventory().hasItem("Sunfish"))
    {
        fishDonated = true;
        donatedSomething = true;

        cout << "You donated a Sunfish. Thank you so much! This will be very helpful" << endl;
        pauseGame();
    }

    if (!mineralDonated &&
        player.getInventory().hasItem("Copper Ore"))
    {
        mineralDonated = true;
        donatedSomething = true;

        cout << "You donated Copper Ore. Thanks! We will smelt it right away" << endl;
        pauseGame();
    }

    if (!donatedSomething)
    {
        cout << "You do not have any needed bundle items." << endl;
        pauseGame();
        return false;
    }

    cout << "Your bundle progress has been updated." << endl;
    displayBundleProgress();

    pauseGame();

    return true;
}

void Game::displayMap()
{
    ifstream mapFile("map.txt");

    if (!mapFile.is_open())
    {
        cout << "Error: could not open map.txt." << endl;
        return;
    }

    int currentLocation = player.getLocation();
    string line;

    while (getline(mapFile, line))
    {
        size_t position = line.find("$Farm$");

        if (position != string::npos)
        {
            if (currentLocation == 0)
            {
                line.replace(position, 6, "*Farm*");
            }
            else
            {
                line.replace(position, 6, "Farm");
            }
        }

        position = line.find("$Town$");

        if (position != string::npos)
        {
            if (currentLocation == 1)
            {
                line.replace(position, 6, "*Town*");
            }
            else
            {
                line.replace(position, 6, "Town");
            }
        }

        position = line.find("$Beach$");

        if (position != string::npos)
        {
            if (currentLocation == 2)
            {
                line.replace(position, 7, "*Beach*");
            }
            else
            {
                line.replace(position, 7, " Beach ");
            }
        }

        position = line.find("$Mine$");

        if (position != string::npos)
        {
            if (currentLocation == 3)
            {
                line.replace(position, 6, "*Mine*");
            }
            else
            {
                line.replace(position, 6, "Mine");
            }
        }

        position = line.find("$Community Center$");

        if (position != string::npos)
        {
            if (currentLocation == 4)
            {
                line.replace(position, 18, "*Community Center*");
            }
            else
            {
                line.replace(position, 18, " Community Center ");
            }
        }

        cout << line << endl;
    }

    mapFile.close();

    pauseGame();
}
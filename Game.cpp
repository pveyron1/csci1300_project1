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

    // places
    locations[0].setName("Farm");
    locations[0].setDescription("Your home and crops.");
    locations[0].setUnlocked(true);

    locations[1].setName("Town");
    locations[1].setDescription("Meet the villagers!");
    locations[1].setUnlocked(true);

    locations[2].setName("Beach");
    locations[2].setDescription("Catch fish and talk to Willy");
    locations[2].setUnlocked(true);

    locations[3].setName("Mine");
    locations[3].setDescription("Find and mine ores.");
    locations[3].setUnlocked(false);

    locations[4].setName("Community Center");
    locations[4].setDescription("Donate bundle items.");
    locations[4].setUnlocked(true);
//beach functions
    willyTalkCount = 0;
    fishQuestComplete = false;
//community center functions
    fishDonated = false;
    cropDonated = false;
    mineralDonated = false;
//town functions
    talkedToClint = false;
    usedJojaDeal = false;
    acceptedJojaHelp = false;
//mining functions
    miningAttempts = 0;
//farm functions
    parsnipsPlanted = false;
    parsnipPlantDay = 0;

    
}

void Game::start()
{
    cout << "=====================================" << endl;
    cout << " Welcome to Bundle Game!" << endl;
    cout << "=====================================" << endl;
    cout << "\nWhat is your name, farmer? ";

    
    string playerName;
    getline(cin, playerName);

    player.setName(playerName);

    cout << endl;
    typeMessage("Welcome to Pelican Town, " + player.getName() + "!");
    cout << endl;
    cout << "Press Enter to continue...";
    cin.get();
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
    if (cropDonated && fishDonated && mineralDonated)
{
    return true;
}
else
{
    return false;
}
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
        pauseGame();
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

            cout << "\nYou used all 3 moves for the day." << endl;
            cout << "A new day begins..." << endl;
        }

        if (bundleComplete())
        {
    if (acceptedJojaHelp)
    {
        typeMessage("Lewis: You completed the Community Center bundle!");
        typeMessage("I wish Morris hadn't been involved...");
        typeMessage("But Pelican Town has been saved thanks to you!");
    }
    else
    {
        typeMessage("Lewis: Thank you so much! You completed the final bundle!");
        typeMessage("You restored the Community Center without Joja's help!");
        typeMessage("Thanks for staying true to your morals!");
        typeMessage("You have saved Pelican Town!");
    }

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
        typeMessage("Lewis: Hey " + player.getName() + "! Welcome to Pelican Town, Im the mayor.");
        typeMessage("I heard you're here to help us complete the Final Bundle! ");
        typeMessage("Don't hesitate to come to me if you need help with anything!");
        typeMessage("Willy at the Beach was looking for someone to help him.");
        typeMessage("Plant some seeds then head over there!");
        

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
        return farmAction();
    }
    else if (currentLocation == 1)
    {
        return townAction();
    }
    else if (currentLocation == 2)
    {
        return beachAction();
    }
    else if (currentLocation == 3)
    {
        return mineAction();
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
        
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
        cout << "            BEACH" << endl;
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
  
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
        typeMessage("Come show me when you're done! I love seeing what newcomers can catch!");
        
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
        typeMessage("After you donate that, talk with Clint in the town.");
        typeMessage("Maybe he can help you find something else for the Community Center");
        typeMessage("Make sure to steer clear of Joja, I've heard they want to turn the");
        typeMessage("Community Center into a storage warehouse!");

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
    for (int i = 0; i < static_cast<int>(message.length()); i++)
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
    cin.ignore(1000, '\n');
    cin.get();
}

bool Game::communityCenterAction()
{
    int choice;

    cout << "You are at the Community Center." << endl;
    cout << "1. Talk to the Junimo" << endl;
    cout << "2. Check Remaining Bundle Items" << endl;
    cout << "3. Donate Item(s)" << endl;
    cout << "4. View the strange portrait" << endl;
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
        pauseGame();
        return false;
    }
    else if (choice == 3)
    {
        return donateBundleItems();
    }
    else if (choice == 4)
    {
        displayJonSnow();
        return false;
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
}

bool Game::donateBundleItems()

{
    bool donatedSomething = false;

    if (!cropDonated &&
        player.getInventory().hasItem("Parsnip"))
    {
        cropDonated = true;
        donatedSomething = true;

        player.getInventory().removeItem("Parsnip");

        cout << "\nYou donated a Parsnip. Thank you so much! One step closer!" << endl;
        cout << "\nParsnip has been removed from your inventory" << endl;
    }

    if (!fishDonated &&
        player.getInventory().hasItem("Sunfish"))
    {
        fishDonated = true;
        donatedSomething = true;

        cout << "\nYou donated a Sunfish. Thank you so much! This will be very helpful" << endl;
        cout << "\nSunfish has been removed from your inventory" << endl;
        player.getInventory().removeItem("Sunfish");
    }


    if (!mineralDonated &&
        player.getInventory().hasItem("Gold Ore"))
    {
        mineralDonated = true;
        donatedSomething = true;

        cout << "\nYou donated Gold Ore. Thanks! We will smelt it right away" << endl;
        player.getInventory().removeItem("Gold Ore");
        cout << "\nGold Ore has been removed from your inventory" << endl;
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

bool Game::townAction()
{
    int choice;

    while (true)
    {
        cout << endl;
        cout << "  /\\" << endl;
        cout << " /  \\" << endl;
        cout << "/____\\      /\\" << endl;
        cout << "|    |     /  \\" << endl;
        cout << "==============================" << endl;
        cout << "            TOWN" << endl;
        cout << "==============================" << endl;
        cout << "1. Visit Clint's Blacksmith Shop" << endl;
        cout << "2. Visit JojaMart" << endl;
        cout << "3. Talk to Lewis" << endl;
        cout << "4. Leave Town" << endl;
        cout << "Enter your choice: ";

        cin >> choice;

        while (cin.fail() || choice < 1 || choice > 4)
        {
            cin.clear();
            cin.ignore(100000000, '\n');

            cout << "Please enter a number from 1 to 4: ";
            cin >> choice;
        }

        if (choice == 1)
        {
            talkToClint();
        }
        else if (choice == 2)
        {
            visitJojaMart();
        }
        else if (choice == 3)
        {
            talkToLewis();
        }
        else
        {
            return false;
        }
    }
}

void Game::talkToClint()
{
    cout << endl;

    if (!talkedToClint)
    {
        typeMessage("Clint: You want to explore the Mine?");
        typeMessage("You will need something to break through the rocks.");
        typeMessage("\nClint reaches behind the counter and gives you an old pickaxe.");

        cout << endl;
        cout << "You received a Pickaxe!" << endl;

        Item pickaxe("Pickaxe", "Tool");
        player.getInventory().addItem(pickaxe);

        cout << "\nPickaxe added to your inventory!" << endl;


        locations[3].setUnlocked(true);

        talkedToClint = true;

        cout << "\nThe Mine has been unlocked!" << endl;
    }
    else
    {
        typeMessage("\nClint: That pickaxe should help you inside the Mine.");
    }

    pauseGame();
}

void Game::visitJojaMart()
{
    int choice;

    while (true)
    {
        cout << endl;
        cout << "==============================" << endl;
        cout << "          JOJAMART" << endl;
        cout << "==============================" << endl;
        cout << "1. Talk to Morris" << endl;
        cout << "2. Leave JojaMart" << endl;
        cout << "Enter your choice: ";

        cin >> choice;

        while (cin.fail() || choice < 1 || choice > 2)
        {
            cin.clear();
            cin.ignore(10000, '\n');

            cout << "Please enter 1 or 2: ";
            cin >> choice;
        }

        if (choice == 1)
        {
            talkToMorris();
        }
        else
        {
            return;
        }
    }
}

void Game::talkToMorris()
{
    cout << endl;

    if (usedJojaDeal)
    {
        typeMessage("Morris: Joja has already provided you with an item.");
        typeMessage("Thank you for choosing Joja.");
        pauseGame();
        return;
    }

    typeMessage("Morris: Still wasting your time restoring that old Community Center?");
    typeMessage("Joja can provide one missing bundle item immediately.");
    typeMessage("Of course, our delivery service will cost you three days.");

    cout << endl;
    cout << "Morris will give you one missing bundle item." << endl;
    cout << "Three days will pass if you accept." << endl;
    cout << endl;
    cout << "1. Accept the Joja deal" << endl;
    cout << "2. Decline the Joja deal" << endl;
    cout << "Enter your choice: ";

    int choice;
    cin >> choice;

    while (cin.fail() || choice < 1 || choice > 2)
    {
        cin.clear();
        cin.ignore(10000, '\n');

        cout << "Please enter 1 or 2: ";
        cin >> choice;
    }

    if (choice == 1)
    {
        giveJojaBundleItem();

        day = day + 3;

        usedJojaDeal = true;
        acceptedJojaHelp = true;

        cout << endl;
        cout << "Three days have passed." << endl;
        cout << "It is now Day " << day << "." << endl;

        typeMessage("Morris: Another satisfied Joja customer.");
        typeMessage("Maybe don't tell Lewis, he has a distaste for me...");
    }
    else
    {
        typeMessage("Morris: You will come around eventually.");
    }

    pauseGame();
}

void Game::giveJojaBundleItem()
{
    cout << endl;

    if (!fishDonated)
    {
        fishDonated = true;

        cout << "Joja delivered a Fish for the bundle!" << endl;
        cout << "The Fish was automatically donated." << endl;
    }
    else if (!cropDonated)
    {
        cropDonated = true;

        cout << "Joja delivered a Crop for the bundle!" << endl;
        cout << "The Crop was automatically donated." << endl;
    }
    else if (!mineralDonated)
    {
        mineralDonated = true;

        cout << "Joja delivered a Mineral for the bundle!" << endl;
        cout << "The Mineral was automatically donated." << endl;
    }
}

void Game::displayJonSnow()
{
    cout << endl;
    cout << "You examine an old portrait hanging on the wall..." << endl;
    cout << endl;

    cout << "                 _..--------.._" << endl;
    cout << "              .-'  .-~~~~~~-.  '-." << endl;
    cout << "            .'   .'  //////  '.   '." << endl;
    cout << "           /   .'  /////////   '.   \\" << endl;
    cout << "          /   /  /////////////   \\   \\" << endl;
    cout << "         |   |  ///  _   _  ///   |   |" << endl;
    cout << "         |   |  //  / \\ / \\  //   |   |" << endl;
    cout << "         |   |  ||    o o    ||   |   |" << endl;
    cout << "         |   |  ||     ^     ||   |   |" << endl;
    cout << "         |   |  ||   _____   ||   |   |" << endl;
    cout << "          \\   \\  \\\\ /_____\\ //   /   /" << endl;
    cout << "           \\   '.  \\\\\\|||///  .'   /" << endl;
    cout << "            '.   '-.|||||.-'   .'" << endl;
    cout << "              '-._  |||||  _.-'" << endl;
    cout << "              .-'\\\\|||||||//'-." << endl;
    cout << "           .-'  \\\\\\|||||||///  '-." << endl;
    cout << "         .'   ////|||||||||\\\\\\\\   '." << endl;
    cout << "        /____/////|||||||||\\\\\\\\\\____\\" << endl;
    cout << "        |   //////|||||||||\\\\\\\\\\\\   |" << endl;
    cout << "        |         LONGCLAW      /|   |" << endl;
    cout << "        |______________________/ |___|" << endl;
    cout << "                              /  /" << endl;
    cout << "                             /  /" << endl;
    cout << "                            /__/" << endl;
    cout << endl;
    cout << "               JON SNOW" << endl;
    cout << "          KING IN THE NORTH" << endl;
    cout << endl;

    typeMessage("The dark-haired warrior stares solemnly into the distance.");
    typeMessage("His heavy black cloak appears covered in snow.");
    typeMessage("A small plaque reads: You know nothing, Jon Snow.");

    pauseGame();
}

bool Game::mineAction()
{
    int choice;

    while (true)
    {
        cout << endl;
        cout << "======================================" << endl;
        cout << "               MINE" << endl;
        cout << "======================================" << endl;
        cout << "1. Mine for Gold Ore" << endl;
        cout << "2. Leave the Mine" << endl;
        cout << "======================================" << endl;
        cout << "Enter your choice: ";

        cin >> choice;

        while (cin.fail() || choice < 1 || choice > 2)
        {
            cin.clear();
            cin.ignore(10000, '\n');

            cout << "Please enter 1 or 2: ";
            cin >> choice;
        }

        if (choice == 1)
        {
            mineForOre();
            return true;
        }
        else
        {
            return false;
        }
    }
}

void Game::mineForOre()
{
    miningAttempts++;

    cout << endl;

    if (miningAttempts == 1)
    {
        typeMessage("You swing your pickaxe into the rock.");
        typeMessage("The rock barely cracks.");
    }
    else if (miningAttempts == 2)
    {
        typeMessage("You strike the rock again.");
        typeMessage("You see something shiny poking through the stone...");
    }
    else
    {
        typeMessage("You give the rock one final swing...");
        typeMessage("The rock shatters!");

        cout << endl;
        cout << "You found Gold Ore!" << endl;

        Item goldOre("Gold Ore", "Mineral");
        player.getInventory().addItem(goldOre);

        cout << "\nGold Ore added to your inventory!" << endl;

        miningAttempts = 0;
    }

    pauseGame();
}

bool Game::farmAction()
{
    int choice;

    while (true)
    {
        cout << endl;
        cout << "======================================" << endl;
        cout << "               FARM" << endl;
        cout << "======================================" << endl;

        if (!parsnipsPlanted)
        {
            cout << "The crop field is empty." << endl;
        }
        else if (day > parsnipPlantDay)
        {
            cout << "The parsnips are ready to harvest!" << endl;
        }
        else
        {
            cout << "The parsnips are still growing." << endl;
            cout << "They will be ready tomorrow." << endl;
        }

        cout << endl;
        cout << "1. Check crop field" << endl;
        cout << "2. Leave the Farm" << endl;
        cout << "Enter your choice: ";

        cin >> choice;

        while (cin.fail() || choice < 1 || choice > 2)
        {
            cin.clear();
            cin.ignore(10000, '\n');

            cout << "Please enter 1 or 2: ";
            cin >> choice;
        }

        if (choice == 1)
        {
            if (!parsnipsPlanted)
            {
                plantParsnips();
            }
            else if (day > parsnipPlantDay)
            {
                harvestParsnips();
            }
            else
            {
                typeMessage("Your parsnips are still growing.");
                typeMessage("Come back tomorrow to harvest them.");

                pauseGame();
            }   return true;
        }
        else
        {
            return false;
        }
    }
}

void Game::plantParsnips()
{
    typeMessage("You prepare the soil.");
    typeMessage("You plant a row of parsnip seeds.");
    typeMessage("The parsnips will be ready tomorrow.");

    parsnipsPlanted = true;
    parsnipPlantDay = day;

    pauseGame();
}

void Game::harvestParsnips()
{
    typeMessage("You pull the fully grown parsnips from the soil.");

    Item parsnip("Parsnip", "Crop");
    player.getInventory().addItem(parsnip);

    cout << endl;
    cout << "Parsnip added to your inventory!" << endl;
    cout << "You should donate it to the Community Center." << endl;

    parsnipsPlanted = false;
    parsnipPlantDay = 0;

    pauseGame();
}
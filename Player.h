#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include "Inventory.h"

using namespace std;

class Player
{
private:
    string name;
    int energy;
    int money;
    int currentLocation;

    Inventory inventory;

public:
    Player();

    void setName(string n);

    string getName();

    int getEnergy();
    int getMoney();
    int getLocation();

    void setLocation(int loc);

    Inventory& getInventory();

    void displayStats();
};

#endif
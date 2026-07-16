#include "Player.h"
#include <iostream>

using namespace std;

Player::Player()
{
    name = "";
    money = 100;
    currentLocation = 0;
}

void Player::setName(string n)
{
    name = n;
}

string Player::getName()
{
    return name;
}

int Player::getMoney()
{
    return money;
}

int Player::getLocation()
{
    return currentLocation;
}

Inventory& Player::getInventory()
{
    return inventory;
}

void Player::displayStats()
{
    cout << "Player: " << name << endl;
   // cout << "Money: $" << money << endl;
}
void Player::setLocation(int newLocation)
{
    currentLocation = newLocation;
}
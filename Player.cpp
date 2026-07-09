#include "Player.h"
#include <iostream>

using namespace std;

Player::Player()
{
    name = "Farmer";
    energy = 10;
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

int Player::getEnergy()
{
    return energy;
}

int Player::getMoney()
{
    return money;
}

int Player::getLocation()
{
    return currentLocation;
}

void Player::setLocation(int loc)
{
    currentLocation = loc;
}

Inventory& Player::getInventory()
{
    return inventory;
}

void Player::displayStats()
{
    cout << "\nPlayer: " << name << endl;
    cout << "Energy: " << energy << endl;
    cout << "Money: $" << money << endl;
}
#include "Location.h"
#include <iostream>

using namespace std;

Location::Location()
{
    name = "";
    description = "";
    unlocked = false;
}

void Location::setName(string n)
{
    name = n;
}

void Location::setDescription(string d)
{
    description = d;
}

void Location::setUnlocked(bool u)
{
    unlocked = u;
}

string Location::getName()
{
    return name;
}

string Location::getDescription()
{
    return description;
}

bool Location::isUnlocked()
{
    return unlocked;
}

void Location::displayLocation()
{
    cout << "Location: " << name << endl;
    cout << description << endl;

    if(unlocked)
        cout << "Unlocked"<< endl;
    else
        cout << "Locked" << endl;
}
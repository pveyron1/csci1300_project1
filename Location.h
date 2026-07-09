#ifndef LOCATION_H
#define LOCATION_H

#include <string>

using namespace std;

class Location
{
private:
    string name;
    string description;
    bool unlocked;

public:
    Location();

    void setName(string n);
    void setDescription(string d);
    void setUnlocked(bool u);

    string getName();
    string getDescription();
    bool isUnlocked();

    void displayLocation();
};

#endif
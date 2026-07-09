#include "Character.h"
#include <iostream>

using namespace std;

Character::Character()
{
    name = "";
    dialogue = "";
}

void Character::setName(string n)
{
    name = n;
}

void Character::setDialogue(string d)
{
    dialogue = d;
}

void Character::talk()
{
    cout << name << ": " << dialogue << endl;
}
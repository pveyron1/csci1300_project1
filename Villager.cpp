#include "Villager.h"
#include <iostream>

using namespace std;

Villager::Villager()
{
    quest = "";
}

void Villager::setQuest(string q)
{
    quest = q;
}

void Villager::giveQuest()
{
    cout << "Quest: " << quest << endl;
}

void Villager::talk()
{
    Character::talk();
    giveQuest();
}
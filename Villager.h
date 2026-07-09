#ifndef VILLAGER_H
#define VILLAGER_H
#include <string>
using namespace std;

#include "Character.h"

class Villager : public Character
{
private:
    string quest;

public:
    Villager();

    void setQuest(string q);

    void giveQuest();

    void talk();
};

#endif
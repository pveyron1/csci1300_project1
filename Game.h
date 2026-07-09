#ifndef GAME_H
#define GAME_H

#include "Player.h"
#include "Villager.h"
#include "Location.h"

class Game
{
private:
    Player player;

    Villager villagers[2];

    Location locations[5];

    bool running;

    int day;

public:
    Game();

    void start();

    void gameLoop();

    void displayMenu();
};

#endif
#ifndef GAME_H
#define GAME_H

#include "Player.h"
#include "Villager.h"
#include "Location.h"


class Game
{
private:
    Player player;

    Villager villagers[3];

    Location locations[5];

    bool running;

    int day;

    void talkToWilly();
    
    int willyTalkCount;
    
    bool fishQuestComplete;

    bool locationAction();

    void talkToLewis();

    bool beachAction();
    
    void gameLoop();

    void displayMenu();

    void displayMap();

    bool bundleComplete();

    bool travel();

    void typeMessage(string message);

    void pauseGame();
    
    bool communityCenterAction();
    
    void talkAtCommunityCenter();
    
    void displayBundleProgress();

    bool donateBundleItems();

    bool fishDonated;
    
    bool cropDonated;

    bool mineralDonated;
   
    public:
    Game();

    void start();


   
};



#endif
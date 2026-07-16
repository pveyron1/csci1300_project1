#ifndef GAME_H
#define GAME_H

#include <string>

#include "Player.h"
#include "Location.h"

using namespace std;

class Game
{
private:
    Player player;

    Location locations[5];

    bool running;

    int day;

    int willyTalkCount;

    bool fishQuestComplete;

    bool fishDonated;

    bool cropDonated;

    bool mineralDonated;

    bool talkedToClint;

    bool usedJojaDeal;

    bool acceptedJojaHelp;

    void gameLoop();

    void displayMenu();

    void displayMap();

    bool locationAction();

    bool travel();

    bool beachAction();

    bool communityCenterAction();

    bool townAction();

    void talkToWilly();

    void talkToLewis();

    void talkToClint();

    void visitJojaMart();

    void talkToMorris();

    void giveJojaBundleItem();

    void talkAtCommunityCenter();

    void displayBundleProgress();

    bool donateBundleItems();

    bool bundleComplete();

    void typeMessage(string message);

    void pauseGame();

    void displayJonSnow();

    bool mineAction();

    void mineForOre();

    int miningAttempts;

    bool farmAction();

    void plantParsnips();

    void harvestParsnips();

    bool parsnipsPlanted;

    int parsnipPlantDay;

    public:
    Game();

    void start();
};

#endif
#include <string>
using namespace std;
#ifndef INVENTORY_H
#define INVENTORY_H

#include "Item.h"


class Inventory
{
private:
    Item items[20];
    int itemCount;

public:
    Inventory();

    void addItem(Item item);
    
    void displayInventory();
    
    bool hasItem(string itemName);

    bool removeItem(string itemName);
};

#endif
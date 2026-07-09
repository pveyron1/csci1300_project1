
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
};

#endif
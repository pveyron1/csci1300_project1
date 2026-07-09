#include "Inventory.h"
#include <iostream>

using namespace std;

Inventory::Inventory()
{
    itemCount = 0;
}

void Inventory::addItem(Item item)
{
    if(itemCount < 20)
    {
        items[itemCount] = item;
        itemCount++;
    }
}

void Inventory::displayInventory()
{
    cout << "\nInventory" << endl;

    if(itemCount == 0)
    {
        cout << "Empty" << endl;
        return;
    }

    for(int i=0;i<itemCount;i++)
    {
        cout << i+1 << ". "
             << items[i].getName()
             << endl;
    }
}
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
    cout << "Inventory" << endl;

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
bool Inventory::hasItem(string itemName)
{
    for (int i = 0; i < itemCount; i++)
    {
        if (items[i].getName() == itemName)
        {
            return true;
        }
    }

    return false;
}
bool Inventory::removeItem(string itemName)
{
    for (int i = 0; i < itemCount; i++)
    {
        if (items[i].getName() == itemName)
        {
            for (int j = i; j < itemCount - 1; j++)
            {
                items[j] = items[j + 1];
            }

            itemCount--;
            return true;
        }
    }

    return false;
}
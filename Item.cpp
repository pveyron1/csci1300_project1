#include "Item.h"

Item::Item()
{
    name = "";
    type = "";
    value = 0;
}

void Item::setName(string n){ name = n; }
void Item::setType(string t){ type = t; }
void Item::setValue(int v){ value = v; }

string Item::getName(){ return name; }
string Item::getType(){ return type; }
int Item::getValue(){ return value; }
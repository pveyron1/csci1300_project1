#ifndef CHARACTER_H
#define CHARACTER_H

#include <string>

using namespace std;

class Character
{
protected:
    string name;
    string dialogue;

public:
    Character();

    void setName(string n);
    void setDialogue(string d);

    virtual void talk();
};

#endif
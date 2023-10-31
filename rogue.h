#include "player.h"
#ifndef _ROGUE_H
#define _ROGUE_H
// Q5c: Create Rogue class (2.5 points)
// Part 1: Create a child class of the Player class named 'Rogue'
class Rogue : public Player {
  public: 
    Rogue(string name, int level, playerType archetype) : Player(name, level, archetype) {};

    virtual void displayPlayer();
};
// Part2: Declare constructor which accepts the same 3 parameters as the parent class Player's constructor.
// Pass the 3 parameters to the super constructor of the Player class.

// Part 3: Re-declare the method displayPlayer (virtual method found inside of parent class Player)

#endif // _ROGUE_H

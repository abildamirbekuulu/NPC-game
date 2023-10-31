#include <iostream>
#include "wizard.h"

void Wizard::displayPlayer() {
    // displaying the info about Wizard 
    cout << "Player name: " << Player::getName() << endl;
    cout << "Health: " << Player::getHealth() << endl;
    cout << "Mana: " << Player::getMana() << endl;
    cout << "Armor: " << Player::getArmor() << endl;
    cout << "Magic Resist: " << Player::getMagicResist() << endl;
    cout << "Attack: " << Player::getAttack() << endl;
    cout << "Magic Attack: " << Player::getMagicAttack() << endl;
    cout << "Level: " << Player::getLevel() << endl;
    cout << "Archetype: Wizard" << endl;
}
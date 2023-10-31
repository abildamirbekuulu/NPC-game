// CSE240 Fall 2023 HW06
// Abil Damirbek uulu

// READ BEFORE YOU START:
// You are given a partially completed program that designed to simulate
// the storage of NPC assets and players in a hypothetical MMO.

// The first part consists of a class 'NPC' defined in NPC.h
// The definitions of class member functions are to be filled in NPC.cpp
// homework6template.cpp (this file) creates an array of objects 'nArr[]' and uses a menu driven program 
// to add an NPC, display NPC info, and sort the NPC list.
// You should start completing the program from from Q1 (found in the NPC.h/NPC.cpp files).

// The second part creates a list of players.
// Each player has name, a set of stats, and an archetype (Warrior, Wizard, or Rogue).
// This information is stored as an object of Player class. The class is defined in player.h
// The classes Warrior, Wizard, and Rogue are child classes of the Player class.
// When adding a new player, these child classes are used to make the player node of the list.
// So each node in the list is actually an object of Warrior, Wizard, or Rogue class.

// To begin, you should trace through the given code and understand how it works.
// Please read the instructions above each required function and follow the directions carefully.
// Do not modify given code.

// You can assume that all input is valid:
// Valid name:	String containing alphabetical letters
// Valid number: a positive integer

#include <iostream>
#include <fstream>
#include <string>
#include "NPC.h"
#include "Container.h"
#include "player.h"
#include "warrior.h"
#include "wizard.h"
#include "rogue.h"

#define MAX_NPCS 10

using namespace std;

// functions already implemented:
void executeAction(char c);
void displayNPCs();
Player* searchPlayer(string nameInput);
void displayList();		

// functions that need implementation:
int addNPC(string nameInput, string occupationInput, int level_input, int health_input);	// X points
void sort();											// X points
void addPlayer(string nameInput, int levelInput, playerType type);				// X points
void save(string fileName);									// X points
void load(string fileName);									// X points

NPC nArr[MAX_NPCS];			// array of objects
int cCount = 0;				// number of NPCs in the list
Container* list = NULL;			// global list

/**************************************** Implemented Functions ****************************************/

int main()
{
	char c = 'i';			// initialized to a dummy value

 	// During first execution, there will be no list.txt in source directory. list.txt is generated by save() while exiting the program.
	load("list.txt");
	do {
		cout << "CSE240 HW06 MMO Data\n";
		cout << "Please select an action:\n";
		cout << "\t n: add a new NPC\n";
		cout << "\t s: sort the NPCs in descending order based on level and display a range\n";
		cout << "\t d: display NPC list\n";
		cout << "\t p: add a new player\n";
		cout << "\t c: change level of a player\n";
		cout << "\t l: display player list\n";
		cout << "\t q: quit\n\n";
		cin >> c;
		cin.ignore();
		executeAction(c);
	} while (c != 'q');

	save("list.txt");

	list = NULL;

	return 0;
}

// Ask for details from user for the given selection and perform that action
// Read the function case by case
void executeAction(char c)
{
	string nameInput, occupationInput;
	int levelInput, healthInput, result;
	int typeInput = 3;
	playerType type;
	Player* playerResult = NULL;

	switch (c)
	{
	case 'n':	// add NPC
			// input NPC details from user
		cout << "Please enter NPC name: ";
		getline(cin, nameInput);
		cout << "Please enter NPC occupation: ";
		getline(cin, occupationInput);
		cout << "Please enter level: ";
		cin >> levelInput;
		cin.ignore();
		cout << "Please enter health: ";
		cin >> healthInput;
		cin.ignore();

		// add the NPC to the list
		result = addNPC(nameInput, occupationInput, levelInput, healthInput);
		if (result == 0)
			cout << "\nThat NPC is already in the list or list is full! \n\n";
		else
			cout << "\nThe NPC was successfully added to the list! \n\n";
		break;
	case 's':		// sort the list
		sort();
		break;
	case 'd':		// display the list
		displayNPCs();
		break;
	case 'p':		// add player
				// input player details from user
		cout << endl << "Enter player name: ";
		getline(cin, nameInput);
		cout << "Enter new player level: ";
		cin >> levelInput;
		cin.ignore();

		while (!(typeInput == 0 || typeInput == 1 || typeInput == 2))
		{
			cout << "Enter player archetype: " << endl;
			cout << "0. Warrior " << endl;
			cout << "1. Wizard" << endl;
			cout << "2. Rogue"<< endl;
			cin >> typeInput;
			cin.ignore();
		}
		type = (playerType)typeInput;

		// searchPlayer() will return the player object if found, else returns NULL
		playerResult = searchPlayer(nameInput);
		if (playerResult == NULL)
		{
			addPlayer(nameInput, levelInput, type);
			cout << endl << "Player added to list!" << endl << endl;
		}
		else
			cout << endl << "Player already present in the list!" << endl << endl;

		break;

	case 'c':	// change level
		cout << endl << "Enter player name: ";
		getline(cin, nameInput);
		// searchPlayer() will return the player node if found, else returns NULL
		playerResult = searchPlayer(nameInput);
		if (playerResult == NULL)
		{
			cout << endl << "Player not in list!" << endl << endl;
		}
		else
		{
			// if player exists in the list, then ask user for a new level
			cout << endl << "Enter new level: ";
			cin >> levelInput;
			cin.ignore();

			// Q3-c: Call changeLevel() here   (1 point)
			// 'playerResult' contains the player whose 'level' is to be changed.
			// 'levelInput' contains the new level of the player.
			// Call the function with appropriate arguments.
			playerResult->updateLevel(playerResult, levelInput);

			cout << endl << "Level changed!" << endl << endl;
		}
		break;
	case 'l':		// display the list
		cout << endl;
		displayList();
		break;
	case 'q':		// quit
		break;

	default: cout << c << " is invalid input!\n";
	}

}

// No implementation needed here, however it may be helpful to review this function
Player* searchPlayer(string nameInput)
{

	Container* tempList = list;			// work on a copy of 'list'

	while (tempList != NULL)			// parse till end of list
	{
		if (tempList->player->getName() == nameInput)
		{
			return tempList->player;	// return the player if found
		}

		tempList = tempList->next;		// parse the list
	}

	return NULL;					// return NULL if player not found in list
}

// displayNPCs
// This function displays the list of NPCs.
// We call the class function 'displayNPC()' here. Note that these are two different functions.
// NPC::displayNPC() displays details of one NPC object, while displayNPCs() should display all NPCs
void displayNPCs()
{
	// Write the code below
	for (int i = 0; i < cCount; i++)	// parse the list
	{
		nArr[i].displayNPC();		// use displayNPC() to display the list
		cout << endl;
	}
}

// displayList
// This function displays the list of players and their details (name, level, archetype)
void displayList()
{
	Container* tempList = list;		// work on a copy of 'list'

	if (list == NULL)
		cout << endl << "List is empty!" << endl;
	// parse the list and use class member function 'displayPlayer()' to display player info
	while (tempList != NULL)
	{
		tempList->player->displayPlayer();
		cout << endl;
		tempList = tempList->next;
	}
}

/************************************** Functions To Be Implemented *********************************/

// Q3 - addNPC (5 points)
// This function adds a new NPC with the details given in function arguments.
// Add the NPC in 'nArr' (array of objects) only if there is remaining capacity in the array and if the NPC does not already exist in the list
// This function returns 1 if the NPC is added successfully, else it returns 0 for the cases mentioned above.
// Assume user enters level in any positive integer range.
int addNPC(string nameInput, string occupationInput, int levelInput, int healthInput)
{
	if (cCount >= MAX_NPCS) {
			return 0;
	}

	// Check if the NPC with the same name already exists in the list
	for (int i = 0; i < cCount; i++) {
			if (nArr[i].getName() == nameInput) {
					return 0; // NPC with the same name already exists
			}
	}

	// If the list is not full and the NPC doesn't already exist, add it
	nArr[cCount].setName(nameInput);
	nArr[cCount].setOccupation(occupationInput);
	nArr[cCount].setLevel(levelInput);
	nArr[cCount].setHealth(healthInput);
	cCount++;

	return 1; // NPC added successfully
}

// Q4 - sort (5 points)
// This function sorts the NPCs in descending order of level
// After, you will iterate through the array and display NPCS whose
// level lies within a range lowerBound <= level <= upperBound.
// You may use the 'tempNPC' object for sorting logic, if needed.
// If you are jumping to a new line, please use endl. 
// You will want to use the following two lines of output in this function:
// "Please enter the lower level bound: "
// "Please enter the upper level bound: "
void sort()
{
	NPC tempNPC;
	int lowerBound;
	int upperBound;
	// Get the lower and upper level bounds from the user
	cout << "Please enter the lower level bound: ";
	cin >> lowerBound;
	cout << "Please enter the upper level bound: ";
	cin >> upperBound;

	// Sort the NPCs by level in descending order
	for (int i = 0; i < cCount - 1; i++) {
			for (int j = i + 1; j < cCount; j++) {
					if (nArr[i].getLevel() < nArr[j].getLevel()) {
							tempNPC = nArr[i];
							nArr[i] = nArr[j];
							nArr[j] = tempNPC;
					}
			}
	}

	// Display NPCs within the specified level range
	for (int i = 0; i < cCount; i++) {
			int level = nArr[i].getLevel();
			if (level >= lowerBound && level <= upperBound) {
					nArr[i].displayNPC();
					cout << endl;
			}
	}
}


// Q7-b: Define Friend Function updateLevel()  (1.5 points)
// Define the function updateLevel()that is declared in player.h file.
// This function sets the new 'level' of the player. The player object and new level is to be passed as function arguments.
// Use 'd' display option after using 'c' option to verify.
// You will need to implement addPlayer() and displayList() before you test this function.
// Updating a player's level will update their stats. This scaling matches the same scaling as the constructor in player.cpp.

void Player::updateLevel(Player *player, int newLevel) {
	player->level = newLevel;
	if(player->archetype == warrior){
		player->health = level * 100;
		player->mana = level * 10;
		player->armor = level * 50;
		player->magicResist = level * 25;
		player->attack = level * 50;
		player->magicAttack = level * 10;
	}
	else if(player->archetype == wizard){
		player->health = level * 25;
		player->mana = level * 100;
		player->armor = level * 10;
		player->magicResist = level * 50;
		player->attack = level * 10;
		player->magicAttack = level * 100;
	}
	else if(player->archetype == rogue){
		player->health = level * 50;
		player->mana = level * 25;
		player->armor = level * 25;
		player->magicResist = level * 10;
		player->attack = level * 100; 
		player->magicAttack = level * 50;
	}
}

// Q8 - addPlayer  (5 points)
// This function is used to add a new player to the global linked list 'list'. Add the new player to tail of the list.
// playerType 'type' can be warrior, wizard, or rogue. You will need to use the function argument type to determine which constructor to use to create new player node.
// For example, if the user enters type as 'rogue', then you need to use the Rogue class and constructor to create new player node and add it to the list.
// NOTE: In executeAction(), searchPlayer() is called before this function. Therefore no need to check here if the player exists in the list.
//       See how this fucntion is called in case 'a' of executeAction()
void addPlayer(string nameInput, int levelInput, playerType type)
{
	//add player to head of linked list
	Container* tempList = list;		// work on a copy of 'list'
	Player* player;
	if(type == warrior) {
		player = new Warrior(nameInput, levelInput, type);
	}
	else 
	if(type == wizard) {
		player = new Wizard(nameInput, levelInput, type);
	}
	else {
		player = new Rogue(nameInput, levelInput, type);
	}
	Container* newPlayer = new Container();
	newPlayer->player = player;
	newPlayer->next = 0;
	if(tempList == NULL) {
		list = newPlayer;
	} else {
		while(tempList->next != 0) {
			tempList = tempList->next;
		}
		tempList->next = newPlayer;
	}
}

// Q9 - save (4 points)
// Save the linked list of players to a file list.txt using ofstream.
// You will need to save the number of players in linked list. That will help in load() when reading the file.
// You must store in the following format:
// <no. of players>
// <Player1 name>
// <Player1 level>
// <Player1 archetype>
// <Player2 name>
// <Player2 level>
// <Player2 archetype>
// and so on..
// You may store the list in another format if you wish. You need to read the file in load () the same way that it is saved in save().
// This function is called when exiting the program (end of main() ).
// Hint: You should cast the enum 'playerType' to an int before writing it to the file.
void save(string fileName)
{

	ofstream saveFile;

	saveFile.open(fileName);
	if(saveFile.is_open()) {
		// loop through linked list and save name, level, type each to a new line in file
		Container* tempList = list;
		int cnt = 0;
		while(tempList != 0) {
			tempList = tempList->next;
			cnt++; // counts number of players
		}
		saveFile << cnt << endl;
		tempList = list;
		while(tempList != 0) {
			// saving players data into file
			saveFile << tempList->player->getName() << endl;
			saveFile << tempList->player->getLevel() << endl;
			saveFile << tempList->player->getPlayerType() << endl;
			tempList = tempList->next;
		}
		saveFile.close();
	} 
}

// q10 - load (4 points)
// Load the linked list of players from the file using ifstream.
// You will need to create the linked list in the same order that is was saved to the file in save().
// First, read the number of players saved in the file.
// Then, for every player you will need to create a new Player node depending on player archetype. Add the player to the tail of the list. 
// Hint: The enum 'playerType' will need to be cast back to 'playerType' when making the player node.
// This function is called at the beginning of main().
void load(string fileName)
{
  ifstream loadFile;

	loadFile.open(fileName);
	if(loadFile.is_open()) {
		string sz, name, level, sttype;
		// read name, level, type into string variables
		getline(loadFile, sz);
		for(int i = 0; i < stoi(sz); i++){
			getline(loadFile, name);
			getline(loadFile, level);
			getline(loadFile, sttype);

			// convert type to playertype
			playerType type;
			if(stoi(sttype) == 0){
				type = warrior;
			}
			if(stoi(sttype) == 1){
				type = wizard;
			}
			if(stoi(sttype) == 2){
				type = rogue;
			}

			// create new player object based off type
			Container* newPlayer = new Container();
			Player* player;
			if (type == warrior) 
			{
				player = new Warrior(name, stoi(level), type);
			}
			else if (type == wizard) 
			{
				player = new Wizard(name, stoi(level), type);
			}
			else {
				player = new Rogue(name, stoi(level), type);
			}
			newPlayer->player = player;

			// add player to end of linked list
			Container* tempList = list;
			newPlayer->next = 0;
			if(tempList == NULL) {
				list = newPlayer;
			} else {
				while(tempList->next != 0) {
					tempList = tempList->next;
				}
				tempList->next = newPlayer;
			}
		}
		loadFile.close();
	}
}

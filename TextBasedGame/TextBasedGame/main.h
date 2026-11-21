#pragma once
#include <iostream>
#include <functional>
#include "Room.h"

bool bPlayerQuitting = false;


//Rooms ------
Room* startingRoomPtr = new Room("Starting_Room");
Room* loungePtr = new Room("Lounge");
Room* testRoomPtr = new Room("Locked_room");
EncounterRoom* testRatRoom = new EncounterRoom("Rat_Nest", 3);
Room* allRooms[] = { loungePtr, startingRoomPtr, testRoomPtr };
EncounterRoom* allEncounterRooms[] = { testRatRoom };

//Player
struct Player
{
	static const uint8_t MAX_INV_SIZE = 8;
	Item* m_inventory[MAX_INV_SIZE] = {};
	bool m_bInventoryFull = false;
	bool m_bInEncounter = false;
	int m_health = 100;
	Room* m_currentRoomPtr = startingRoomPtr;
	int m_fistDamage = 5;
};
Player player;
Item** firstEmptyInvSlot = &player.m_inventory[0];
Item** FindFirstEmptyInvSlot();

string TextToLowerCase(string input);
bool CompletedAllEncounters();

//commands -----
std::map <string, std::function<void()>> commands;
void EnterRoom();
void ExitGame();
void ShowAllCommands();
void ShowAllConnectedRooms();
void ShowCurrentRoom();
void SearchObject();
void UseItem();
void ShowInventory();
void ShowPlayerStats();

//Item types ------
HealthPotion* lesserPotion = new HealthPotion("Lesser_HealthPotion", 25);
Weapon* sword = new Weapon("Sword", 25);
Key* blueKey = new Key(KeyColour::Blue);
Item* allItemTypes[] = { sword, lesserPotion, blueKey };
MagicScroll* fireballScroll = new MagicScroll(ScrollType::Fireball);

//Object types -----
Object* chest = new Object(ObjectType::Chest, sword);
Object* cupboard = new Object(ObjectType::Cupboard, blueKey);
Object* allObjects[] = {chest, cupboard};
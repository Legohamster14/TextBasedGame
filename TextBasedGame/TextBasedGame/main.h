#pragma once
#include <iostream>
#include <functional>
#include "Room.h"

bool bPlayerQuitting = false;


Room* startingRoomPtr = new Room("Starting_Room");
Room* loungePtr = new Room("Space_Room");
Room* testRoomPtr = new Room("Locked_room");
Room* allRooms[] = { loungePtr, startingRoomPtr, testRoomPtr };

struct Player
{
	static const uint8_t MAX_INV_SIZE = 8;
	Item* m_inventory[MAX_INV_SIZE] = {};
	bool m_bInventoryFull = false;
	bool m_bInEncounter = false;
	const int8_t m_Health = 100;
	Room* m_currentRoomPtr = startingRoomPtr;
};
Player player;
Item** firstEmptyInvSlot = &player.m_inventory[0];
Item** FindFirstEmptyInvSlot();
string TextToLowerCase(string input);

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

//Item types ------
HealthPotion* lesserPotion = new HealthPotion("Lesser_HealthPotion", 25);
Weapon* sword = new Weapon("Sword", 25);

//Object types -----
Object chest = Object(ObjectType::Chest, sword);
Object cupboard = Object(ObjectType::Cupboard, lesserPotion);
#pragma once
#include <iostream>
#include <functional>
#include "Room.h"

//Rooms ------
Room* startingRoomPtr = new Room("Ratungeon_Entrance");
Room* kitchenRoomPtr = new Room("Kitchen");
Room* studyRoomPtr = new Room("Study");
EncounterRoom* secretTreasureRoomPtr = new EncounterRoom("Secret_Treasure_Room", 5);
Room* diningRoomPtr = new Room("Dining_Room");
EncounterRoom* trophyRoomPtr = new EncounterRoom("Trophy_Room", 3);
Room* stairsPtr = new Room("Stairs");
EncounterRoom* treasureRoomPtr = new EncounterRoom("Treasure_Room", 5);
Room* barracksPtr = new Room("Barracks");
Room* relaxationRoomPtr = new Room("Relaxation_Room");
Room* armoryPtr = new Room("Armory");
EncounterRoom* wineCellarPtr = new EncounterRoom("Wine_Cellar", 7);
EncounterRoom* burialRoomPtr = new EncounterRoom("Burial_Room", 8);
EncounterRoom* summoningRoomPtr = new EncounterRoom("Summoning_Room", 9);
EncounterRoom* ratBreedingRoomPtr = new EncounterRoom("Rat_Breeding_Room", 10);
Room* allRooms[] = { startingRoomPtr, kitchenRoomPtr, studyRoomPtr, secretTreasureRoomPtr, 
	diningRoomPtr, trophyRoomPtr, stairsPtr, treasureRoomPtr, barracksPtr, relaxationRoomPtr,
	armoryPtr, wineCellarPtr, burialRoomPtr, summoningRoomPtr, ratBreedingRoomPtr };
EncounterRoom* allEncounterRooms[] = { secretTreasureRoomPtr, trophyRoomPtr, treasureRoomPtr, 
	wineCellarPtr, burialRoomPtr, summoningRoomPtr, ratBreedingRoomPtr };

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
bool bPlayerQuitting = false;
Item** FindFirstEmptyInvSlot();

string TextToLowerCase(string input);
bool CompletedAllEncounters();
void PlayerDeath();

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
void DropItem();

//Item types ------
HealthPotion* lesserPotion = new HealthPotion("Lesser_HealthPotion", 10);
HealthPotion* mediumPotion = new HealthPotion("Medium_HealthPotion", 25);
HealthPotion* greaterPotion = new HealthPotion("Greater_HealthPotion", 50);
Key* blueKey = new Key(KeyColour::Blue);
Key* redKey = new Key(KeyColour::Red);
Key* purpleKey = new Key(KeyColour::Purple);
Weapon* bluntSword = new Weapon("Dented_Sword", 10);
Weapon* sword = new Weapon("Sword", 25);
Weapon* sharpSword = new Weapon("Sharp_Sword", 40);
MagicScroll* fireballScroll = new MagicScroll(ScrollType::Fireball);
MagicScroll* lightningScroll = new MagicScroll(ScrollType::Lightning);
MagicScroll* iceSpikeScroll = new MagicScroll(ScrollType::IceSpike);
MagicScroll* earthquakeScroll = new MagicScroll(ScrollType::Earthquake);
Item* emptyItem = new Item();
Item* allItemTypes[] = { sword, emptyItem, earthquakeScroll, iceSpikeScroll, lightningScroll, fireballScroll, sharpSword, bluntSword, purpleKey, redKey, greaterPotion, mediumPotion, lesserPotion, blueKey };

//Object types -----
Object* startTable = new Object(ObjectType::Table, bluntSword);
Object* redKeyCabinet = new Object(ObjectType::Cabinet, redKey);
Object* purpleKeyCabinet = new Object(ObjectType::Cabinet, purpleKey);
Object* blueKeyCabinet = new Object(ObjectType::Cabinet, blueKey);
Object* swordTable = new Object(ObjectType::Table, sword);
Object* sharpSwordChest = new Object(ObjectType::Chest, sharpSword);
Object* lesserPotionChest = new Object(ObjectType::Chest, lesserPotion);
Object* lesserPotionCarpet = new Object(ObjectType::Carpet, lesserPotion);
Object* lesserPotionCabinet = new Object(ObjectType::Cabinet, lesserPotion);
Object* lesserPotionTable = new Object(ObjectType::Table, lesserPotion);
Object* mediumPotionChest = new Object(ObjectType::Chest, mediumPotion);
Object* mediumPotionCabinet = new Object(ObjectType::Cabinet, mediumPotion);
Object* greaterPotionChest = new Object(ObjectType::Chest, greaterPotion);
Object* fireballScrollChest = new Object(ObjectType::Chest, fireballScroll);
Object* lightningScrollChest = new Object(ObjectType::Chest, lightningScroll);
Object* iceSpikeScrollChest = new Object(ObjectType::Chest, iceSpikeScroll);
Object* earthquakeScrollChest = new Object(ObjectType::Chest, earthquakeScroll);
Object* emptyChest = new Object(ObjectType::Chest, emptyItem);
Object* emptyTable = new Object(ObjectType::Table, emptyItem);
Object* emptyCabinet = new Object(ObjectType::Cabinet, emptyItem);
Object* emptyCarpet = new Object(ObjectType::Carpet, emptyItem);
Object* allObjects[] = { startTable, redKeyCabinet, purpleKeyCabinet, blueKeyCabinet, swordTable, sharpSwordChest, 
	lesserPotionChest, lesserPotionCarpet, lesserPotionCabinet, lesserPotionTable, mediumPotionChest, mediumPotionCabinet,
	greaterPotionChest, fireballScrollChest, lightningScrollChest, iceSpikeScrollChest, earthquakeScrollChest, emptyChest, 
	emptyTable, emptyCabinet, emptyCarpet };
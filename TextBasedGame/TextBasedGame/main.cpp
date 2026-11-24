#include "main.h"


void ConnectRooms()
{
	startingRoomPtr->AddAccessibleRoom(*kitchenRoomPtr);
	startingRoomPtr->AddAccessibleRoom(*studyRoomPtr);
	studyRoomPtr->AddAccessibleRoom(*diningRoomPtr);
	studyRoomPtr->AddLockedRoom(*secretTreasureRoomPtr, KeyColour::Blue);
	studyRoomPtr->AddAccessibleRoom(*startingRoomPtr);
	kitchenRoomPtr->AddAccessibleRoom(*diningRoomPtr);
	kitchenRoomPtr->AddAccessibleRoom(*startingRoomPtr);
	secretTreasureRoomPtr->AddAccessibleRoom(*kitchenRoomPtr);
	diningRoomPtr->AddAccessibleRoom(*studyRoomPtr);
	diningRoomPtr->AddAccessibleRoom(*kitchenRoomPtr);
	diningRoomPtr->AddAccessibleRoom(*trophyRoomPtr);
	diningRoomPtr->AddAccessibleRoom(*barracksPtr);
	trophyRoomPtr->AddAccessibleRoom(*diningRoomPtr);
	trophyRoomPtr->AddAccessibleRoom(*stairsPtr);
	stairsPtr->AddAccessibleRoom(*trophyRoomPtr);
	stairsPtr->AddLockedRoom(*treasureRoomPtr, KeyColour::Purple);
	treasureRoomPtr->AddAccessibleRoom(*stairsPtr);
	barracksPtr->AddAccessibleRoom(*armoryPtr);
	barracksPtr->AddAccessibleRoom(*relaxationRoomPtr);
	relaxationRoomPtr->AddAccessibleRoom(*barracksPtr);
	armoryPtr->AddAccessibleRoom(*barracksPtr);
	armoryPtr->AddLockedRoom(*wineCellarPtr, KeyColour::Red);
	wineCellarPtr->AddAccessibleRoom(*armoryPtr);
	wineCellarPtr->AddAccessibleRoom(*burialRoomPtr);
	burialRoomPtr->AddAccessibleRoom(*wineCellarPtr);
	burialRoomPtr->AddAccessibleRoom(*summoningRoomPtr);
	summoningRoomPtr->AddAccessibleRoom(*burialRoomPtr);
	summoningRoomPtr->AddAccessibleRoom(*ratBreedingRoomPtr);
	ratBreedingRoomPtr->AddAccessibleRoom(*summoningRoomPtr);
}

void SetUpRoomDescriptions()
{
	ifstream descriptionFile("RoomDescriptions.txt");
	string tempString;
	if (!descriptionFile.is_open())
	{
		cout << "ERROR: \'RoomDescriptions.txt\' is not open.\n";
		return;
	}
	if (!descriptionFile.good())
	{
		cout << "ERROR: \'RoomDescriptions.txt\' is not readable.\n";
		descriptionFile.close();
		return;
	}
	//goes through every line of the file and gives the rooms their descripton
	getline(descriptionFile, tempString);
	startingRoomPtr->SetRoomDescription(tempString);
	getline(descriptionFile, tempString);
	kitchenRoomPtr->SetRoomDescription(tempString);
	getline(descriptionFile, tempString);
	studyRoomPtr->SetRoomDescription(tempString);
	getline(descriptionFile, tempString);
	secretTreasureRoomPtr->SetRoomDescription(tempString);
	getline(descriptionFile, tempString);
	diningRoomPtr->SetRoomDescription(tempString);
	getline(descriptionFile, tempString);
	trophyRoomPtr->SetRoomDescription(tempString);
	getline(descriptionFile, tempString);
	stairsPtr->SetRoomDescription(tempString);
	getline(descriptionFile, tempString);
	treasureRoomPtr->SetRoomDescription(tempString);
	getline(descriptionFile, tempString);
	barracksPtr->SetRoomDescription(tempString);
	getline(descriptionFile, tempString);
	relaxationRoomPtr->SetRoomDescription(tempString);
	getline(descriptionFile, tempString);
	armoryPtr->SetRoomDescription(tempString);
	getline(descriptionFile, tempString);
	wineCellarPtr->SetRoomDescription(tempString);
	getline(descriptionFile, tempString);
	burialRoomPtr->SetRoomDescription(tempString);
	getline(descriptionFile, tempString);
	summoningRoomPtr->SetRoomDescription(tempString);
	getline(descriptionFile, tempString);
	ratBreedingRoomPtr->SetRoomDescription(tempString);

	descriptionFile.close();
}

void SpawnLoot() //Adds all the objects with there loot to each room
{
	startingRoomPtr->AddSearchableObject(*startTable);
	startingRoomPtr->AddSearchableObject(*emptyCarpet);
	relaxationRoomPtr->AddSearchableObject(*blueKeyCabinet);
	kitchenRoomPtr->AddSearchableObject(*purpleKeyCabinet);
	secretTreasureRoomPtr->AddSearchableObject(*redKeyCabinet);
	secretTreasureRoomPtr->AddSearchableObject(*fireballScrollChest);
	treasureRoomPtr->AddSearchableObject(*lightningScrollChest);
	burialRoomPtr->AddSearchableObject(*iceSpikeScrollChest);
	wineCellarPtr->AddSearchableObject(*earthquakeScrollChest);
	barracksPtr->AddSearchableObject(*swordTable);
	armoryPtr->AddSearchableObject(*sharpSwordChest);
	studyRoomPtr->AddSearchableObject(*lesserPotionTable);
	studyRoomPtr->AddSearchableObject(*emptyCabinet);
	diningRoomPtr->AddSearchableObject(*mediumPotionCabinet);
	diningRoomPtr->AddSearchableObject(*emptyTable);
	diningRoomPtr->AddSearchableObject(*emptyCarpet);
	kitchenRoomPtr->AddSearchableObject(*lesserPotionTable);
	barracksPtr->AddSearchableObject(*emptyCarpet);
	armoryPtr->AddSearchableObject(*emptyTable);
	armoryPtr->AddSearchableObject(*emptyCabinet);
	trophyRoomPtr->AddSearchableObject(*greaterPotionChest);
	stairsPtr->AddSearchableObject(*lesserPotionCarpet);
	summoningRoomPtr->AddSearchableObject(*greaterPotionChest);
	ratBreedingRoomPtr->AddSearchableObject(*greaterPotionChest);
}

void OnStart()
{
	cout << "\x1b]0; " << "The Ratungeon" << "\x1b\\";
	for (int i = 0; i < player.MAX_INV_SIZE; i++)
	{
		player.m_inventory[i] = new Item();
	}
	ConnectRooms();
	SetUpRoomDescriptions();
	SpawnLoot();
	cout << "Welcome to The Ratungeon!\n" << 
		"Goal kill all rats.\n" <<
		"-use \'help\' to know what actions you can do.\n";
	ShowCurrentRoom();
}

int main()
{
	OnStart();
	do
	{
		string inputCommand;
		cout << "What would you like to do\n>";
		cin >> inputCommand;
		inputCommand = TextToLowerCase(inputCommand);
		if (commands[inputCommand])
		{
			commands[inputCommand]();
		}
		else
		{
			cout << "\'" << inputCommand << "\' isn't a valid action.\n";
		}
		if (CompletedAllEncounters())
		{
			cout << "You have defeated all the rats in The Ratungeon.\nDo you want to continue playing? (y\\n)\n>";
			string input;
			cin >> input;
			if (input == "no" || input == "n")
			{
				cout << "Thank you for playing The Ratungeon.\n";
				bPlayerQuitting = true;
			}
		}
	} while (!bPlayerQuitting);

	//delet anything in the heap
	for (int i = 0; i < (sizeof(allObjects) / sizeof(Object*)); i++)
	{
		delete allObjects[i];
	}
	for (int i = 0; i < (sizeof(allRooms) / sizeof(Room*)); i++)
	{
		delete allRooms[i];
	}
	for (Item* item : player.m_inventory)
	{
		delete item;
	}
	for (int i = 0; i < (sizeof(allItemTypes) / sizeof(Item*)); i++)
	{
		delete allItemTypes[i];
	}
}

//returns a pointer pointer to the first empty inv slot
Item** FindFirstEmptyInvSlot()
{
	Item** tempItemPtr = nullptr;
	for (int i = 0; i < player.MAX_INV_SIZE; i++)
	{
		if (player.m_inventory[i]->GetName() == "Empty")
		{
			tempItemPtr = &player.m_inventory[i];
			break;
		}
	}
	if (tempItemPtr == nullptr)
	{
		player.m_bInventoryFull = true;
	}
	else
	{
		player.m_bInventoryFull = false;
	}
	return tempItemPtr;
}

//returns a string with only lower case characters
string TextToLowerCase(string input)
{
	string tempString = "";
	for (int i = 0; i < input.size(); i++)
	{
		if (isupper(input[i]))
		{
			tempString += tolower(input[i]);
		}
		else
		{
			tempString += input[i];
		}
	}
	return tempString;
}

bool CompletedAllEncounters()
{
	bool bHasCompletedAllEncounters = true;
	for (int i = 0; i < sizeof(allEncounterRooms) / sizeof(EncounterRoom*); i++)
	{
		if (!allEncounterRooms[i]->GetEncounterCompleted())
		{
			bHasCompletedAllEncounters = false;
			break;
		}
	}
	return bHasCompletedAllEncounters;
}

//called in any situation where the player dies
void PlayerDeath()
{
	cout << "You have been slain. Better luck next time.\n";
	bPlayerQuitting = true;
}

void EnterRoom()
{
	if (player.m_bInEncounter)
	{
		cout << "-You cannot leave the room while in combat\n";
	}
	ShowAllConnectedRooms();
	cout << "Which room would you like to enter?\n>";
	string inputRoom;
	cin >> inputRoom;
	if (player.m_currentRoomPtr->m_unlockedRooms[inputRoom]) // if the inputed room is available go to it
	{
		player.m_currentRoomPtr = player.m_currentRoomPtr->m_unlockedRooms[inputRoom];
		player.m_currentRoomPtr->OnEnter();
	}
	else if (player.m_currentRoomPtr->m_lockedRooms[inputRoom])
	{
		cout << "-\'" << inputRoom << "\' is currently locked, you need a " << player.m_currentRoomPtr->m_lockedRooms[inputRoom]->GetKeyColourText() << " key to unlock this room.\n";
	}
	else
	{
		cout << "-\'" << inputRoom << "\' is an unavailable room.\n";
		return;
	}
	if ((EncounterRoom*)player.m_currentRoomPtr) // if the room has an encounter then mark the player as in combat
	{
		player.m_bInEncounter = true;
	}
}

void ExitGame()
{
	cout << "Exiting game\n";
	bPlayerQuitting = true;
}

void ShowAllCommands() // show any commands/actions the player can do
{
	cout << "Actions are:\n-Help - Tells you all the actions that you can do.\n" << 
		"-Enter - Show you all the rooms an you can pick which one to enter, although it must be .\n" <<
		"-Exit - Exit the game.\n" <<
		"-Show_Rooms - Shows all the connected rooms and whether they are locked or unlocked.\n" << 
		"-Current_Room - Shows the current room you are in.\n" << 
		"-Search - Shows you all the searchable objects in the room you are currently in.\n" << 
		"-Inventory - Displays all the items in your inventory and any stats.\n" <<
		"-Use - Uses an item of your choosing from your invnetory. You can also \'Punch\' enemies if you haven\'t got any weapons\n" <<
		"-Stats - Shows your health, what is in your inventory and whether you are in combat.\n" << 
		"-Drop - Drop an item from your inventory. Warning: this will permanaetly delete the item.\n";
}

void ShowAllConnectedRooms()
{
	cout << "-All connected rooms are:\n";
	for (int i = 0; i < player.m_currentRoomPtr->m_allConnectedRooms.size(); i++)
	{
		cout << i << ". " << player.m_currentRoomPtr->m_allConnectedRooms[i]->GetName() << ": " <<
			((player.m_currentRoomPtr->m_lockedRooms[player.m_currentRoomPtr->m_allConnectedRooms[i]->GetName()]) ? ("Locked") : ("Unlocked")) << std::endl;
	}
}

void ShowCurrentRoom()
{
	cout << "-You are in the " << player.m_currentRoomPtr->GetName() << endl << player.m_currentRoomPtr->GetRoomDescription() << "\n";
}

void SearchObject()
{
	//checkes for if the player can search an object
	if (player.m_bInEncounter)
	{
		cout << "-You cannot search while in combat\n";
	}
	if (player.m_bInventoryFull)
	{
		cout << "-Your inventory is full.\n";
		return;
	}
	if (player.m_currentRoomPtr->m_objects.size() < 1)
	{
		cout << "-There are no objects to search in this room\n";
		return;
	}
	string input;
	cout << "-What do you want to search.\n";
	for (int i = 0; i < player.m_currentRoomPtr->m_objects.size(); i++) // shows all the objects in the room
	{
		cout << i << ". " << player.m_currentRoomPtr->m_objects[i]->GetName() << endl;
	}
	cout << ">";
	cin >> input;
	Item* tempItemPtr = nullptr;
	int searchedObjectIteration = -1;
	for (int i = 0; i < player.m_currentRoomPtr->m_objects.size(); i++) // checks if there is an object that matches the player input
	{
		if (input == player.m_currentRoomPtr->m_objects[i]->GetName())
		{
			tempItemPtr = player.m_currentRoomPtr->m_objects[i]->Search(); // searches the corresponding object
			searchedObjectIteration = i;
			break;
		}
	}
	if (tempItemPtr && tempItemPtr->GetName() != "Empty")
	{
		switch (tempItemPtr->GetItemType()) // stores found item in corresponding item child class
		{
		case ItemType::DefaultItemType:
		{
			*firstEmptyInvSlot = new Item(tempItemPtr);
		}
		break;
		case ItemType::PotionType:
		{
			HealthPotion* tempPotionPtr = (HealthPotion*)tempItemPtr;
			*firstEmptyInvSlot = new HealthPotion(tempPotionPtr);
		}
		break;
		case ItemType::MagicScrollType:
		{
			MagicScroll* tempMagicScrollPtr = (MagicScroll*)tempItemPtr;
			*firstEmptyInvSlot = new MagicScroll(tempMagicScrollPtr);
		}
		break;
		case ItemType::KeyType:
		{
			Key* tempKeyPtr = (Key*)tempItemPtr;
			*firstEmptyInvSlot = new Key(tempKeyPtr);
		}
		break;
		case ItemType::WeaponType:
		{
			Weapon* tempWeaponPtr = (Weapon*)tempItemPtr;
			*firstEmptyInvSlot = new Weapon(tempWeaponPtr);
		}
		break;
		}
		firstEmptyInvSlot = FindFirstEmptyInvSlot();
	}
	if (searchedObjectIteration > -1)
	{
		player.m_currentRoomPtr->RemoveSearchableObject(*player.m_currentRoomPtr->m_objects[searchedObjectIteration]);
	}
	else
	{
		cout << "\'" << input << "\' isn't a valid object.\n";
	}
}

void UseItem()
{
	cout << "-This is what's in your inventory: " << endl;
	ShowInventory();
	cout << "What would you like to use:\n>";
	string inputItem;
	cin >> inputItem;
	if (TextToLowerCase(inputItem) == "punch") // if the player 'punches' then do the same thing as with a weapon
	{
		if (player.m_bInEncounter)
		{
			EncounterRoom* tempEncounterRoomPtr = (EncounterRoom*)player.m_currentRoomPtr;
			cout << "-Punch the rats for " << player.m_fistDamage << " damage\n";
			tempEncounterRoomPtr->ReceiveDamage(player.m_fistDamage);
			cout << "This group of rats are now down to " << ((tempEncounterRoomPtr->GetRatGroupHealth() >= 0) ? (tempEncounterRoomPtr->GetRatGroupHealth()) : (0)) << " health\n";
			if (tempEncounterRoomPtr->GetRatGroupHealth() < 1)
			{
				tempEncounterRoomPtr->CompleteEncounter();
				player.m_bInEncounter = false;
			}
			else
			{
				player.m_health -= tempEncounterRoomPtr->GetRatDamage();
				cout << "The rats now attack you for " << tempEncounterRoomPtr->GetRatDamage() << " damage.\n" <<
					"You are now at " << player.m_health << " health.\n";
			}
		}
		else
		{
			cout << "-You can only punch things when in combat.\n";
		}
		return;
	}
	int itemPosInInv = -1;
	for (int i = 0; i < player.MAX_INV_SIZE; i++) // finds item in inv that player entered
	{
		if (player.m_inventory[i]->GetName() == inputItem)
		{
			itemPosInInv = i;
			break;
		}
	}
	if (itemPosInInv < 0 || itemPosInInv > player.MAX_INV_SIZE)
	{
		cout << "\'" << inputItem << "\' is not in your inventory.\n";
		return;
	}
	switch (player.m_inventory[itemPosInInv]->GetItemType())
	{
	case ItemType::DefaultItemType:
	{
		cout << "You cannot use this item.\n";
		return;
		break;
	}
	case ItemType::PotionType: // gain potions health and remove potion from inv
	{
		HealthPotion* tempPotionPtr = (HealthPotion*)player.m_inventory[itemPosInInv];
		cout << "-You gain " << tempPotionPtr->GetHealthAmount() << " health.\n";
		player.m_health += tempPotionPtr->GetHealthAmount();
		cout << "Your health is now at " << player.m_health << endl;
		delete tempPotionPtr;
		player.m_inventory[itemPosInInv] = new Item();
		firstEmptyInvSlot = FindFirstEmptyInvSlot();
	}
	return;
	break;
	case ItemType::MagicScrollType: // if in an encounter end it and remove scroll from inv
	{
		if (player.m_bInEncounter)
		{
			MagicScroll* tempMagicScrollPtr = (MagicScroll*)player.m_inventory[itemPosInInv];
			EncounterRoom* tempEncounterRoomPtr = (EncounterRoom*)player.m_currentRoomPtr;
			cout << "-You use your " << tempMagicScrollPtr->GetName() << " to send a " << tempMagicScrollPtr->GetScrollTypeText() << " at the group of rats.\n";
			tempEncounterRoomPtr->CompleteEncounter();
			player.m_bInEncounter = false;
			delete tempMagicScrollPtr;
			player.m_inventory[itemPosInInv] = new Item();
			firstEmptyInvSlot = FindFirstEmptyInvSlot();
		}
		else
		{
			cout << "-You can only use magic scrolls in combat\n";
		}
	}
	return;
	break;
	case ItemType::KeyType: // unlock a room if key matches and delete the key if successful
	{
		Key* tempKeyPtr = (Key*)player.m_inventory[itemPosInInv];
		cout << "Which room would you like to unlock:\n";
		player.m_currentRoomPtr->DisplayAllLockedRooms();
		cout << ">";
		string inputRoom;
		cin >> inputRoom;
		if (player.m_currentRoomPtr->m_lockedRooms[inputRoom] && 
			player.m_currentRoomPtr->CanUnlockRoom(*player.m_currentRoomPtr->m_lockedRooms[inputRoom], tempKeyPtr->GetKeyColour()))
		{
			player.m_currentRoomPtr->UnlockRoom(*player.m_currentRoomPtr->m_lockedRooms[inputRoom]);
			cout << "-You have successfully unlocked " << player.m_currentRoomPtr->m_unlockedRooms[inputRoom]->GetName() <<
				" with your " << tempKeyPtr->GetName() << endl;
			delete tempKeyPtr;
			player.m_inventory[itemPosInInv] = new Item();
			firstEmptyInvSlot = FindFirstEmptyInvSlot();
		}
		else if (player.m_currentRoomPtr->m_lockedRooms[inputRoom])
		{
			cout << "-You need a " << player.m_currentRoomPtr->m_lockedRooms[inputRoom]->GetKeyColourText() << " key to unlock this room.\n";
		}
	}
	return;
	break;
	case ItemType::WeaponType: // attack but deal the weapon's damage instead
	{
		if (player.m_bInEncounter)
		{
			Weapon* tempWeaponPtr = (Weapon*)player.m_inventory[itemPosInInv];
			EncounterRoom* tempEncounterRoomPtr = (EncounterRoom*)player.m_currentRoomPtr;
			cout << "-You attack with " << tempWeaponPtr->GetName() << " dealing " << tempWeaponPtr->GetWeaponDamage() << endl;
			tempEncounterRoomPtr->ReceiveDamage(tempWeaponPtr->GetWeaponDamage());
			cout << "This group of rats are now down to " << ((tempEncounterRoomPtr->GetRatGroupHealth() >= 0) ? (tempEncounterRoomPtr->GetRatGroupHealth()) : (0)) << " health\n";
			if (tempEncounterRoomPtr->GetRatGroupHealth() < 1)
			{
				tempEncounterRoomPtr->CompleteEncounter();
			}
			else // rats attack back if they survive player attack
			{
				player.m_health -= tempEncounterRoomPtr->GetRatDamage();
				cout << "The rats now attack you for " << tempEncounterRoomPtr->GetRatDamage() << " damage.\n" <<
					"You are now at " << player.m_health << " health.\n";
				if (player.m_health < 1)
				{
					PlayerDeath();
				}
			}
		}
		else
		{
			cout << "-You can only use weapons in combat\n";
		}
	}
	return;
	break;
	}

	cout << "\'" << inputItem << "\' is not a valid item.\n";
}

void ShowInventory()
{
	for (int i = 0; i < player.MAX_INV_SIZE; i++)
	{
		cout << "Slot " << i + 1 << ". " << player.m_inventory[i]->GetName();
		switch (player.m_inventory[i]->GetItemType())
		{
		case ItemType::WeaponType:
		{
			Weapon* tempWeaponPtr = (Weapon*)player.m_inventory[i];
			cout << ", damage: " << tempWeaponPtr->GetWeaponDamage();
		}
		break;
		case ItemType::PotionType:
		{
			HealthPotion* tempPotionPtr = (HealthPotion*)player.m_inventory[i];
			cout << ", health: " << tempPotionPtr->GetHealthAmount();
		}
		break;
		}
		cout << endl;
	}
}

void ShowPlayerStats()
{
	cout << "-You currently have " << player.m_health << " health.\n" <<
		"You are" << ((player.m_bInEncounter) ? (" ") : (" not ")) << "currently in combat.\n" <<
		"These are the items in your inventory:\n";
	ShowInventory();
}

void DropItem() // allows the player to get rid of items at any time
{
	cout << "-Which item do you want to drop:\n";
	ShowInventory();
	cout << ">";
	string input;
	cin >> input;
	int itemPosInInv = -1;
	for (int i = 0; i < player.MAX_INV_SIZE; i++)
	{
		if (player.m_inventory[i]->GetName() == input)
		{
			itemPosInInv = i;
			break;
		}
	}
	if (itemPosInInv < -1 || itemPosInInv > player.MAX_INV_SIZE)
	{
		cout << "\'" << input << "\' is not in your inventory.\n";
		return;
	}
	cout << "You have dropped \'" << player.m_inventory[itemPosInInv]->GetName() << "\' from slot " << itemPosInInv + 1 << endl;
	delete player.m_inventory[itemPosInInv];
	player.m_inventory[itemPosInInv] = new Item();
}

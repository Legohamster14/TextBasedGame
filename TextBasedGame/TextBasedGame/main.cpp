#include "main.h"


void ConnectRooms()
{
	startingRoomPtr->AddAccessibleRoom(*loungePtr);
	startingRoomPtr->AddLockedRoom(*testRoomPtr, KeyColour::Blue);
	loungePtr->AddAccessibleRoom(*startingRoomPtr);
	loungePtr->AddAccessibleRoom(*testRatRoom);
}

void SetUpRoomDescriptions()
{
	ifstream descriptionFile("RoomDescriptions.txt");
	string tempString;
	getline(descriptionFile, tempString);
	startingRoomPtr->SetRoomDescription(tempString);
	getline(descriptionFile, tempString);
	loungePtr->SetRoomDescription(tempString);
	getline(descriptionFile, tempString);
	testRoomPtr->SetRoomDescription(tempString);

	if (descriptionFile.is_open())
	{
		descriptionFile.close();
	}
}

void SpawnLoot()
{
	startingRoomPtr->AddSearchableObject(*chest);
	startingRoomPtr->AddSearchableObject(*cupboard);
}

void OnStart()
{
	for (int i = 2; i < player.MAX_INV_SIZE; i++)
	{
		player.m_inventory[i] = new Item();
	}
	player.m_inventory[0] = new Weapon(sword);
	player.m_inventory[1] = new MagicScroll(fireballScroll);
	ConnectRooms();
	SetUpRoomDescriptions();
	SpawnLoot();
	cout << "Welcome to game\n-use \'help\' to know what actions you can do\n";
	ShowCurrentRoom();
}

int main()
{
	OnStart();
	commands["exit"] = ExitGame;
	commands["help"] = ShowAllCommands;
	commands["enter"] = EnterRoom;
	commands["show_rooms"] = ShowAllConnectedRooms;
	commands["current_room"] = ShowCurrentRoom;
	commands["search"] = SearchObject;
	commands["use"] = UseItem;
	commands["inventory"] = ShowInventory;
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

	} while (!bPlayerQuitting);

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
	if (player.m_currentRoomPtr->m_unlockedRooms[inputRoom])
	{
		player.m_currentRoomPtr = player.m_currentRoomPtr->m_unlockedRooms[inputRoom];
		player.m_currentRoomPtr->OnEnter();
	}
	else
	{
		cout << inputRoom << " is an unavailable room.\n";
		return;
	}
	if ((EncounterRoom*)player.m_currentRoomPtr)
	{
		player.m_bInEncounter = true;
	}
}

void ExitGame()
{
	cout << "Exiting game\n";
	bPlayerQuitting = true;
}

void ShowAllCommands()
{
	cout << "Actions are:\n-Help - Tells you all the actions that you can do.\n" << 
		"-Enter RoomName - Enters the room from the name given if it is availabel.\n" <<
		"-Exit - Exit the game.\n" <<
		"-Show_Rooms - Shows all the connected rooms and whether they are locked or unlocked.\n" << 
		"-Current_Room - Shows the current room you are in.\n" << 
		"-Search - Shows you all the searchable objects in the room you are currently in.\n" << 
		"-Inventory - Displays all the items in your inventory and any stats\n" <<
		"-Use - Uses an item of your choosing from your invnetory\n";
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
	for (int i = 0; i < player.m_currentRoomPtr->m_objects.size(); i++)
	{
		cout << i << ". " << player.m_currentRoomPtr->m_objects[i]->GetName() << endl;
	}
	cout << ">";
	cin >> input;
	Item* tempItemPtr = nullptr;
	int searchedObjectIteration = -1;
	for (int i = 0; i < player.m_currentRoomPtr->m_objects.size(); i++)
	{
		if (input == player.m_currentRoomPtr->m_objects[i]->GetName())
		{
			tempItemPtr = player.m_currentRoomPtr->m_objects[i]->Search();
			searchedObjectIteration = i;
			break;
		}
	}
	if (tempItemPtr && tempItemPtr->GetName() != "Empty")
	{
		switch (tempItemPtr->GetItemType())
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
	cout << "This is what's in your inventory: " << endl;
	ShowInventory();
	cout << "What would you like to use:\n>";
	string inputItem;
	cin >> inputItem;
	int itemPosInInv = -1;
	for (int i = 0; i < player.MAX_INV_SIZE; i++)
	{
		if (player.m_inventory[i]->GetName() == inputItem)
		{
			itemPosInInv = i;
			break;
		}
	}
	if (itemPosInInv < -1 || itemPosInInv > player.MAX_INV_SIZE)
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
	case ItemType::PotionType:
	{
		HealthPotion* tempPotionPtr = (HealthPotion*)player.m_inventory[itemPosInInv];
		cout << "-You gain " << tempPotionPtr->GetHealthAmount() << " health.\n";
		player.m_health += tempPotionPtr->GetHealthAmount();
		cout << "Your health is now at " << player.m_health << endl;
		delete tempPotionPtr;
		player.m_inventory[itemPosInInv] = new Item();
		firstEmptyInvSlot = FindFirstEmptyInvSlot();
	}
	break;
	case ItemType::MagicScrollType:
	{
		if (player.m_bInEncounter)
		{
			MagicScroll* tempMagicScrollPtr = (MagicScroll*)player.m_inventory[itemPosInInv];
		}
		else
		{
			cout << "-You can only use magic scrolls in combat\n";
		}
	}
	break;
	case ItemType::KeyType:
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
			cout << "You have successfully unlocked " << player.m_currentRoomPtr->m_unlockedRooms[inputRoom]->GetName() <<
				" with your " << tempKeyPtr->GetName() << endl;
			delete tempKeyPtr;
			player.m_inventory[itemPosInInv] = new Item();
			firstEmptyInvSlot = FindFirstEmptyInvSlot();
		}
	}
	break;
	case ItemType::WeaponType:
	{
		if (player.m_bInEncounter)
		{
			Weapon* tempWeaponPtr = (Weapon*)player.m_inventory[itemPosInInv];
			EncounterRoom* tempEncounterRoomPtr = (EncounterRoom*)player.m_currentRoomPtr;
			cout << "You attack with " << tempWeaponPtr->GetName() << " dealing " << tempWeaponPtr->GetWeaponDamage() << endl;
			tempEncounterRoomPtr->ReceiveDamage(tempWeaponPtr->GetWeaponDamage());
			cout << "This group of rats are now down to " << ((tempEncounterRoomPtr->GetRatGroupHealth() >= 0) ? (tempEncounterRoomPtr->GetRatGroupHealth()) : (0)) << " health\n";
			if (tempEncounterRoomPtr->GetRatGroupHealth() < 1)
			{
				tempEncounterRoomPtr->CompleteEncounter();
				player.m_bInEncounter = false;
			}
		}
		else
		{
			cout << "-You can only use weapons in combat\n";
		}
	}
	break;
	}
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
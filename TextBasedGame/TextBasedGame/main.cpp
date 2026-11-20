#include "main.h"


void ConnectRooms()
{
	startingRoomPtr->AddAccessibleRoom(*loungePtr);
	startingRoomPtr->AddLockedRoom(*testRoomPtr);
	loungePtr->AddAccessibleRoom(*startingRoomPtr);
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
	startingRoomPtr->AddSearchableObject(chest);
	startingRoomPtr->AddSearchableObject(cupboard);
}

void OnStart()
{
	for (int i = 0; i < player.MAX_INV_SIZE; i++)
	{
		player.m_inventory[i] = new Item();
	}
	ConnectRooms();
	SetUpRoomDescriptions();
	SpawnLoot();
	cout << "Welcome to game\n-use \'help\' to know what actions you can do\n";
	ShowCurrentRoom();
}

int main()
{
	OnStart();
	string arg1;
	string arg2;
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
		cout << '>';
		cin >> inputCommand;
		cin >> arg1;
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

	for (int i = 0; i < (sizeof(allRooms) / sizeof(Room*)); i++)
	{
		delete allRooms[i];
	}
	for (Item* item : player.m_inventory)
	{
		delete item;
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
		"-Search - Shows you all the searchable items in the room you are currently in.\n";
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
		cout << player.m_currentRoomPtr->m_objects[i]->GetName() << ((i == (player.m_currentRoomPtr->m_objects.size() - 1)) ? ("") : (", "));
	}
	cout << endl << ">";
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
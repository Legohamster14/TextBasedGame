#include "main.h"


void ConnectRooms()
{
	startingRoom->AddAccessibleRoom(*loungePtr);
	startingRoom->AddLockedRoom(*testRoomPtr);
}

void SetUpRoomDescriptions()
{
	ifstream descriptionFile("RoomDescriptions.txt");
	string tempString;
	getline(descriptionFile, tempString);
	startingRoom->SetRoomDescription(tempString);
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
	commands["enter"] = [&arg1]() {EnterRoom(arg1);};
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
		//cin >> arg2;
		inputCommand = TextToLowerCase(inputCommand);
		if (commands[inputCommand])
		{
			commands[inputCommand]();
		}
		else
		{
			cout << "invalid function call\n";
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

void EnterRoom(std::string roomName)
{
	if (player.m_currentRoomPtr->m_unlockedRooms[roomName])
	{
		player.m_currentRoomPtr = player.m_currentRoomPtr->m_unlockedRooms[roomName];
		cout << "entering: " << player.m_currentRoomPtr->GetName() << endl <<
			player.m_currentRoomPtr->GetRoomDescription() << "\n";
	}
	else
	{
		cout << roomName << " is an unavailable room.\n";
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
	cout << "All connected rooms are:\n";
	for (int i = 0; i < player.m_currentRoomPtr->m_allConnectedRooms.size(); i++)
	{
		cout << i << ". " << player.m_currentRoomPtr->m_allConnectedRooms[i]->GetName() << ": " <<
			((player.m_currentRoomPtr->m_lockedRooms[player.m_currentRoomPtr->m_allConnectedRooms[i]->GetName()]) ? ("Locked") : ("Unlocked")) << std::endl;
	}
}

void ShowCurrentRoom()
{
	cout << "You are in the " << player.m_currentRoomPtr->GetName() << endl << player.m_currentRoomPtr->GetRoomDescription() << "\n";
	//give room description again
}

void SearchObject()
{
	if (player.m_bInventoryFull)
	{
		cout << "Your inventory is full.\n";
		return;
	}
	if (player.m_currentRoomPtr->m_objects.size() < 1)
	{
		cout << "There are no objects to search in this room\n";
		return;
	}
	string input;
	cout << "What do you want to search.\n";
	for (int i = 0; i < player.m_currentRoomPtr->m_objects.size(); i++)
	{
		cout << player.m_currentRoomPtr->m_objects[i].GetName() << ((i == (player.m_currentRoomPtr->m_objects.size() - 1)) ? ("") : (", "));
	}
	cout << endl << ">";
	cin >> input;
	Item* tempItemPtr = nullptr;
	for (int i = 0; i < player.m_currentRoomPtr->m_objects.size(); i++)
	{
		if (input == player.m_currentRoomPtr->m_objects[i].GetName())
		{
			tempItemPtr = player.m_currentRoomPtr->m_objects[i].Search();
			player.m_currentRoomPtr->RemoveSearchableObject(player.m_currentRoomPtr->m_objects[i]);
			break;
		}
	}
	if (tempItemPtr->GetName() != "Empty")
	{
		*firstEmptyInvSlot = new Item(tempItemPtr);
		firstEmptyInvSlot = FindFirstEmptyInvSlot();
	}
}

void UseItem()
{

}

void ShowInventory()
{
	for (int i = 0; i < player.MAX_INV_SIZE; i++)
	{
		cout << i << ". " << player.m_inventory[i]->GetName();
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
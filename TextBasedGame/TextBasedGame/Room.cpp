#include "Room.h"
#include <iostream>

void Room::SetKeyColour(KeyColour keyColour)
{
	m_keyToUnlock = keyColour;
}

Room::Room()
{
	m_roomName = "DefaultName";
}

Room::Room(string roomName)
{
	m_roomName = roomName;
}

Room::~Room() {}

string Room::GetName() const
{
	return m_roomName;
}

string Room::GetRoomDescription() const
{
	return m_roomDescription;
}

void Room::SetRoomDescription(string input)
{
	m_roomDescription = input;
}

void Room::OnEnter() const
{
	std::cout << "-Entering: " << m_roomName << std::endl <<
		m_roomDescription << std::endl;
}

void Room::AddAccessibleRoom(Room& room, bool bNewRoom)
{
	m_unlockedRooms[room.GetName()] = &room;
	if (bNewRoom)
	{
		m_allConnectedRooms.push_back(&room);
	}
}

void Room::AddLockedRoom(Room& room, KeyColour keyColour)
{
	room.SetKeyColour(keyColour);
	m_lockedRooms[room.GetName()] = &room;
	m_allConnectedRooms.push_back(&room);
}

void Room::AddSearchableObject(Object& object)
{
	Object* tempPtr = new Object(&object);
	m_objects.push_back(make_unique<Object>(tempPtr));
}

void Room::RemoveSearchableObject(Object& object)
{
	for (int i = 0; i < m_objects.size(); i++)
	{
		if (m_objects[i]->GetName() == object.GetName())
		{
			m_objects[i]->DeleteHiddenItem();
			m_objects.erase(m_objects.begin() + i);
			break;
		}
	}
}

void Room::DisplayAllLockedRooms() 
{
	for (int i = 0; i < m_allConnectedRooms.size(); i++)
	{
		std::cout << (m_lockedRooms[m_allConnectedRooms[i]->GetName()] ? (to_string(i) + std::string(". ") + m_allConnectedRooms[i]->GetName() + std::string("\n")) : (""));
	}
}

bool Room::CanUnlockRoom(Room& lockedRoom, KeyColour colour) 
{
	return ((colour == lockedRoom.m_keyToUnlock &&
		m_lockedRooms[lockedRoom.GetName()]) ? (true) : (false));
}

void Room::UnlockRoom(Room& room)
{
	AddAccessibleRoom(*m_lockedRooms[room.GetName()]);
	m_lockedRooms.erase(room.GetName());
}

std::string Room::GetKeyColourText()
{
	string tempString = "";
	switch (m_keyToUnlock)
	{
	case KeyColour::Blue:
		tempString = "blue";
		break;
	case KeyColour::Purple:
		tempString = "purple";
		break;
	case KeyColour::Red:
		tempString = "red";
		break;
	default:
		tempString = "";
		break;
	}
	return tempString;
}

//EncounterRoom
void EncounterRoom::SetRatGroupStats(int ratAmount) // set rat group damage and health based on the size
{
	m_ratGroup.m_groupHealth *= ratAmount;
	m_ratGroup.m_groupDamage *= ratAmount;
}

EncounterRoom::EncounterRoom() : Room()
{
	m_roomName = "DefaultName";
	m_ratGroup.m_groupAmount = 1;
	SetRatGroupStats(m_ratGroup.m_groupAmount);
}

EncounterRoom::EncounterRoom(string name, int ratAmount) : Room(name)
{
	m_roomName = name;
	m_ratGroup.m_groupAmount = ratAmount;
	SetRatGroupStats(m_ratGroup.m_groupAmount);
}

void EncounterRoom::OnEnter() const
{
	std::cout << "-Entering: " << m_roomName << std::endl <<
		m_roomDescription << std::endl;
	if (!m_bEncounterCompleted)
	{
		cout << "There are " << m_ratGroup.m_groupAmount << " rats in here, they have a total health pool of " << m_ratGroup.m_groupHealth << endl;
	}
}

bool EncounterRoom::GetEncounterCompleted() const
{
	return m_bEncounterCompleted;
}

void EncounterRoom::CompleteEncounter()
{
	m_bEncounterCompleted = true;
	cout << "You have successfully slain this group of " << m_ratGroup.m_groupAmount << " rats\n";
	m_ratGroup.m_groupHealth = 0;
}

int EncounterRoom::GetRatGroupHealth() const
{
	return m_ratGroup.m_groupHealth;
}

int EncounterRoom::GetRatDamage() const
{
	return m_ratGroup.m_groupDamage;
}

void EncounterRoom::ReceiveDamage(int damage)
{
	m_ratGroup.m_groupHealth -= damage;
}

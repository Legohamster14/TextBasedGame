#include "Room.h"
#include <iostream>

Room::Room()
{
	m_roomName = "DefaultName";
}

Room::Room(string roomName)
{
	m_roomName = roomName;
}

Room::~Room()
{
	//for (int i = 0; i < m_objects.size(); i++)
	//{
	//	m_objects.pop_back();
	//}
}

string Room::GetName()
{
	return m_roomName;
}

string Room::GetRoomDescription()
{
	return m_roomDescription;
}

void Room::SetRoomDescription(string input)
{
	m_roomDescription = input;
}

void Room::OnEnter()
{
	std::cout << "-Entering: " << m_roomName << std::endl <<
		m_roomDescription << std::endl;
}

void Room::AddAccessibleRoom(Room& room)
{
	m_unlockedRooms[room.GetName()] = &room;
	m_allConnectedRooms.push_back(&room);
}

void Room::AddLockedRoom(Room& room)
{
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

bool Room::CanUnlockRoom(KeyColour colour)
{
	return false;
}

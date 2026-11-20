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
	//Object* tempPtr = &object;
	m_objects.push_back(new Object(&object));
}

void Room::RemoveSearchableObject(Object& object)
{
	for (int i = 0; i < m_objects.size(); i++)
	{
		if (m_objects[i]->GetName() == object.GetName())
		{
			Object* tempPtr = m_objects[i];
			m_objects.erase(m_objects.begin() + i);
			delete tempPtr;
			break;
		}
	}
}

#include "Room.h"

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

void Room::OnEnter()
{
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

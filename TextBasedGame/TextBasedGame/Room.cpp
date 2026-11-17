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
	m_availableRooms[room.GetName()] = &room;
}

void Room::AddLockedRoom(Room& room)
{
	m_lockedRooms[room.GetName()] = &room;
}

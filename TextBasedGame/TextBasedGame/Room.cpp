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

void Room::AddSearchableObject(Object object)
{
	m_objects.push_back(object);
}

void Room::RemoveSearchableObject(Object& object)
{

}

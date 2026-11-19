#pragma once

#include <map>
#include <string>
#include <vector>
#include <fstream>
#include "Object.h"

using namespace std;

class Room
{
protected:
	std::string m_roomName;
	string m_roomDescription;
public:
	Room();
	Room(string roomName);
	~Room();
	std::map<string, Room*> m_unlockedRooms;
	std::map<string, Room*> m_lockedRooms;
	std::vector<Room*> m_allConnectedRooms;
	std::vector<Object> m_objects;
	string GetName();
	string GetRoomDescription();
	void SetRoomDescription(string input);
	virtual void OnEnter();
	void AddAccessibleRoom(Room& room);
	void AddLockedRoom(Room& room);
	void AddSearchableObject(Object object);
	void RemoveSearchableObject(Object& object);
};


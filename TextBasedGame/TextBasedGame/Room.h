#pragma once

#include <map>
#include <string>

using namespace std;

class Room
{
protected:
	std::string m_roomName;
public:
	Room();
	Room(string roomName);
	~Room();
	std::map<string, Room*> m_availableRooms;
	std::map<string, Room*> m_lockedRooms;
	string GetName();
	virtual void OnEnter();
	void AddAccessibleRoom(Room& room);
	void AddLockedRoom(Room& room);
};


#pragma once

#include <map>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

class Room
{
protected:
	std::string m_roomName;
public:
	Room();
	Room(string roomName);
	~Room();
	std::map<string, Room*> m_unlockedRooms;
	std::map<string, Room*> m_lockedRooms;
	std::vector<Room*> m_allConnectedRooms;
	string GetName();
	virtual void OnEnter();
	void AddAccessibleRoom(Room& room);
	void AddLockedRoom(Room& room);
};


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
	KeyColour m_keyToUnlock = KeyColour::Blank;
	void SetKeyColour(KeyColour keyColour);
public:
	Room();
	Room(string roomName);
	~Room();
	std::map<string, Room*> m_unlockedRooms;
	std::map<string, Room*> m_lockedRooms;
	std::vector<Room*> m_allConnectedRooms;
	std::vector<std::unique_ptr<Object>> m_objects;
	string GetName() const;
	string GetRoomDescription() const;
	void SetRoomDescription(string input);
	virtual void OnEnter() const;
	void AddAccessibleRoom(Room& room, bool bNewRoom = true);
	void AddLockedRoom(Room& room, KeyColour keyColour);
	void AddSearchableObject(Object& object);
	void RemoveSearchableObject(Object& object);
	void DisplayAllLockedRooms();
	bool CanUnlockRoom(Room& lockedRoom, KeyColour colour);
	void UnlockRoom(Room& room);
	std::string GetKeyColourText();
};

struct RatGroup
{
	int m_groupHealth = 10;
	int m_groupDamage = 1;
	int m_groupAmount;
};

class EncounterRoom : public Room
{
private:
	RatGroup m_ratGroup;
	bool m_bEncounterCompleted = false;
	void SetRatGroupStats(int ratAmount);
public:
	EncounterRoom();
	EncounterRoom(string name, int ratAmount);
	void OnEnter() const override;
	bool GetEncounterCompleted() const;
	void CompleteEncounter();
	int GetRatGroupHealth() const;
	int GetRatDamage() const;
	void ReceiveDamage(int damage);
};
#pragma once
#include "Room.h"
class EncounterRoom : public Room
{
public:
	void OnEnter() override;
	//EncounterRoom();// : Room();
	//EncounterRoom(string roomName);//:Room(string roomName);
};


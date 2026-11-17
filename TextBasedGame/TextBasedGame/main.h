#pragma once
#include <iostream>
#include <functional>
#include "Room.h"

bool bPlayerQuitting = false;


Room* entranceHallPtr = new Room("Entrance Hall");
Room* loungePtr = new Room("Space_Room");
Room* testRoomPtr = new Room("Locked_room");
Room* currentRoomPtr = entranceHallPtr;
Room* allRooms[2] = { currentRoomPtr, entranceHallPtr };

string TextToLowerCase(string input);

//commands
std::map <string, std::function<void()>> commands;
void EnterRoom(std::string roomName);
void ExitGame();
void ShowAllCommands();
void ShowAllConnectedRooms();
void ShowCurrentRoom();

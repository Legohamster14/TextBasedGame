#pragma once
#include <iostream>
#include <functional>
#include "Room.h"

bool bPlayerQuitting = false;


Room* entranceHallPtr = new Room("Entrance Hall");
Room* currentRoom = entranceHallPtr;

string TextToLowerCase(string input);

//commands
std::map <string, std::function<void()>> commands;
void EnterRoom(std::string roomName);
void ExitGame();
void ShowAllCommands();
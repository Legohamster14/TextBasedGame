#include "main.h"


void ConnectRooms()
{
    entranceHallPtr->AddAccessibleRoom(*loungePtr);
    entranceHallPtr->AddLockedRoom(*testRoomPtr);
}

void OnStart()
{
    ConnectRooms();
    cout << "Welcome to game\n-use \'help\' to know what actions you can do\n-Entrance room description-\n";
}

int main()
{
    OnStart();
    //std::function<void(string)> tempFuncPtr = EnterRoom;
    string arg1;
    string arg2;
    commands["exit"] = ExitGame;
    commands["help"] = ShowAllCommands;
    commands["enter"] = [&arg1]() {EnterRoom(arg1);};
    commands["show_rooms"] = ShowAllConnectedRooms;
    commands["current_room"] = ShowCurrentRoom;
    ifstream RoomDesc("RoomDescriptions.txt");
    getline(RoomDesc, arg2);
    cout << arg2;
    do
    {
        string inputCommand;
        cout << '>';
        cin >> inputCommand;
        cin >> arg1;
        //cin >> arg2;
        inputCommand = TextToLowerCase(inputCommand);
        if (commands[inputCommand])
        {
            commands[inputCommand]();
        }
        else
        {
            cout << "invalid function call\n";
        }

    } while (!bPlayerQuitting);

    for (int i = 0; i < (sizeof(allRooms) / sizeof(Room*)); i++)
    {
        delete allRooms[i];
    }
}

string TextToLowerCase(string input)
{
    string tempString = "";
    for (int i = 0; i < input.size(); i++)
    {
        if (isupper(input[i]))
        {
            tempString += tolower(input[i]);
        }
        else
        {
            tempString += input[i];
        }
    }
    return tempString;
}

void EnterRoom(std::string roomName)
{
    if (currentRoomPtr->m_unlockedRooms[roomName])
    {
        currentRoomPtr = currentRoomPtr->m_unlockedRooms[roomName];
        cout << "entering: " << currentRoomPtr->GetName();
    }
    else
    {
        cout << roomName << " is an unavailable room.\n";
    }
}

void ExitGame()
{
    cout << "Exiting game\n";
    bPlayerQuitting = true;
}

void ShowAllCommands()
{
    cout << "Actions are:\n-Help - Tells you all the actions that you can do\n" << 
        "-Enter RoomName - Enters the room from the name given if it is availabel\n" <<
        "-Exit - Exit the game\n" <<
        "-Show_Rooms - Shows all the connected rooms and whether they are locked or unlocked\n" << 
        "-Current_Room - Shows the current room you are in\n";
}

void ShowAllConnectedRooms()
{
    cout << "All connected rooms are:\n";
    for (int i = 0; i < currentRoomPtr->m_allConnectedRooms.size(); i++)
    {
        cout << i << ". " << currentRoomPtr->m_allConnectedRooms[i]->GetName() << ": " <<
            ((currentRoomPtr->m_lockedRooms[currentRoomPtr->m_allConnectedRooms[i]->GetName()]) ? ("Locked") : ("Unlocked")) << std::endl;
    }
}

void ShowCurrentRoom()
{
    cout << "You are in the " << currentRoomPtr->GetName() << endl;
    //give room description again
}

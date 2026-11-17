#include "main.h"

int main()
{
    //std::function<void(string)> tempFuncPtr = EnterRoom;
    commands["exit"] = ExitGame;
    commands["help"] = ShowAllCommands;
    do
    {
        string inputCommand;
        string arg1;
        string arg2;
        cout << '>';
        cin >> inputCommand;
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
    if (currentRoom->m_availableRooms[roomName])
    {
        currentRoom = currentRoom->m_availableRooms[roomName];
        cout << "entering: " << currentRoom->GetName();
    }
    else
    {
        cout << roomName << "is an unavailable room.\n";
    }
}

void ExitGame()
{
    cout << "Exiting game\n";
    bPlayerQuitting = true;
}

void ShowAllCommands()
{
    cout << "Actions are:\n-Help\n-EnterRoom RoomName\n-Exit\n";
}

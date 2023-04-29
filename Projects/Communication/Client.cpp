#include "Function.hpp"
int Socket = -1;
int main()
{
    string ServerIP;
    cout << "Input ServerIP: ";
    cin >> ServerIP;
    Socket = socket(AF_INET, SOCK_STREAM, 0);
    ASSERT(Socket != -1);
    sockaddr_in ServerAddress;
    memset(&ServerAddress, 0, sizeof(ServerAddress));
    ServerAddress.sin_family = AF_INET;
    ServerAddress.sin_port = htons(SERVER_PORT);
    ServerAddress.sin_addr.s_addr = inet_addr(ServerIP.c_str());
    ASSERT(connect(Socket, (struct sockaddr *)&ServerAddress, sizeof(ServerAddress)) == 0);

    while (1)
    {
        char Function = 0;
        cout << "Please input: (\33[0;4mE\33[0mxit, \33[0;4mT\33[0mext)";
        Function = getchar();
        if (Function == 10)
            continue;
        while (getchar() != 10)
            ;
        Message SendMessage;
        memset(&SendMessage, 0, sizeof(SendMessage));
        switch (Function)
        {
        case 'e':
        case 'E':
        {
            SendMessage.DataType = SendMessage.GOODBYE;
            send(Socket, (char *)&SendMessage, sizeof(SendMessage), 0);
            break;
        }
        case 't':
        case 'T':
        {
            string InputText;
            cout << "Input the text you want to say(max: 1024 chars): ";
            getline(cin, InputText);
            SendMessage.DataType = SendMessage.TEXT;
            InputText = InputText.substr(0, min((int)InputText.size(), 1024));
            strcpy(SendMessage.Data.TextData, InputText.c_str());
            send(Socket, (char *)&SendMessage, sizeof(SendMessage), 0);
            break;
        }
        default:
            break;
        }
    }

    close(Socket);
    return 0;
}
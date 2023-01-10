#include "Function.hpp"
int ListenSocket = -1;
sockaddr_in ServerAddress;
vector<queue<Message>> SendMessageList;
vector<queue<Message>> ReceiveMessageList;
vector<thread> ThreadList;
void Do(int ID, int Socket, sockaddr_in ClientAddress)
{
    cout << "Connected: " << inet_ntoa(ClientAddress.sin_addr) << endl;
    while (1)
    {
        fd_set TestList;
        FD_ZERO(&TestList);
        FD_SET(Socket, &TestList);
        struct timeval SelectTimeout;
        SelectTimeout.tv_sec = 60;
        SelectTimeout.tv_usec = 0;
        switch (select(Socket + 1, &TestList, 0, 0, &SelectTimeout))
        {
        case -1:
            ASSERT(-1);
            break;
        case 0:
            break;
        case 1:
            Message ReceivedData;
            memset(&ReceivedData, 0, sizeof(ReceivedData));
            int ReceivedSize = recv(Socket, (char *)&ReceivedData, sizeof(ReceivedData), 0);
            ASSERT(ReceivedSize > 0);
            if (ReceivedData.DataType == ReceivedData.GOODBYE)
            {
                break;
            }
            ReceiveMessageList[ID].push(ReceivedData);
            break;
        }

        if (SendMessageList[ID].size() != 0)
        {
            Message SendedData = SendMessageList[ID].front();
            SendMessageList[ID].pop();
            memset(&SendedData, 0, sizeof(SendedData));
            int SendedSize = send(Socket, (char *)&SendedData, sizeof(SendedData), 0);
            ASSERT(SendedSize > 0);
        }

        usleep(1000000);
    }
    close(Socket);
}
int main()
{
    ListenSocket = socket(AF_INET, SOCK_STREAM, 0);
    ASSERT(ListenSocket != -1);
    memset(&ServerAddress, 0, sizeof(ServerAddress));
    ServerAddress.sin_family = AF_INET;
    ServerAddress.sin_addr.s_addr = htonl(INADDR_ANY);
    ServerAddress.sin_port = htons(SERVER_PORT);
    ASSERT(bind(ListenSocket, (sockaddr *)&ServerAddress, sizeof(ServerAddress)) == 0);
    ASSERT(listen(ListenSocket, 5) == 0);
    while (1)
    {
        sockaddr_in ClientAddress;
        int ClientAddressSize = sizeof(sockaddr_in);
        int CurrentSocket = accept(ListenSocket, (sockaddr *)&ClientAddress, (socklen_t *)&ClientAddressSize);
        ASSERT(CurrentSocket != -1);
        Message HelloMessage;
        HelloMessage.DataType = HelloMessage.HELLO;
        SendMessageList.resize(SendMessageList.size() + 1);
        SendMessageList[SendMessageList.size() - 1].push(HelloMessage);
        ReceiveMessageList.resize(ReceiveMessageList.size() + 1);
        ThreadList.push_back(thread(Do, SendMessageList.size() - 1, CurrentSocket, ClientAddress));
    }
    close(ListenSocket);
    return 0;
}
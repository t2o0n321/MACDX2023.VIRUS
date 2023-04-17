#include <iostream>
#include <thread>
#include <map>
#include "ssocket.hpp"
#include "cmder.hpp"
using namespace std;

map<int, string> clients;
int currentClient = -1;

void test()
{
    cout << "Testing" << endl;
}

void onClientConnect(MySocket::Socket serverSocket)
{
    while (true)
    {
        pair<int, sockaddr_in> clientData = serverSocket.Accept();
        if (clientData.first < 0)
        {
            cout << "Failed to connect to client ... " << endl;
            continue;
        }

        // Get client info
        socklen_t cAddrLen = sizeof(clientData.second);
        getpeername(clientData.first, (sockaddr *)&clientData.second, &cAddrLen);
        string clientIP = inet_ntoa(clientData.second.sin_addr);
        clients[clientData.first] = clientIP;
        cout << "Connected to " << clientIP << " . Client_Socket: " << clientData.first << endl;
    }
}

int main()
{
    MySocket::Socket socket(23534);

    socket.Init();
    socket.Listen(test);

    thread handleClient(onClientConnect, socket);
    handleClient.detach();

    string cmd;
    while (1)
    {
        std::cin >> cmd;
        if (cmd == "/quit")
        {
            break;
        }
        // char *eCmd = CreateCmd(cmd);
        else if (cmd == "/help")
        {
            displayHelp();
        }
        else if (cmd == "/list_users")
        {
            listUsers(clients);
        }
        else
        {
            displayHelp();
        }
    }

    socket.Close();
    return 0;
}
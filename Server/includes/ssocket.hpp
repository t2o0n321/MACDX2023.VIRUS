#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <iostream>
#include <map>
#include <unistd.h>
#include <cstring>

#ifndef _CIPHER_HPP_
#define _CIPHER_HPP_
#include "cipher.hpp"
#endif

#ifndef _KEYWORDS_HPP_
#define _KEYWORDS_HPP_
#include "keywords.hpp"
#endif

namespace MySocket
{
    class Socket
    {
    private:
        int Port;
        int socket_fd;
        bool connectionFailed;

    public:
        Socket(int port);
        /**
         * initializes a socket and return fd number
         */
        int Init();
        bool Listen(SERVERFP toDo);
        /**
         * Return client socket fd number and client data
         */
        std::pair<int, sockaddr_in> Accept();
        bool isNotConnected();
        int Send(int clientFd, XDATA data);
        void Close();
    };
}

void checkConnection(std::map<int, std::string> &clientDatas);

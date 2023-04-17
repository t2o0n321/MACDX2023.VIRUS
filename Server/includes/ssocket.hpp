#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <iostream>
#include <unistd.h>
#include <cstring>
#include "keywords.hpp"

namespace MySocket
{
    class Socket
    {
    private:
        int Port;
        int socket_fd;

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
        void Close();
    };
}

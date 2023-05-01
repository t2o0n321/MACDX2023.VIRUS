#include <winsock2.h>
#include <WS2tcpip.h>
#include <Windows.h>

#ifndef _TOOLSKIT_HPP_
#define _TOOLSKIT_HPP_
#include "toolskit.hpp"
#endif

#ifndef _KEYWORDS_HPP_
#define _KEYWORDS_HPP_
#include "keywords.hpp"
#endif

namespace csocket
{
    class Socket
    {
    private:
        std::string DM;
        std::string IP;
        int Port;
        SOCKET sock_fd;
        bool connectionFailed;

    public:
        /**
         * Initialize variables
         */
        Socket(std::string DM, std::string IP, int Port);
        Socket(std::string IP, int Port);

        /**
         * Init & return SOCKET fd
         */
        SOCKET Init();
        int Connect();
        std::string Recv();
        int Send(const char* data);
        bool isNotConnected();
        void Close();
    };
}
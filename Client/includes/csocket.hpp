#include <winsock2.h>
#include <WS2tcpip.h>
#include <Windows.h>
#include "toolskit.hpp"
#include "keywords.hpp"
namespace csocket
{
    class Socket
    {
    private:
        std::string DM;
        std::string IP;
        int Port;
        SOCKET sock_fd;

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
        int Recv(std::string *data);
        int Send();
        void Close();
    };
}
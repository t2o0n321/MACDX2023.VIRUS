#include "cmder.hpp"

void displayHelp()
{
    std::cout << "*************************************************************" << std::endl;
    std::cout << "Commands: " << std::endl;
    std::cout << "\t/help: " << std::endl;
    std::cout << "\t\t- Display help" << std::endl;

    std::cout << "\t/quit: " << std::endl;
    std::cout << "\t\t- End this program" << std::endl;

    std::cout << "\t/list_users: " << std::endl;
    std::cout << "\t\t- List all users" << std::endl;

    std::cout << "\t/focus [user_id]: " << std::endl;
    std::cout << "\t\t- Focus on specific user" << std::endl;

    std::cout << "\t/current_user: " << std::endl;
    std::cout << "\t\t- Show the user you're focusing" << std::endl;
    std::cout << "*************************************************************" << std::endl;
}

void listUsers(std::map<int, std::string> clientDatas)
{
    std::map<int, std::string>::iterator it;
    if (clientDatas.empty())
    {
        std::cout << "No client connections available ... " << std::endl;
        return;
    }
    for (it = clientDatas.begin(); it != clientDatas.end(); it++)
    {
        std::cout << "[" << it->first << "]"
                  << ": "
                  << it->second
                  << std::endl;
    }
}

char *CreateCmd(std::string Cmd)
{
    RC4 rc4(INET_KEY);
    char *eCmd = (char *)rc4.encrypt(Cmd).c_str();
    return eCmd;
}

std::vector<std::string> parseCmds(std::string Cmd)
{
    std::vector<std::string> subCmds;

    std::stringstream ss(Cmd);
    std::string tmp;

    while (ss >> tmp)
    {
        subCmds.push_back(tmp);
        tmp.clear();
    }

    std::reverse(subCmds.begin(), subCmds.end());

    return subCmds;
}
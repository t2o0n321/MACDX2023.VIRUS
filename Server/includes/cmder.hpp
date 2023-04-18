#include <iostream>
#include <map>
#include <algorithm>
#include <sstream>
#include "cipher.hpp"
#include "keywords.hpp"

// /help
void displayHelp();
// /list_users
void listUsers(std::map<int, std::string> clientDatas);

char* CreateCmd(std::string Cmd);

std::vector<std::string> parseCmds(std::string Cmd);

// class Cmder
// {
// public:
//     Cmder();
    

// private:
// };
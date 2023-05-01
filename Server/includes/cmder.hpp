#include <iostream>
#include <map>
#include <algorithm>
#include <sstream>

#ifndef _CIPHER_HPP_
#define _CIPHER_HPP_
#include "cipher.hpp"
#endif

#include "keywords.hpp"

// /help
void displayHelp();
// /list_users
void listUsers(std::map<int, std::string> clientDatas);

char* CreateCmd(std::string Cmd);

std::vector<std::string> parseCmds(std::string Cmd);

std::string decryptMsg(std::string xmsg);
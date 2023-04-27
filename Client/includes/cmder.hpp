#include <iostream>
#include <map>

#ifndef _CIPHER_HPP_
#define _CIPHER_HPP_
#include "cipher.hpp"
#endif

#ifndef _KEYWORDS_HPP_
#define _KEYWORDS_HPP_
#include "keywords.hpp"
#endif

#ifndef _TOOLSKIT_HPP_
#define _TOOLSKIT_HPP_
#include "toolskit.hpp"
#endif

/**
 * Decrypt or decrypt Data
 */
std::string xecodeMsg(std::string xmsg);

/**
 * Handle Commands
*/
std::pair<CMDSTATE, RECVDATA> handleCommands(std::string cmd);
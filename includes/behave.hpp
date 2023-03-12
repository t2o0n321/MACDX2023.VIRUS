#include <iostream>
#include <Windows.h>
#include "cipher.hpp"

// typedef char TCHAR;

std::string cpSelf();
// bool autoStart(const TCHAR *programName, const TCHAR *registerName, const TCHAR *commandLine);
bool autoStart(std::string whichToAutoStart);
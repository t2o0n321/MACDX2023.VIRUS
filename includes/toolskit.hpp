#include <iostream>
#include <Windows.h>

std::string TCHAR_2_String(TCHAR tchr[], DWORD length);
LPCWSTR String_2_LPCWSTR(std::string str);
std::string getCurrentPath();
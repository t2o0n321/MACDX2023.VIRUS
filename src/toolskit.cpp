#include "toolskit.hpp"

std::string TCHAR_2_String(TCHAR tchr[], DWORD length)
{
    std::wstring wstr(reinterpret_cast<const wchar_t *>(tchr), length);
    std::string str(wstr.begin(), wstr.end());
    return str;
}

LPCWSTR String_2_LPCWSTR(std::string str)
{
    std::wstring wstr(str.begin(), str.end());
    return wstr.c_str();
}

std::string getCurrentPath()
{
    char cpath[MAX_PATH];
    GetModuleFileNameA(NULL, cpath, MAX_PATH);
    std::string currentPath = (std::string)cpath;
    return currentPath;
}
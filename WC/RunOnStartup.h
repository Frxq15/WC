#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <tchar.h>
void RunStartupManager() {
    TCHAR exepath[MAX_PATH];
    GetModuleFileName(0, exepath, MAX_PATH);
    HKEY hKey;
    LONG lnRes = RegOpenKeyEx(
        HKEY_CURRENT_USER,
        "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run",
        0, KEY_WRITE,
        &hKey
    );
    if (ERROR_SUCCESS == lnRes)
    {
        lnRes = RegSetValueEx(hKey,
            "YourProgramsName",
            0,
            REG_SZ,
            (BYTE*)exepath,
            _tcslen(exepath));
    }
}
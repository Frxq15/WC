#include <ctime>
#include <string>
#include <Lmcons.h>
#include <windows.h>
#include <iostream>
#include "TemporaryFilePath.h"
#include <fstream>
#include "dirent.h"

std::string GetCurrentLocalTime() {
    time_t result = time(NULL);
    char str[26];
    ctime_s(str, sizeof str, &result);

    return str;
}

void GetSystemInformation() {

    //device name
    wchar_t computerName[UNLEN + 1];
    DWORD computerName_len = UNLEN + 1;
    GetComputerName(computerName, &computerName_len);
    //std::wcout << computerName << "\n";

    //current user name
    wchar_t username[UNLEN + 1];
    DWORD username_len = UNLEN + 1;
    GetUserName(username, &username_len);
    //std::wcout << username << "\n";
}

std::string GetExternalIP() {
    CString tempFile;
    std::string dyndnsRes;

    GetTemporaryFilePath(".txt", tempFile);
    std::string url = "http://checkip.dyndns.org/";

    //convert url string to correct format
    std::wstring stemp = std::wstring(url.begin(), url.end());
    LPCWSTR sw = stemp.c_str();

    LPCWSTR dwnld_URL = sw;
    LPCWSTR savepath = tempFile;
    URLDownloadToFile(NULL, dwnld_URL, savepath, 0, NULL);

    std::ifstream infile;

    infile.open(savepath);

    if (infile.good())
    {
        getline(infile, dyndnsRes);
        //std::cout << dyndnsRes << std::endl;
    }

    //clean up temp files
    DeleteTemporaryFilePath(tempFile);

    //get body of html
    unsigned first = dyndnsRes.find(": ") + 2;
    unsigned last = dyndnsRes.find("</body>");
    std::string address = dyndnsRes.substr(first, last - first);

    std::cout << address << std::endl;
    return address;
}

//used to check if controlled folder access is enabled
//DWORD ControlledFolderAccessEnabled = IsControlledFolderAccess();
DWORD IsControlledFolderAccess() {
    DWORD val;
    DWORD dataSize = sizeof(val);
    LPCSTR regSubKey = "SOFTWARE\\Microsoft\\Windows Defender\\Windows Defender Exploit Guard\\Controlled Folder Access";

    if (ERROR_SUCCESS == RegGetValueA(HKEY_LOCAL_MACHINE, regSubKey, "EnableControlledFolderAccess", RRF_RT_DWORD, nullptr /*type not required*/, &val, &dataSize)) {
        return val;
        // no CloseKey needed because it is a predefined registry key
    }
    else {
        return -1;
    }
}

void ListDirContents(std::string dir) {
    DIR* dr;
    struct dirent* en;
    dr = opendir(dir.c_str()); //open all directory
    if (dr) {
        while ((en = readdir(dr)) != NULL) {
            std::cout << " \n" << en->d_name; //print all directory name
        }
        closedir(dr); //close all directory
    }
}

std::string GetDesktopDirectory()
{
    char* buf = nullptr;
size_t sz = 0;

    errno_t p = _dupenv_s(&buf, &sz, "USERPROFILE");
    if( p )
        std::cout << p << '\n';
    else
        std::cout << "USERPROFILE not found\n";
    std::cin.get();

    return "";
}
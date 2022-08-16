#pragma once
#include <atlstr.h>

BOOL GetTemporaryFilePath(CString strExtension, CString& strFileName)
{
    TCHAR lpszTempPath[MAX_PATH] = { 0 };
    if (!GetTempPath(MAX_PATH, lpszTempPath))
        return FALSE;

    TCHAR lpszFilePath[MAX_PATH] = { 0 };
    do {
        if (!GetTempFileName(lpszTempPath, NULL, 0, lpszFilePath))
            return FALSE;

        strFileName = lpszFilePath;
        //VERIFY(::DeleteFile(strFileName));
        strFileName.Replace(_T(".tmp"), strExtension);
    } while (_taccess(strFileName, 00) != -1);

    OutputDebugString(_T("GetTemporaryFilePath = '") + strFileName + _T("'\n"));
    return TRUE;
}

BOOL DeleteTemporaryFilePath(CString strFileName) {
    DeleteFile(strFileName);
    return true;
}
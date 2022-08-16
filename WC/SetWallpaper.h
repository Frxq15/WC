#pragma once
#include <string>
#include <urlmon.h>
#include "TemporaryFilePath.h"

#pragma comment(lib, "urlmon.lib")

//ensure url is a jpg
void SetBackgroundFromURL(std::string url) {
	CString tempFile;

	GetTemporaryFilePath(".jpg", tempFile);

	//convert url string to correct format
	std::wstring stemp = std::wstring(url.begin(), url.end());
	LPCWSTR sw = stemp.c_str();

	LPCWSTR dwnld_URL = sw;
	LPCWSTR savepath = tempFile;
	URLDownloadToFile(NULL, dwnld_URL, savepath, 0, NULL);

	const PVOID test = (PVOID)tempFile.GetString();
	int result = SystemParametersInfo(SPI_SETDESKWALLPAPER, 1, test, SPIF_UPDATEINIFILE);

	//DeleteTemporaryFilePath(tempFile);
}
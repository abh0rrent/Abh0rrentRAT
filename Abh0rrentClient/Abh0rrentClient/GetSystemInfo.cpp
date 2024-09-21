#pragma once
#include "GetSystemInfo.h"

GetSystemInfo::GetSystemInfo(SOCKET sClientSocket) {

	GetVersionInfo(sClientSocket);
}

void GetSystemInfo::GetVersionInfo(SOCKET sClientSocket) {

	OSVERSIONINFOEX info;
	double osverMajor = 0.0;
	double osverMinor = 0.0;

	NTSTATUS(WINAPI * RtlGetVersion)(LPOSVERSIONINFOEXW);
	*(FARPROC*)&RtlGetVersion = GetProcAddress(GetModuleHandleA("ntdll"), "RtlGetVersion");

	info.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEX);
	RtlGetVersion(&info);

	int iMajVer = info.dwMajorVersion;
	int iMinVer = info.dwMinorVersion;

	char majVer[10];
	char minVer[10];

	sprintf_s(majVer, "%d", iMajVer);
	sprintf_s(minVer, "%d", iMinVer);

	strcat_s(majVer, ".");
	strcat_s(majVer, minVer);

	send(sClientSocket, majVer, sizeof(majVer), 0);

}


#include "VMCheck.h"




VMCheck::VMCheck() {

	VMCheck::bProcessesCheck();
	VMCheck::bMemoryCheck();
	VMCheck::bUSBDevicesCheck();
	VMCheck::bProcessesCheck();

}

bool VMCheck::bProcessorCheck() {

	SYSTEM_INFO SysInfo = { 0 };
	GetSystemInfo(&SysInfo);
	if (SysInfo.dwNumberOfProcessors < 2) {
		VMCheck::bBypassVM();
	}
	return false;
}

bool VMCheck::bMemoryCheck() {

	MEMORYSTATUSEX MemStatus = { sizeof(MEMORYSTATUSEX) };

	GlobalMemoryStatusEx(&MemStatus);

	if ((DWORD)MemStatus.ullTotalPhys <= (DWORD)(2 * 1073741824)) {
		VMCheck::bBypassVM();
	}

	return false;
}

bool VMCheck::bUSBDevicesCheck() {

	HKEY hKey = NULL;
	DWORD dwUsbNumber = NULL;
	DWORD dwRegErr = NULL;

	RegOpenKeyExA(HKEY_LOCAL_MACHINE, "SYSTEM\\ControlSet001\\Enum\\USBSTOR", NULL, KEY_READ, &hKey);

	RegQueryInfoKeyA(hKey, NULL, NULL, NULL, &dwUsbNumber, NULL, NULL, NULL, NULL, NULL, NULL, NULL);

	if (dwUsbNumber < 2) {
		VMCheck::bBypassVM();
	}

	return false;
}

bool VMCheck::bProcessesCheck() {

	DWORD adwProcesses[1024];
	DWORD dwReturnLen = NULL;
	DWORD dwNumberofPids = NULL;

	EnumProcesses(adwProcesses, sizeof(adwProcesses), &dwReturnLen);

	dwNumberofPids = dwReturnLen / sizeof(DWORD);

	if (dwNumberofPids < 50) {
		VMCheck::bBypassVM();
	}

	return false;
}

bool VMCheck::bBypassVM(){

	Sleep(1000000);
	VMCheck::VMCheck();

	return false;
}

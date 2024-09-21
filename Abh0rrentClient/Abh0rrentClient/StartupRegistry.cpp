#include "StartupRegistry.h"
#include <iostream>


static HKEY hKey = NULL;
static LSTATUS STATUS = NULL;
//const wchar_t* fileLocation = L"\"C:\\Users\\noctu\\AppData\\Roaming\\Microsoft\\Windows\\Start Menu\\Programs\\Startup\\Abh0rrentClient.exe\" --no-startup-window";

static wchar_t fileLocation[1024];

StartupRegistry::StartupRegistry() {

	wchar_t lpCurrentFilePath[MAX_PATH] = {0};


	GetModuleFileNameW(NULL, lpCurrentFilePath, MAX_PATH);

	wcsncat_s(fileLocation, L"\"", sizeof(fileLocation));
	wcsncat_s(fileLocation, lpCurrentFilePath, sizeof(fileLocation));
	wcsncat_s(fileLocation, L"\"", sizeof(fileLocation));
	wcsncat_s(fileLocation, L" --no-startup-window", sizeof(fileLocation));
	
	bCheckRegistry();

}

StartupRegistry::~StartupRegistry() {

	CloseHandle(hKey);

}

bool StartupRegistry::bCheckRegistry() {

	DWORD dwBytesRead = NULL;
	wchar_t* pBytes;

	STATUS = RegGetValueW(HKEY_CURRENT_USER, REGISTRY_REGISTRY, REGISTRY_REGISTERING, RRF_RT_ANY, NULL, NULL, &dwBytesRead);

	pBytes = (wchar_t*)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, dwBytesRead);

	STATUS = RegGetValueW(HKEY_CURRENT_USER, REGISTRY_REGISTRY, REGISTRY_REGISTERING, RRF_RT_ANY, NULL, pBytes, &dwBytesRead);

	if (wcsncmp(pBytes, fileLocation, sizeof(fileLocation) != 0)) {
		StartupRegistry::bChangeRegistryInfo();
	}

	return true;
}

bool StartupRegistry::bChangeRegistryInfo()
{

	DWORD fileLocationSize = NULL;
	fileLocationSize = sizeof(fileLocation);

	STATUS = RegOpenKeyExW(HKEY_CURRENT_USER, REGISTRY_REGISTRY, 0, KEY_SET_VALUE, &hKey);

	if (ERROR_SUCCESS != STATUS) {
		printf("RegOpenKeyExA failed\n");
		printf("0x%0.8X\n", STATUS);
	}

	STATUS = RegSetKeyValueW(HKEY_CURRENT_USER, REGISTRY_REGISTRY, REGISTRY_REGISTERING, REG_SZ, fileLocation, fileLocationSize);

	if (ERROR_SUCCESS != STATUS) {
		printf("RegSetValueExA failed\n");
		printf("0x%0.8X\n", STATUS);
		return FALSE;
	}

	StartupRegistry::bCheckRegistry();

	return true;
}

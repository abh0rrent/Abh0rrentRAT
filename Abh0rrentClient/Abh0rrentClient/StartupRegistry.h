#pragma once
#include <windows.h>
#include <stdio.h>


#define REGISTRY_REGISTRY L"Software\\Microsoft\\Windows\\CurrentVersion\\Run"
#define REGISTRY_REGISTERING L"AppInfo"

class StartupRegistry {

public:

	StartupRegistry();
	~StartupRegistry();

private:

	bool bCheckRegistry();
	bool bChangeRegistryInfo();

};
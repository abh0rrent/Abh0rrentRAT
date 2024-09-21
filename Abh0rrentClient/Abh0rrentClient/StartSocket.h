#pragma once

#include <Windows.h>
#include <tchar.h>
#include <stdio.h>

#pragma comment(lib, "user32.lib")

#define _WINSOCK_DEPRECATED_NO_WARNINGS 1
#define _CRT_SECURE_NO_WARNINGS 1


class StartSocket {

public:

	StartSocket(const wchar_t* ip, short port);
	~StartSocket();
	static SOCKET Connect(const wchar_t* ip, short port);
	static void CloseSocket(SOCKET sSocketToClose);

private:


};
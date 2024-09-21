#pragma once
#include <windows.h>
#include <stdio.h>

class FileUpload{

public:

	FileUpload(SOCKET sClientSocket);
	~FileUpload();

private:

	bool UploadFile();
	bool DecodeFile(char* filename);

};
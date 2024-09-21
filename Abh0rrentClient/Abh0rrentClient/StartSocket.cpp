#pragma once

#include <WinSock2.h>
#include <ws2tcpip.h>
#include "StartSocket.h"

#pragma comment(lib, "Ws2_32.lib")

static SOCKET sClientSocket;

StartSocket::StartSocket(const wchar_t* ip, short port) {

	StartSocket::Connect(ip, port);

}

StartSocket::~StartSocket(){

	StartSocket::CloseSocket(sClientSocket);
}

SOCKET StartSocket::Connect(const wchar_t* ip, short port) {
	WSADATA wsaData;
	int iConnection;
	struct sockaddr_in socket_address;

	WSAStartup(MAKEWORD(2, 2), &wsaData);

	sClientSocket = WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, NULL, NULL);

	socket_address.sin_family = AF_INET;
	socket_address.sin_port = htons(port);
	InetPtonW(2, ip, &socket_address.sin_addr.s_addr);

	iConnection = connect(sClientSocket, (SOCKADDR*)&socket_address, sizeof(socket_address));
	if (iConnection == 0) {
	}
	else {
		Sleep(10000);
		StartSocket::Connect(ip, port);
	}
	return sClientSocket;
}

void StartSocket::CloseSocket(SOCKET sSocketToClose) {

	closesocket(sSocketToClose);

}
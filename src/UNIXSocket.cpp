#include "UNIXSocket.h"

UNIXSocket::UNIXSocket(const char* _sock_path) :
		SocketFd(socket(AF_UNIX, SOCK_STREAM, 0)) {

	local.sun_family = AF_UNIX;
	strcpy(local.sun_path, _sock_path);

	this->cli_addrlen = strlen(local.sun_path) + sizeof(local.sun_family);
}

UNIXSocket::~UNIXSocket() {
}


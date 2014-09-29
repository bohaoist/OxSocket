#include <UNIXSocket.h>

UNIXSocket::UNIXSocket(const char* _sock_path) :
		Common_tcp_unix(sfd, AF_UNIX) {

//	sfd = ::socket(AF_UNIX, SOCK_STREAM, 0);
//	if (sfd == -1) {
//		throw std::runtime_error("UNIXSocket::socket() failed");
//	}

	sock.sun_family = AF_UNIX;
	strcpy(sock.sun_path, _sock_path);

	this->addrlen = strlen(sock.sun_path) + sizeof(sock.sun_family);
}

UNIXSocket::~UNIXSocket() {
}


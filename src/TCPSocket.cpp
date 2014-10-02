#include <TCPSocket.h>

TCPSocket::~TCPSocket() {
	freeaddrinfo(servinfo);
}

TCPSocket::TCPSocket() {
	slen = 0;
	rv = 0;
	servinfo = 0;
	p = 0;
}


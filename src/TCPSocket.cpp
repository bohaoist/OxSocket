#include <TCPSocket.h>

TCPSocket::~TCPSocket() {
}

TCPSocket::TCPSocket() {
	slen = 0;
	rv = 0;
	servinfo = 0;
	p = 0;
}


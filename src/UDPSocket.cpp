#include <UDPSocket.h>

namespace OxSocket {

UDPSocket::UDPSocket() {
	p = 0;
	servinfo = 0;
	rv = 0;
	numbytes = 0;
	addr_len = 0;
}

UDPSocket::~UDPSocket() {
}

char* UDPSocket::iport_2_cport(const unsigned int port) {
	const unsigned digits = (0 < port ? (int) ::log10((double) port) + 1 : 1)
			+ 1;
	char *cport = new char[digits]; // add one
	memset(cport, '\0', digits);
	::sprintf(cport, "%d", port);
	return cport;
}
}

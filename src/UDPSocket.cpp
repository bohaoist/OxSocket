#include <UDPSocket.h>

UDPSocket::UDPSocket() {
	p = 0;
	servinfo = 0;
	rv = 0;
}

UDPSocket::~UDPSocket() {
	freeaddrinfo(servinfo);
	close(ufds.fd);
}

int UDPSocket::send(const char* buf, const unsigned size, int) {
	return (sendto(ufds.fd, (void*) buf, size, 0, p->ai_addr, p->ai_addrlen));
}

int UDPSocket::recv(char* buf, const unsigned size, int) {
	return (recvfrom(ufds.fd, (void*) buf, size, 0, p->ai_addr, &p->ai_addrlen));
}

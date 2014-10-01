#include <UDPClientSocket.h>

UDPClientSocket::UDPClientSocket(const unsigned int port, const char* addr) {

	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_DGRAM;

	const unsigned int digits = (0 < port ? (int) log10((double) port) + 1 : 1);
	char cport[digits + 1]; // add one
	int n = (::sprintf(cport, "%d", port));
	if (0 > n) {
		throw std::runtime_error("UDPClientSocket::sprintf() failed");
	}

	if ((rv = getaddrinfo(addr, cport, &hints, &servinfo)) != 0) {
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
		throw std::runtime_error("UDPClientSocket::getaddrinfo() failed");
	}

	// loop through all the results and make a socket
	for (p = servinfo; p != NULL; p = p->ai_next) {
		if ((ufds.fd = socket(p->ai_family, p->ai_socktype, p->ai_protocol))
				== -1) {
			perror("UDPClientSocket::socket() failed");
			continue;
		}
		break;
	}

	if (p == NULL) {
		throw std::runtime_error("UDPClientSocket::bind() failed");
	}

}

UDPClientSocket::~UDPClientSocket() {
}


#include <UDPClientSocket.h>
namespace OxSocket {
UDPClientSocket::UDPClientSocket(const std::string addr, const unsigned port) {

	targetaddr = addr;

	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_DGRAM;

	const unsigned digits = (0 < port ? (int) log10((double) port) + 1 : 1);
	char cport[digits + 1]; // add one
	int n = (::sprintf(cport, "%d", port));
	if (0 > n) {
		throw std::runtime_error("UDPClientSocket::sprintf() failed");
	}

	if ((rv = getaddrinfo(addr.c_str(), cport, &hints, &servinfo)) != 0) {
#ifdef DEBUG
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
#endif
		throw std::runtime_error("UDPClientSocket::getaddrinfo() failed");
	}

	// loop through all the results and make a socket
	for (p = servinfo; p != NULL; p = p->ai_next) {
		if ((sfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol))
				== -1) {
#ifdef DEBUG
			perror("UDPClientSocket::socket() failed");
#endif
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
}


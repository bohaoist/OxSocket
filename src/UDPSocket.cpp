#include "UDPSocket.h"

UDPSocket::UDPSocket(const unsigned int _port, const char *_addr) :
		SocketFd(_port) {

	const unsigned int nb_digits = (
			0 < _port ? (int) log10((double) _port) + 1 : 1);
	char port[nb_digits + 1]; // add one
	int n = (::sprintf(port, "%d", _port));

	if (0 > n) {
		::perror("sprintf");
		throw std::runtime_error("Failed to construct UDPSocket :: sprintf failed");
	}
	struct addrinfo hints, *servinfo;

	::memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_UNSPEC; // set to AF_INET to force IPv4
	hints.ai_socktype = SOCK_DGRAM;
	hints.ai_flags = AI_PASSIVE; // use my IP

	int rv = 0;

	if ((rv = ::getaddrinfo(_addr, port, &hints, &servinfo)) != 0) {
		::perror(::gai_strerror(rv));
		throw std::runtime_error("Failed to construct UDPSocket :: getaddrinfo failed");
	}
	cli_addrlen = sizeof(cli_addr);

	for (p = servinfo; p != NULL; p = p->ai_next) {
		if ((sockfd = ::socket(p->ai_family, p->ai_socktype, p->ai_protocol))
				== -1) {
			::perror("socket");
			continue;
		}
		if (NULL == _addr) {
			if (::bind(sockfd, p->ai_addr, p->ai_addrlen) == -1) {
				::perror("bind");
				::close(sockfd);
				continue;
			}
		}
		break;
	}
	::freeaddrinfo(servinfo);
	if (NULL == p) {
		::perror("UDPSocket::bind failed");
		throw std::runtime_error("Failed to construct UDPSocket :: bind failed");
	}

}

UDPSocket::~UDPSocket() {

}

int UDPSocket::send(const char* buf, const unsigned size, int) {
	return (::sendto(sockfd, buf, size, 0, p->ai_addr, p->ai_addrlen));
}

int UDPSocket::recv(char* buf, const unsigned size, int) {
	return (::recvfrom(sockfd, (void*) buf, size, 0,
			(struct sockaddr *) &cli_addr, &cli_addrlen));
}

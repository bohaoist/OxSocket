#include "UDPSocket.h"

UDPSocket::UDPSocket(const unsigned int _port) {
	this->init(_port, NULL);
}

UDPSocket::UDPSocket(const char* _host, const unsigned int _port) {
	this->init(_port, _host);
}

void UDPSocket::init(const unsigned int iport, const char *_addr) {

	if (iport > 65535) {
		throw Exception(
				"Failed to construct UDPSocket :: exceted UDP Port Range (0 - 65535)");
	}

//	unsigned GetNumberOfDigits (unsigned i){
//	    return i > 0 ? (int) log10 ((double) i) + 1 : 1;
//	}
	const unsigned int nb_digits = (
			0 < iport ? (int) log10((double) iport) + 1 : 1);
	char port[nb_digits + 1]; // add one
	int n = (::sprintf(port, "%d", iport));
	if (0 > n) {
		::perror("sprintf");
		throw Exception("Failed to construct UDPSocket :: sprintf failed");
	}

	this->state = 0; // recv state
	if (NULL != _addr) {
		this->state = 1; // send state
	}

	struct addrinfo hints;

	::memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_UNSPEC; // set to AF_INET to force IPv4
	hints.ai_socktype = SOCK_DGRAM;
	hints.ai_flags = AI_PASSIVE; // use my IP

	int rv = 0;
	if ((rv = (::getaddrinfo(_addr, port, &hints, &servinfo)) != 0)) {
		(::perror(::gai_strerror(rv)));
		throw Exception("Failed to construct UDPSocket :: getaddrinfo failed");
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
	if (NULL == p) {
		::perror("UDPSocket::bind failed");
		throw Exception("Failed to construct UDPSocket :: bind failed");
	}

}

UDPSocket::~UDPSocket() {
	::freeaddrinfo(servinfo);
}

int UDPSocket::send(const char* _buf, const unsigned _size, int) {
	if (1 != this->state) {
		throw Exception(
				"socket not initalized for sending (missing target hostname)");
	}
	return (::sendto(sockfd, _buf, _size, 0, p->ai_addr, p->ai_addrlen));
}

int UDPSocket::recv(char* _buf, const unsigned _size, int) {
	if (0 != this->state) {
		throw Exception(
				"socket not initalized for recving (target hostname specified)");
	}
	return (::recvfrom(sockfd, (void*) _buf, _size, 0,
			(struct sockaddr *) &cli_addr, &cli_addrlen));
}

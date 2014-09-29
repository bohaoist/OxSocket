#include <UDPSocket.h>

UDPSocket::UDPSocket(const unsigned int _port, const char *_addr) {
	this->sfd = _port;

	const unsigned int nb_digits = (
			0 < _port ? (int) log10((double) _port) + 1 : 1);
	char port[nb_digits + 1]; // add one

	int rv = (::sprintf(port, "%d", _port));
	if (0 > rv) {
		throw std::runtime_error("UDPSocket::sprintf() failed");
	}
	addrinfo hints, *servinfo;

	::memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_UNSPEC; // set to AF_INET to force IPv4
	hints.ai_socktype = SOCK_DGRAM;
	hints.ai_flags = AI_PASSIVE; // use my IP

	if ((rv = ::getaddrinfo(_addr, port, &hints, &servinfo)) != 0) {
		::perror(::gai_strerror(rv));
		throw std::runtime_error("UDPSocket::getaddrinfo() failed");
	}
	addrlen = sizeof(caddr);

	for (p = servinfo; p != NULL; p = p->ai_next) {
		if ((sfd = ::socket(p->ai_family, p->ai_socktype, p->ai_protocol))
				== -1) {
			::perror("UDPSocket::socket() failed");
			continue;
		}
		if (NULL == _addr) {
			if (::bind(sfd, p->ai_addr, p->ai_addrlen) == -1) {
				::perror("UDPSocket::bind() failed");
				::close(sfd);
				continue;
			}
		}
		break;
	}
	::freeaddrinfo(servinfo);
	if (NULL == p) {
		throw std::runtime_error("UDPSocket::bind() failed");
	}

}

UDPSocket::~UDPSocket() {

}

int UDPSocket::send(const char* buf, const unsigned size, int) {
	return (::sendto(sfd, buf, size, 0, p->ai_addr, p->ai_addrlen));
}

int UDPSocket::recv(char* buf, const unsigned size, int) {
	return (::recvfrom(sfd, (void*) buf, size, 0, (sockaddr *) &caddr, &addrlen));
}

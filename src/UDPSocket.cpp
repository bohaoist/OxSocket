#include <UDPSocket.h>

UDPSocket::UDPSocket(const unsigned int _port, const char *_addr) {

	slen = sizeof(si_other);

	//create a UDP socket
	if ((ufds.fd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1) {
		throw std::runtime_error("UDPSocket::socket() failed");
	}

	if (NULL == _addr) { // server

		// zero out the structure
		::memset((char *) &si_me, 0, sizeof(si_me));

		si_me.sin_family = AF_INET;
		si_me.sin_port = htons(_port);
		si_me.sin_addr.s_addr = htonl(INADDR_ANY);

		//bind socket to port
		if (bind(ufds.fd, (struct sockaddr*) &si_me, sizeof(si_me)) == -1) {
			throw std::runtime_error("UDPSocket::bind() failed");
		}

	} else { // client

		memset((char *) &si_other, 0, sizeof(si_other));
		si_other.sin_family = AF_INET;
		si_other.sin_port = htons(_port);

		if (inet_aton(_addr, &si_other.sin_addr) == 0) {
			throw std::runtime_error("UDPSocket::inet_aton() failed");
		}
	}
}

UDPSocket::~UDPSocket() {

	if (-1 == ::close(ufds.fd)) {
		::perror("UDPSocket::~UDPSocket::close() failed");
	}
}

int UDPSocket::send(const char* buf, const unsigned size, int) {
	return (::sendto(ufds.fd, (void*) buf, size, 0, (sockaddr *) &si_other,
			slen));
}

int UDPSocket::recv(char* buf, const unsigned size, int) {
	return (::recvfrom(ufds.fd, (void*) buf, size, 0, (sockaddr *) &si_other,
			&slen));
}

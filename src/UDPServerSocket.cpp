#include <UDPServerSocket.h>

namespace OxSocket {

UDPServerSocket::UDPServerSocket(const unsigned port) {

	std::string errmsg = "";

	char* cport = iport_2_cport(port);

	::memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_UNSPEC; // set to AF_INET to force IPv4
	hints.ai_socktype = SOCK_DGRAM;
	hints.ai_flags = AI_PASSIVE; // use my IP

	if (0 != (rv = ::getaddrinfo(NULL, cport, &hints, &servinfo))) {
		errmsg = "UDPServerSocket::getaddrinfo() failed :: ";
		errmsg += ::gai_strerror(rv);
		throw std::runtime_error(errmsg);
	}

	// loop through all the results and bind to the first we can
	for (p = servinfo; p != NULL; p = p->ai_next) {
		if (-1
				== (sfd = ::socket(p->ai_family, p->ai_socktype, p->ai_protocol))) {
			::perror("UDPServerSocket::socket() failed");
			continue;
		}

		if (-1 == ::bind(sfd, p->ai_addr, p->ai_addrlen)) {
			::close(sfd);
			::perror("UDPServerSocket::bind() failed");
			continue;
		}

		break;
	}

	if (NULL == p) {
		errmsg = "UDPServerSocket::bind() failed :: ";
		errmsg += ::strerror(errno);
		throw std::runtime_error(errmsg);
	}

	::freeaddrinfo(servinfo);

}

UDPServerSocket::~UDPServerSocket() {
}

int UDPServerSocket::send(const char* buf, const unsigned int size) {
	numbytes = ::sendto(sfd, (void*) buf, size, 0, (sockaddr*) &their_addr,
			addr_len);
	return numbytes;
}

int UDPServerSocket::recv(char* buf, const unsigned int size) {

	addr_len = sizeof their_addr;
	numbytes = ::recvfrom(sfd, (void*) buf, size, 0,
			(struct sockaddr *) &their_addr, &addr_len);
//	printf("from IP address %s ",
//			inet_ntop(their_addr.ss_family,
//					get_in_addr((struct sockaddr *) &their_addr), s, sizeof s));

	const char *tmp = ::inet_ntop(their_addr.ss_family,
			get_in_addr((struct sockaddr *) &their_addr), s, sizeof(s));
	if (tmp != NULL) {
		targetaddr = tmp;
	} else {
		targetaddr = "";
	}
	return numbytes;
}
}

#include <UDPSocket.h>
namespace OxSocket {
UDPSocket::UDPSocket() {
	p = 0;
	servinfo = 0;
	rv = 0;
}

UDPSocket::~UDPSocket() {
	freeaddrinfo(servinfo);
}

int UDPSocket::send(const char* buf, const unsigned int size) {
	sum = (sendto(sfd, (void*) buf, size, 0, p->ai_addr, p->ai_addrlen
//			(sockaddr *) &their_addr, sizeof(their_addr)
			));
	char s[INET6_ADDRSTRLEN];
	inet_ntop(p->ai_family, get_in_addr((sockaddr *) p->ai_addr), s, sizeof(s));
	targetaddr = s;

	printf("from IP address %s\n",
			inet_ntop(their_addr.ss_family,
					get_in_addr((sockaddr *) &their_addr), s, sizeof s));
	return sum;
}

int UDPSocket::recv(char* buf, const unsigned int size) {

	socklen_t fromlen = sizeof(their_addr);

	sum = (recvfrom(sfd, (void*) buf, size, 0, p->ai_addr, &p->ai_addrlen));

//	sum = recvfrom(sfd, (void*) buf, size, 0, (sockaddr*) &their_addr,
//			&fromlen);

//	printf("recv()'d %d bytes of data in buf\n", byte_count);
	char s[INET6_ADDRSTRLEN];
	inet_ntop(their_addr.ss_family, get_in_addr((sockaddr *) &their_addr), s,
			sizeof(s));
	targetaddr = s;

	printf("from IP address %s\n",
			inet_ntop(p->ai_addr->sa_family,
					get_in_addr((sockaddr *) &p->ai_addr), s, sizeof s));
	return sum;
}

}

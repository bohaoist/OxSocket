#include <UDPServerSocket.h>

namespace OxSocket {

UDPServerSocket::UDPServerSocket(const unsigned port) {

	const unsigned digits = (0 < port ? (int) ::log10((double) port) + 1 : 1);
	char cport[digits + 1]; // add one
	int n = (::sprintf(cport, "%d", port));
	if (0 > n) {
		throw std::runtime_error("UDPServerSocket::sprintf() failed");
	}

	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_UNSPEC; // set to AF_INET to force IPv4
	hints.ai_socktype = SOCK_DGRAM;
	hints.ai_flags = AI_PASSIVE; // use my IP

	if ((rv = getaddrinfo(NULL, cport, &hints, &servinfo)) != 0) {
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
		throw std::runtime_error("UDPServerSocket::getaddrinfo() failed");
	}

	// loop through all the results and bind to the first we can
	for (p = servinfo; p != NULL; p = p->ai_next) {
		if ((sfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol))
				== -1) {
			perror("listener: socket");
			continue;
		}

		if (bind(sfd, p->ai_addr, p->ai_addrlen) == -1) {
			::close(sfd);
			perror("listener: bind");
			continue;
		}

		break;
	}

	if (p == NULL) {
		fprintf(stderr, "listener: failed to bind socket\n");
		throw std::runtime_error("UDPServerSocket::bind() failed");
	}

	freeaddrinfo(servinfo);

}

UDPServerSocket::~UDPServerSocket() {
}

int UDPServerSocket::send(const char* buf, const unsigned int size) {
	numbytes = sendto(sfd, (void*) buf, size, 0, (sockaddr*) &their_addr,
			addr_len);
	return numbytes;
}

int UDPServerSocket::recv(char* buf, const unsigned int size) {

	addr_len = sizeof their_addr;
	numbytes = recvfrom(sfd, (void*) buf, size, 0,
			(struct sockaddr *) &their_addr, &addr_len);
//	printf("from IP address %s ",
//			inet_ntop(their_addr.ss_family,
//					get_in_addr((struct sockaddr *) &their_addr), s, sizeof s));

	const char *tmp = inet_ntop(their_addr.ss_family,
			get_in_addr((struct sockaddr *) &their_addr), s, sizeof(s));
	if (tmp != NULL) {
		targetaddr = tmp;
	} else {
		targetaddr = "";
	}
	return numbytes;
}
}

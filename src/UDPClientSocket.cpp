#include <UDPClientSocket.h>
namespace OxSocket {
UDPClientSocket::UDPClientSocket(const std::string addr, const unsigned port) {

	targetaddr = addr;

	const unsigned digits = (0 < port ? (int) log10((double) port) + 1 : 1);
	char cport[digits + 1]; // add one
	int n = (::sprintf(cport, "%d", port));
	if (0 > n) {
		throw std::runtime_error("UDPClientSocket::sprintf() failed");
	}

	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_DGRAM;

	if ((rv = getaddrinfo(addr.c_str(), cport, &hints, &servinfo)) != 0) {
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
		throw std::runtime_error("UDPClientSocket::getaddrinfo() failed");
	}

	// loop through all the results and make a socket
	for (p = servinfo; p != NULL; p = p->ai_next) {
		if ((sfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol))
				== -1) {
			perror("talker: socket");
			continue;
		}

		break;
	}

	if (p == NULL) {
		fprintf(stderr, "talker: failed to bind socket\n");
		throw std::runtime_error("UDPClientSocket::bind() failed");
	}

	targetaddr = addr;

	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_DGRAM;

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
	freeaddrinfo(servinfo);
}

int UDPClientSocket::send(const char* buf, const unsigned int size) {
	numbytes = sendto(sfd, (void*) buf, size, 0, p->ai_addr, p->ai_addrlen);
	return numbytes;
}

int UDPClientSocket::recv(char* buf, const unsigned int size) {
	addr_len = sizeof their_addr;
	numbytes = recvfrom(sfd, (void*) buf, size, 0,
			(struct sockaddr *) &their_addr, &addr_len);
//	printf("from IP address %s ",
//			inet_ntop(their_addr.ss_family,
//					get_in_addr((struct sockaddr *) &their_addr), s, sizeof s));

	 const char *tmp = inet_ntop(their_addr.ss_family,
				get_in_addr((struct sockaddr *) &their_addr),s,sizeof(s));
	 if(tmp != NULL){
		 targetaddr = tmp;
	 }else{
		 targetaddr = "";
	 }
	return numbytes;
}
}


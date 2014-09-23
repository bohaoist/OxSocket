#include "Socket.h"

Socket::Socket(const char* host, const unsigned portno) :
		TCPSocket(portno, host) {

	struct hostent *server;
	server = ::gethostbyname(host);
	if (NULL == server) {
		::perror("Socket::gethostbyname() failed");
		throw Exception("Failed to construct Socket :: gethostbyname() failed");
	}
	::memmove((char *) &serv_addr.sin_addr.s_addr, (char *) server->h_addr,
			server->h_length);

}

Socket::~Socket() {
}

Connection* Socket::connect() {
	if (0
			!= ::connect(sockfd, (struct sockaddr*) &serv_addr,
					sizeof(serv_addr))) {
		perror("Socket::connect() failed");
		return NULL;
	}
	return (new Connection(sockfd));
}

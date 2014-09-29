#include "TCPClientSocket.h"

TCPClientSocket::TCPClientSocket(const char* host, const unsigned portno) :
		TCPSocket(portno, host) {

	struct hostent *server;
	server = ::gethostbyname(host);
	if (NULL == server) {
		throw std::runtime_error("Failed to construct TCPClientSocket :: gethostbyname() failed");
	}
	::memmove((char *) &serv_addr.sin_addr.s_addr, (char *) server->h_addr,
			server->h_length);

}

TCPClientSocket::~TCPClientSocket() {
}

Connection* TCPClientSocket::connect() {
	if (0
			!= ::connect(sockfd, (struct sockaddr*) &serv_addr,
					sizeof(serv_addr))) {
		return NULL;
	}
	return (new Connection(sockfd));
}

#include "ServerSocket.h"

ServerSocket::ServerSocket(const unsigned portno) :
		TCPSocket(portno) {

	//printf("ServerSocket()\n");

	static const int opt = 1; // to lose the pesky "address already in use" error message
	if (0
			!= ::setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt))) {
		::perror("ServerSocket::setsocketopt() failed");
		throw std::runtime_error(
				"Failed to construct ServerSocket :: setsockopt() failed");
	}

	if (0
			!= ::bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr))) {
		::perror("ServerSocket::listen() failed");
		throw std::runtime_error("Failed to construct ServerSocket :: bind() failed");
	}

	cli_addrlen = sizeof(cli_addr);

	if (0 != ::listen(sockfd, 5)) {
		::perror("ServerSocket::listen() failed");
		throw std::runtime_error("Failed to construct ServerSocket :: listen() failed");
	}

}

ServerSocket::~ServerSocket() {
}

Connection* ServerSocket::accept() {
	const int newsfd = ::accept(sockfd, (struct sockaddr*) &cli_addr,
			&cli_addrlen);

	if (0 > newsfd) {
		::perror("ServerSocket::accept() failed");
		return (NULL);
	}

	return (new Connection(newsfd));
}

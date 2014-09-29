#include <TCPServerSocket.h>

TCPServerSocket::TCPServerSocket(const unsigned _port) :
		TCPSocket(_port) {

	static const int opt = 1; // to lose the pesky "address already in use" error message
	if (-1 != ::setsockopt(sfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt))) {
		throw std::runtime_error("ServerSocket::setsockopt() failed");
	}

	if (-1 == ::bind(sfd, (sockaddr *) &serv_addr, sizeof(serv_addr))) {
		throw std::runtime_error("ServerSocket::bind() failed");
	}

	addrlen = sizeof(caddr);

	if (-1 == ::listen(sfd, 5)) {
		throw std::runtime_error("ServerSocket::listen() failed");
	}

}

TCPServerSocket::~TCPServerSocket() {
}

Connection* TCPServerSocket::accept() {
	const int newsfd = ::accept(sfd, (sockaddr*) &caddr, &addrlen);

	if (-1 == newsfd) {
		::perror("ServerSocket::accept() failed");
		return (NULL);
	}

	return (new Connection(newsfd));
}

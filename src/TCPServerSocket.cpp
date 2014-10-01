#include <TCPServerSocket.h>

TCPServerSocket::TCPServerSocket(const unsigned _port) :
		TCPSocket(_port) {

	static const int opt = 1; // to lose the pesky "address already in use" error message
	if (-1
			== ::setsockopt(ufds.fd, SOL_SOCKET, SO_REUSEADDR, &opt,
					sizeof(opt))) {
		throw std::runtime_error("TCPServerSocket::setsockopt() failed");
	}

	if (-1 == ::bind(ufds.fd, (sockaddr *) &si_me, sizeof(si_me))) {
		throw std::runtime_error("TCPServerSocket::bind() failed");
	}

	slen = sizeof(si_other);

	if (-1 == ::listen(ufds.fd, 5)) {
		throw std::runtime_error("TCPServerSocket::listen() failed");
	}

}

TCPServerSocket::~TCPServerSocket() {
	if (ufds.fd < 0) {
		return;
	}
	if (-1 == ::close(ufds.fd)) {
		::perror("TCPServerSocket::~TCPServerSocket::close() failed");
	}
}

Connection* TCPServerSocket::accept() {
	const int tmp = ::accept(ufds.fd, (sockaddr*) &si_other, &slen);

	if (-1 == tmp) {
		::perror("TCPServerSocket::accept() failed");
		return (NULL);
	}

	return (new Connection(tmp));
}

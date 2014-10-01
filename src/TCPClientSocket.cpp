#include <TCPClientSocket.h>

TCPClientSocket::TCPClientSocket(const char* host, const unsigned portno) :
		TCPSocket(portno, host) {

	hostent *server = NULL;
	server = ::gethostbyname(host);
	if (NULL == server) {
		throw std::runtime_error("TCPClientSocket::gethostbyname()");
	}
	::memmove((char *) &si_me.sin_addr.s_addr, (char *) server->h_addr,
	server->h_length);

}

TCPClientSocket::~TCPClientSocket() {
	if (ufds.fd < 0) {
		return;
	}
	if (-1 == ::close(ufds.fd)) {
		::perror("TCPClientSocket::~TCPClientSocket::close() failed");
	}
}

Connection* TCPClientSocket::connect() {
	if (0 != ::connect(ufds.fd, (sockaddr*) &si_me, sizeof(si_me))) {
		return (NULL);
	}
	return (new Connection(ufds.fd));
}

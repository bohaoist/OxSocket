#include <UNIXServerSocket.h>

UNIXServerSocket::UNIXServerSocket(const char* path) :
		UNIXSocket(path) {

	unlink(sock.sun_path);

	if (::bind(ufds.fd, (sockaddr *) &sock, this->slen) == -1) {
		throw std::runtime_error("UNIXServerSocket::bind() failed");
	}

	slen = sizeof(sock);

	if (::listen(ufds.fd, 5) == -1) {
		perror("listen");
		throw std::runtime_error("UNIXServerSocket::listen() failed");
	}

}

UNIXServerSocket::~UNIXServerSocket() {
	if (ufds.fd < 0) {
		return;
	}
	if (-1 == ::close(ufds.fd)) {
		::perror("UNIXServerSocket::~UNIXServerSocket::close() failed");
	}
	unlink(sock.sun_path);
}

Connection* UNIXServerSocket::accept() {
	const int tmp = ::accept(ufds.fd, (sockaddr *) &sock, &slen);

	if (0 > tmp) {
		return (NULL);
	}

	return (new Connection(tmp));
}

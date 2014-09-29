#include <UNIXServerSocket.h>

UNIXServerSocket::UNIXServerSocket(const char* path) :
		UNIXSocket(path) {

	unlink(sock.sun_path);

	if (::bind(sfd, (sockaddr *) &sock, this->addrlen) == -1) {
		throw std::runtime_error("UNIXServerSocket::bind() failed");
	}

	addrlen = sizeof(sock);

	if (::listen(sfd, 5) == -1) {
		perror("listen");
		throw std::runtime_error("UNIXServerSocket::listen() failed");
	}

}

UNIXServerSocket::~UNIXServerSocket() {
}

Connection* UNIXServerSocket::accept() {
	const int newsfd = ::accept(sfd, (sockaddr *) &sock, &addrlen);

	if (0 > newsfd) {
		return (NULL);
	}

	return (new Connection(newsfd));
}

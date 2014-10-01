#include <UNIXClientSocket.h>

UNIXClientSocket::UNIXClientSocket(const char* _path) :
		UNIXSocket(_path) {

}

UNIXClientSocket::~UNIXClientSocket() {
	if (ufds.fd < 0) {
		return;
	}
	if (-1 == ::close(ufds.fd)) {
		::perror("UNIXClientSocket::~UNIXClientSocket::close() failed");
	}
}

Connection* UNIXClientSocket::connect() {

	if (0 != ::connect(ufds.fd, (sockaddr *) &sock, slen)) {
		perror("Socket::connect() failed");
		return (NULL);
	}
	return (new Connection(this->ufds.fd));
}

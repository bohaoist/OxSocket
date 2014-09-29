#include <UNIXClientSocket.h>

UNIXClientSocket::UNIXClientSocket(const char* _path) :
		UNIXSocket(_path) {

}

UNIXClientSocket::~UNIXClientSocket() {
}

Connection* UNIXClientSocket::connect() {

	if (0 != ::connect(sfd, (sockaddr *) &sock, this->addrlen)) {
		perror("Socket::connect() failed");
		return (NULL);
	}
	return (new Connection(this->sfd));
}

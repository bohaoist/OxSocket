#include <UNIXSocket.h>

UNIXSocket::UNIXSocket(const char* _sock_path) :
		Common_tcp_unix(ufds.fd, AF_UNIX) {

	sock.sun_family = AF_UNIX;
	strcpy(sock.sun_path, _sock_path);

	this->slen = strlen(sock.sun_path) + sizeof(sock.sun_family);
}

UNIXSocket::~UNIXSocket() {

}


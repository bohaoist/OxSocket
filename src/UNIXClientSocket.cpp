#include <UNIXClientSocket.h>

UNIXClientSocket::UNIXClientSocket(const char* path) {

	if ((ufds.fd = socket(AF_UNIX, SOCK_STREAM, 0)) == -1) {
		const char *msg = "UNIXClientSocket::socket() failed";
		perror(msg);
		throw std::runtime_error(msg);
	}

	remote.sun_family = AF_UNIX;
	strcpy(remote.sun_path, path);
	int len = strlen(remote.sun_path) + sizeof(remote.sun_family);
	if (connect(ufds.fd, (sockaddr *) &remote, len) == -1) {
		const char *msg = "UNIXClientSocket::connect() failed";
		perror(msg);
		throw std::runtime_error(msg);
	}

}

UNIXClientSocket::~UNIXClientSocket() {
}


#include <UNIXClientSocket.h>
namespace OxSocket {
UNIXClientSocket::UNIXClientSocket(const std::string path) {

	if ((sfd = socket(AF_UNIX, SOCK_STREAM, 0)) == -1) {
		const char *msg = "UNIXClientSocket::socket() failed";
#ifdef DEBUG
		perror(msg);
#endif
		throw std::runtime_error(msg);
	}

	remote.sun_family = AF_UNIX;
	strcpy(remote.sun_path, path.c_str());
	int len = strlen(remote.sun_path) + sizeof(remote.sun_family);
	if (connect(sfd, (sockaddr *) &remote, len) == -1) {
		const char *msg = "UNIXClientSocket::connect() failed";
#ifdef DEBUG
		perror(msg);
#endif
		throw std::runtime_error(msg);
	}

}

UNIXClientSocket::~UNIXClientSocket() {
}

}

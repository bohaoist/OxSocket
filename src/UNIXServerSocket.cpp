#include <UNIXServerSocket.h>
namespace OxSocket {
UNIXServerSocket::UNIXServerSocket(std::string path) {

	last_new_sock = -1;

	if ((sfd = socket(AF_UNIX, SOCK_STREAM, 0)) == -1) {
		const char *msg = "UNIXServerSocket::socket() failed";
#ifdef DEBUG
		perror(msg);
#endif
		throw std::runtime_error(msg);
	}

	local.sun_family = AF_UNIX;
	strcpy(local.sun_path, path.c_str());
	unlink(local.sun_path);

	int len = strlen(local.sun_path) + sizeof(local.sun_family);

	if (::bind(sfd, (sockaddr *) &local, len) == -1) {
		const char *msg = "UNIXServerSocket::bind() failed";
#ifdef DEBUG
		perror(msg);
#endif
		throw std::runtime_error(msg);
	}

	if (listen(sfd, 5) == -1) {
		const char *msg = "UNIXServerSocket::listen() failed";
#ifdef DEBUG
		perror(msg);
#endif
		throw std::runtime_error(msg);
	}
}

UNIXServerSocket::~UNIXServerSocket() {
	::unlink(local.sun_path);
}

Connection* UNIXServerSocket::accept() {
	unsigned t = sizeof(remote);
	last_new_sock = ::accept(sfd, (sockaddr *) &remote, &t);

	if (0 > last_new_sock) {
		perror("UNIXServerSocket::accept() failed");
		return (NULL);
	}

	return (new Connection(last_new_sock));
}

}

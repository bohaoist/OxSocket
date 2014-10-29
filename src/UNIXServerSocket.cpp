#include <UNIXServerSocket.h>
namespace OxSocket {
UNIXServerSocket::UNIXServerSocket(std::string path) {

	std::string errmsg = "";

	last_new_sock = -1;

	if (-1 == (sfd = ::socket(AF_UNIX, SOCK_STREAM, 0))) {
		errmsg = "UNIXServerSocket::socket() failed";
		errmsg += ::strerror(errno);
		throw std::runtime_error(errmsg);
	}

	local.sun_family = AF_UNIX;
	::strcpy(local.sun_path, path.c_str());
	::unlink(local.sun_path);

	const unsigned int len = ::strlen(local.sun_path)
			+ sizeof(local.sun_family);

	if (::bind(sfd, (sockaddr *) &local, len) == -1) {
		errmsg = "UNIXServerSocket::bind() failed";
		errmsg += ::strerror(errno);
		throw std::runtime_error(errmsg);

	}

	if (listen(sfd, 5) == -1) {
		errmsg = "UNIXServerSocket::listen() failed";
		errmsg += ::strerror(errno);
		throw std::runtime_error(errmsg);
	}
}

UNIXServerSocket::~UNIXServerSocket() {
	::unlink(local.sun_path);
}

Connection* UNIXServerSocket::accept() {
	unsigned t = sizeof(remote);
	last_new_sock = ::accept(sfd, (sockaddr *) &remote, &t);

	if (0 > last_new_sock) {
#ifdef DEBUG
		perror("UNIXServerSocket::accept() failed");
#endif
		return (NULL);
	}

	return (new Connection(last_new_sock));
}

}

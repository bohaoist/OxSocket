#include <UNIXClientSocket.h>
namespace OxSocket {

UNIXClientSocket::UNIXClientSocket(const std::string path) {

	std::string errmsg = "";

	if (-1 == (sfd = ::socket(AF_UNIX, SOCK_STREAM, 0))) {
		errmsg = "UNIXClientSocket::socket() failed";
		errmsg += ::strerror(errno);
		throw std::runtime_error(errmsg);
	}

	remote.sun_family = AF_UNIX;
	::strcpy(remote.sun_path, path.c_str());
	int len = ::strlen(remote.sun_path) + sizeof(remote.sun_family);
	if (-1 == ::connect(sfd, (sockaddr *) &remote, len)) {
		errmsg = "UNIXClientSocket::connect() failed";
		errmsg += ::strerror(errno);
		throw std::runtime_error(errmsg);
	}

}

UNIXClientSocket::~UNIXClientSocket() {
}

}

#include <Common_tcp_unix.h>

Common_tcp_unix::Common_tcp_unix(int& _sfd, const int _socktype) {
	_sfd = ::socket(_socktype, SOCK_STREAM, 0);
	if (-1 == _sfd) {
		throw std::runtime_error("Common_tcp_unix::socket() failed");
	}
}

Common_tcp_unix::~Common_tcp_unix() {
}


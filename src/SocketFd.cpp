#include <SocketFd.h>

SocketFd::SocketFd() {
	this->ufds.fd = -1;
}

SocketFd::~SocketFd() {

}

int SocketFd::setNonBlocking() {
	if (ufds.fd < 0) {
		return (1);
	}
	int flags = 0;
	flags = ::fcntl(ufds.fd, F_GETFL, 0);
	if (0 != ::fcntl(ufds.fd, F_SETFL, flags | O_NONBLOCK)) {
		::perror("SocketFd::mkNonBlocking::fcntl() failed");
		return (1);
	}
	return (0);
}

int SocketFd::setBlocking() {
	if (ufds.fd < 0) {
		return (1);
	}
	int flags = 0;
	flags = ::fcntl(ufds.fd, F_GETFL, 0);
	if (0 != ::fcntl(ufds.fd, F_SETFL, flags & ~O_NONBLOCK)) {
		::perror("SocketFd::mkBlocking::fcntl() failed");
		return (1);
	}
	return (0);
}

int SocketFd::setTimeout(const unsigned sec, const unsigned usec) {
	if (ufds.fd < 0) {
		return (1);
	}
	timeval tv;
	tv.tv_sec = sec;
	tv.tv_usec = usec;
	if (-1
			== ::setsockopt(ufds.fd, SOL_SOCKET, SO_RCVTIMEO, (char *) &tv,
					sizeof tv)) {
		::perror("SocketFd::setsockopt() failed to set recv timeout");
		return (1);
	}
	if (-1
			== ::setsockopt(ufds.fd, SOL_SOCKET, SO_SNDTIMEO, (char *) &tv,
					sizeof tv)) {
		::perror("SocketFd::setsockopt() failed to set send timeout");
		return (1);
	}

	return (0);

}


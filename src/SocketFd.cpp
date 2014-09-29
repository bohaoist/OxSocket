#include <SocketFd.h>

SocketFd::SocketFd() {
	this->sfd = -1;
}

SocketFd::~SocketFd() {
	if (sfd < 0) {
		return;
	}
	if (-1 == ::close(sfd)) {
		::perror("SocketFd::~SocketFd::close() failed");
	}
}

int SocketFd::setNonBlocking() {
	if (sfd < 0) {
		return (1);
	}
	int flags = 0;
	flags = ::fcntl(sfd, F_GETFL, 0);
	if (0 != ::fcntl(sfd, F_SETFL, flags | O_NONBLOCK)) {
		::perror("SocketFd::mkNonBlocking::fcntl() failed");
		return (1);
	}
	return (0);
}

int SocketFd::setBlocking() {
	if (sfd < 0) {
		return (1);
	}
	int flags = 0;
	flags = ::fcntl(sfd, F_GETFL, 0);
	if (0 != ::fcntl(sfd, F_SETFL, flags & ~O_NONBLOCK)) {
		::perror("SocketFd::mkBlocking::fcntl() failed");
		return (1);
	}
	return (0);
}

int SocketFd::setTimeout(const unsigned sec, const unsigned usec) {
	if (sfd < 0) {
		return (1);
	}
	timeval tv;
	tv.tv_sec = sec;
	tv.tv_usec = usec;
	if (-1
			== ::setsockopt(sfd, SOL_SOCKET, SO_RCVTIMEO, (char *) &tv,
					sizeof tv)) {
		::perror("SocketFd::setsockopt() failed to set recv timeout");
		return (1);
	}
	if (-1
			== ::setsockopt(sfd, SOL_SOCKET, SO_SNDTIMEO, (char *) &tv,
					sizeof tv)) {
		::perror("SocketFd::setsockopt() failed to set send timeout");
		return (1);
	}

	return (0);
}


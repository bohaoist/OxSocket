#include "SocketFd.h"

SocketFd::SocketFd(const int sfd) {
	if (sfd == -1) {
		throw std::runtime_error(
				"invalid Socked File Descriptor SocketFd :: socket() failed");
	}
	sockfd = sfd;
}

SocketFd::~SocketFd() {
	if (0 != ::close(sockfd)) {
		::perror("~Connection::close failed");
	}
}

int SocketFd::mkNonBlocking() {
	int flags = 0;
	flags = ::fcntl(sockfd, F_GETFL, 0);
	if (0 != ::fcntl(sockfd, F_SETFL, flags | O_NONBLOCK)) {
		::perror("SocketFd::mkNonBlocking::fcntl() failed");
		return (1);
	}
	return (0);
}

int SocketFd::mkBlocking() {
	int flags = 0;
	flags = ::fcntl(sockfd, F_GETFL, 0);
	if (0 != ::fcntl(sockfd, F_SETFL, flags & ~O_NONBLOCK)) {
		::perror("SocketFd::mkBlocking::fcntl() failed");
		return (1);
	}
	return (0);
}

int SocketFd::setTimeout(const unsigned sec, const unsigned usec) {
	struct timeval tv;
	tv.tv_sec = sec;
	tv.tv_usec = usec;
	if (::setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, (char *) &tv,
			sizeof tv)) {
		::perror("SocketFd::setsockopt() failed to set recv timeout");
		return (1);
	}
	if (::setsockopt(sockfd, SOL_SOCKET, SO_SNDTIMEO, (char *) &tv,
			sizeof tv)) {
		::perror("SocketFd::setsockopt() failed to set send timeout");
		return (1);
	}

	return (0);
}


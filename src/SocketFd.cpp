#include <SocketFd.h>
namespace OxSocket {
SocketFd::SocketFd() {
	sfd = -1;
	isAcceptSocket = false;
}

void SocketFd::close() {
	if (sfd > 0) {
		::close(sfd);
	}
}

SocketFd::~SocketFd() {
	close();
}

int SocketFd::setNonBlocking() {
	int flags = 0;
	flags = ::fcntl(sfd, F_GETFL, 0);
	if (0 != ::fcntl(sfd, F_SETFL, flags | O_NONBLOCK)) {
#ifdef DEBUG
		::perror("SocketFd::mkNonBlocking::fcntl() failed");
#endif
		return (1);
	}

	return (0);
}

void* SocketFd::get_in_addr(sockaddr *sa) {
	if (sa->sa_family == AF_INET) {
		return &(((sockaddr_in*) sa)->sin_addr);
	}

	return &(((sockaddr_in6*) sa)->sin6_addr);
}

int SocketFd::setBlocking() {
	if (sfd < 0) {
		return (1);
	}
	int flags = 0;
	flags = ::fcntl(sfd, F_GETFL, 0);
	if (0 != ::fcntl(sfd, F_SETFL, flags & ~O_NONBLOCK)) {
#ifdef DEBUG
		::perror("SocketFd::mkBlocking::fcntl() failed");
#endif
		return (1);
	}
	return (0);
}

int SocketFd::setTimeout(const unsigned int sec, const unsigned int usec) {

	timeval tv;
	tv.tv_sec = sec;
	tv.tv_usec = usec;
	if (-1
			== ::setsockopt(sfd, SOL_SOCKET, SO_RCVTIMEO, (char *) &tv,
					sizeof tv)) {
#ifdef DEBUG
		::perror("SocketFd::setsockopt() failed to set recv timeout");
#endif
		return (1);
	}
	if (-1
			== ::setsockopt(sfd, SOL_SOCKET, SO_SNDTIMEO, (char *) &tv,
					sizeof tv)) {
#ifdef DEBUG
		::perror("SocketFd::setsockopt() failed to set send timeout");
#endif
		return (1);
	}

	return (0);

}

int SocketFd::get_sfd(){
	return this->sfd;
}
}


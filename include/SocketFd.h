#ifndef SOCKFD_H_
#define SOCKFD_H_

extern "C" {
#include <netinet/in.h> /* sockaddr_in */
#include <sys/socket.h> /* setsockopt */
#include <fcntl.h>      /* fcntl */
#include <stdio.h>      /* perror */
#include <unistd.h>     /* close */
#include <poll.h>       /* poll */
}

class SocketFd {
protected:
	pollfd ufds;
	SocketFd();
	void *get_in_addr(struct sockaddr *sa) {
		if (sa->sa_family == AF_INET) {
			return &(((struct sockaddr_in*) sa)->sin_addr);
		}

		return &(((struct sockaddr_in6*) sa)->sin6_addr);
	}
public:
	virtual ~SocketFd();
	int setNonBlocking();
	int setBlocking();
	int setTimeout(const unsigned, const unsigned = 0);

};
#endif

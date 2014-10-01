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
public:
	virtual ~SocketFd();
	int setNonBlocking();
	int setBlocking();
	int setTimeout(const unsigned, const unsigned = 0);
};
#endif

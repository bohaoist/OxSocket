#ifndef SOCKFD_H_
#define SOCKFD_H_

extern "C" {
#include <netinet/in.h> /* sockaddr_in */
#include <arpa/inet.h>  /* inet_ntoa */
#include <sys/socket.h> /* setsockopt */
#include <fcntl.h>      /* fcntl */
#include <stdio.h>      /* perror */
#include <unistd.h>     /*close */
#include <errno.h>
#include <netinet/tcp.h> /* TCP_NODELAY */
}

#include "Common.h"
/**
 * \brief    Socket File Descriptor
 * \details  Socket File Descriptor
 * \author   Ingo Breuer (ingo.breuer@hhu.de)
 */
class SocketFd: public Common {
protected:
	struct sockaddr_in serv_addr;
	socklen_t serv_addrlen;

	SocketFd(const int);

public:
	virtual ~SocketFd();
	int mkNonBlocking();
	int mkBlocking();
	int setTimeout(const unsigned, const unsigned = 0);
	char *getServerAddr();

};
#endif

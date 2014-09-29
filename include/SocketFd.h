#ifndef SOCKFD_H_
#define SOCKFD_H_

extern "C" {
#include <netinet/in.h> /* sockaddr_in */
#include <arpa/inet.h>  /* inet_ntoa */
#include <sys/socket.h> /* setsockopt */
#include <fcntl.h>      /* fcntl */
#include <stdio.h>      /* perror */
#include <unistd.h>     /* close */
}
#include <stdexcept>
/**
 * \brief    Socket File Descriptor
 * \details  Socket File Descriptor
 * \author   Ingo Breuer (Ingo_Breuer@t-online.de)
 */
class SocketFd {
protected:
	int sockfd; // Socket FileDescriptor
	SocketFd(const int);
public:
	virtual ~SocketFd();
	int mkNonBlocking();
	int mkBlocking();
	int setTimeout(const unsigned, const unsigned = 0);

};
#endif

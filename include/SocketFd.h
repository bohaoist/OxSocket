#ifndef SOCKFD_H_
#define SOCKFD_H_

extern "C" {
#include <netinet/in.h> /* sockaddr_in */
#include <sys/socket.h> /* setsockopt */
#include <fcntl.h>      /* fcntl */
#include <stdio.h>      /* perror */
#include <unistd.h>     /* close */
}

namespace OxSocket {

/**
 * \brief  Virtual Base for SocketFileDescriptor
 * \details Virtual Base for SocketFileDescriptor.
 * 			Provides means to setting timeout, non/blocking
 * 			and getting addr of remote connection
 */
class SocketFd {
protected:

	/**
	 * \brief  set SockFd to -1
	 * \details set SockFd to -1
	 */
	SocketFd();

	/**
	 * TODO Add description
	 * \brief
	 * \details
	 */
	void *get_in_addr(sockaddr*);

	/**
	 * The Socket File Descriptor as a poll struct
	 * for Event Management
	 */
	int sfd;

public:

	bool isAcceptSocket;

	int get_sfd();
	/**
	 *
	 */
	void close();
	/**
	 * \brief does nothing
	 * \details does nothing
	 */
	virtual ~SocketFd();

	/**
	 * \brief make SockFd nonblocking
	 * \details  make SockFd nonblocking
	 */
	int setNonBlocking();

	/**
	 * \brief make SockFd blocking
	 * \details  make SockFd blocking
	 */
	int setBlocking();

	/**
	 * \brief set Tiemout on SocketFileDescriptor
	 * \details  set Tiemout on SocketFileDescriptor
	 * \param[in] sec   Seconds to timeout
	 * \param[in] msec  Milliseconds to timeout
	 */
	int setTimeout(const unsigned int sec, const unsigned int msec = 0);

};
}
#endif


#ifndef TCPSOCKET_H_
#define TCPSOCKET_H_

extern "C" {
#include <stdio.h> /* perror */
#include <sys/socket.h> /* socket, AF_INET,  */
#include <string.h> /* memset */
#include <netinet/in.h> /* htons , INADDR_ANY*/
#include <netdb.h>
}
#include <stdexcept>

#include "SocketFd.h"
/**
 * \brief   General Initialization for a TCP Socket
 * \details General Initialization for a TCP Socket
 * \author  Ingo Breuer (ingo.breuer@hhu.de)
 */
class TCPSocket: public SocketFd {
protected:
	//bool isValidIpAddress(const char *);
	TCPSocket(const unsigned, const char* = NULL);
public:
	virtual ~TCPSocket();
};
#endif

#ifndef TCPSOCKET_H_
#define TCPSOCKET_H_

extern "C" {
#include <stdio.h> /* perror */
#include <sys/socket.h> /* socket, AF_INET,  */
#include <string.h> /* memset */
#include <netinet/in.h> /* htons , INADDR_ANY*/
#include <netdb.h>
}

#include "SocketFd.h"
#include <stdexcept>
//#include "Exception.h"
#include "Common_tcp_udp_unix.h"
#include "Common_tcp_udp.h"
/**
 * \brief   General Initialization for a TCP Socket
 * \details General Initialization for a TCP Socket
 * \author  Ingo Breuer (Ingo_Breuer@t-online.de)
 */
class TCPSocket: public SocketFd,
		public Common_tcp_udp_unix,
		public Common_tcp_udp {
protected:
	struct sockaddr_in serv_addr;
	socklen_t serv_addrlen;
	//bool isValidIpAddress(const char *);
	TCPSocket(const unsigned, const char* = NULL);
public:
	char *getServerAddr();
	virtual ~TCPSocket();
};
#endif

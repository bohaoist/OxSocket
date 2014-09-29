#ifndef UDPSOCKET_H_
#define UDPSOCKET_H_

extern "C" {
#include <string.h>     /* memset */
#include <stdio.h>      /* perror */
#include <netdb.h>      /* addrinfo, AI_PASSIVE, getaddrinfo,gai_strerror,freeaddrinfo	*/
#include <sys/socket.h> /* AF_UNSPEC,SOCK_DGRAM, socket , bind,sendto,recvfrom  */
#include <unistd.h>     /* close */
}

#include "Transceiver.h"
#include "Common_tcp_udp.h"
#include "Common_tcp_udp_unix.h"
//#include "Exception.h"
#include "SocketFd.h"
#include <cmath>
#include <stdexcept>
/**
 * \brief   UDPSocket for sending and recving UDP Packages
 * \details UDPSocket for sending and recving UDP Packages
 * \author  Ingo Breuer (Ingo_Breuer@t-online.de)
 */
class UDPSocket: public SocketFd,
		public Common_tcp_udp_unix,
		public Common_tcp_udp,
		public Transceiver {

private:
	struct addrinfo *p;

public:

	UDPSocket(const unsigned int, const char* = NULL);
	virtual ~UDPSocket();

	int send(const char*, const unsigned, int = 0);
	int recv(char*, const unsigned, int = 0);
};

#endif

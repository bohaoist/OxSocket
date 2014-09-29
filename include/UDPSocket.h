#ifndef UDPSOCKET_H_
#define UDPSOCKET_H_

extern "C" {
#include <string.h>     /* memset */
#include <stdio.h>      /* perror */
#include <netdb.h>      /* addrinfo, AI_PASSIVE, getaddrinfo,gai_strerror,freeaddrinfo	*/
#include <sys/socket.h> /* AF_UNSPEC,SOCK_DGRAM, socket , bind,sendto,recvfrom  */
#include <unistd.h>     /* close */
}

#include <cmath>
#include <stdexcept>

#include <Transceiver.h>
#include <Common_tcp_udp.h>
#include <Common_tcp_udp_unix.h>
#include <SocketFd.h>

class UDPSocket: public SocketFd,
		public Common_tcp_udp_unix,
		public Common_tcp_udp,
		public Transceiver {

private:
	addrinfo *p;
public:
	UDPSocket(const unsigned int, const char* = NULL);
	virtual ~UDPSocket();

	int send(const char*, const unsigned, int = 0);
	int recv(char*, const unsigned, int = 0);
};

#endif

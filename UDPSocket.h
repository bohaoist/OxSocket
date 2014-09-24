#ifndef UDPSOCKET_H_
#define UDPSOCKET_H_

extern "C" {
#include <string.h>     /* memset */
#include <stdio.h>      /* perror,sprintf */
#include <netdb.h>      /* addrinfo, AI_PASSIVE, getaddrinfo,gai_strerror,freeaddrinfo	*/
#include <sys/socket.h> /* AF_UNSPEC,SOCK_DGRAM, socket , bind,sendto,recvfrom  */
#include <unistd.h>     /* close */
}

#include <cmath>  // log10
#include <stdexcept>

#include "Transceiver.h"
#include "Common.h"

/**
 * \brief   UDPSocket for sending and recving UDP Packages
 * \details UDPSocket for sending and recving UDP Packages
 * \author  Ingo Breuer (ingo.breuer@hhu.de)
 */
class UDPSocket: public Common, public Transceiver {

protected:
	struct addrinfo *p, *servinfo;
	int state;
	void init(const unsigned int port, const char* host = NULL);

public:

	UDPSocket(const unsigned int port);
	UDPSocket(const char* host, const unsigned int port);

	virtual ~UDPSocket();

	int send(const char* buffer, const unsigned buffersize, int = 0);
	int recv(char* buffer, const unsigned maxbuffersize, int = 0);
};

#endif

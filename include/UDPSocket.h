#ifndef UDPSOCKET_H_
#define UDPSOCKET_H_

extern "C" {
#include <unistd.h>      /* close */
#include <netdb.h>       /* addrinfo, freeaddrinfo */
#include <sys/socket.h>  /* sockaddr_storage, sendto, recvfrom, */
#include <arpa/inet.h>
#include <string.h>
}
#include <cstdio>
#include <cmath>

namespace OxSocket {
/**
 * virtual base for UDP Sockets
 * implements send() and recv() for Client and Server Sockets
 * and holds some structs used by both
 */
class UDPSocket {
protected:
	struct addrinfo hints, *servinfo, *p;
	int rv;
	int numbytes;
	struct sockaddr_storage their_addr;
	socklen_t addr_len;
	char s[INET6_ADDRSTRLEN];
	UDPSocket();
	char* iport_2_cport(const unsigned int port);
public:

	/**
	 * \brief  frees some structs
	 * \details frees some structs
	 */
	virtual ~UDPSocket();
};
}
#endif

#ifndef UDPSOCKET_H_
#define UDPSOCKET_H_

extern "C" {
#include <unistd.h>      /* close */
#include <netdb.h>       /* addrinfo, freeaddrinfo */
#include <sys/socket.h>  /* sockaddr_storage, sendto, recvfrom, */

}

#include <Transceiver.h>
#include <SocketFd.h>

class UDPSocket: public SocketFd, public Transceiver {
protected:
	int rv;
	struct addrinfo hints, *servinfo, *p;
	struct sockaddr_storage their_addr;
	UDPSocket();
public:
	int send(const char* buf, const unsigned size, int = 0);
	int recv(char* buf, const unsigned size, int = 0);
	virtual ~UDPSocket();
};

#endif

#ifndef TCPSOCKET_H_
#define TCPSOCKET_H_

extern "C" {
#include <netdb.h>        /* addrinfo */
#include <bits/socket.h>  /* socklen_t */
#include <sys/socket.h>   /* sockaddr_storage */
}

class TCPSocket {
protected:
	int rv;
	socklen_t slen;
	addrinfo hints, *servinfo, *p;
	sockaddr_storage their_addr;
	TCPSocket();
public:
	virtual ~TCPSocket();
};
#endif

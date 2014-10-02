#ifndef TCPSOCKET_H_
#define TCPSOCKET_H_

extern "C" {
#include <netdb.h>        /* addrinfo */
#include <bits/socket.h>  /* socklen_t */
#include <sys/socket.h>   /* sockaddr_storage */
}

/**
 *  Non constructable BaseClass for TCP Sockets
 *  just because they share some structs
 *  This is purely for internal use
 */
class TCPSocket {
protected:
	int rv; // return value
	socklen_t slen;
	addrinfo hints, *servinfo, *p;
	sockaddr_storage their_addr;
	TCPSocket();
public:
	virtual ~TCPSocket();
};
#endif

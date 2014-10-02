#ifndef TCPSERVERSOCKET_H_
#define TCPSERVERSOCKET_H_

extern "C" {

#include <sys/socket.h> /* accept , listen, setsockopt, bind. sockaddr_storage */
#include <netdb.h>      /* addrinfo, getaddrinfo, gai_strerror */
#include <arpa/inet.h>  /* inet_ntop */
}

#include <cstdio>      /* perror, sprintf, fprintf */
#include <cstring>     /* memset */
#include <cmath>       /* log10 */
#include <stdexcept>   /* runtime_error */

#include <Connection.h>
#include <TCPSocket.h>
#include <ServerSocket.h>

class TCPServerSocket: public SocketFd, public ServerSocket, public TCPSocket {

public:
	TCPServerSocket(const unsigned);
	virtual ~TCPServerSocket();
	Connection* accept();
};

#endif

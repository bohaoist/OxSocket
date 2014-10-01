#ifndef TCPCLIENTSOCKET_H_
#define TCPCLIENTSOCKET_H_

extern "C" {
#include <sys/socket.h>  /* connect, socket        */
#include <netdb.h>       /* addrinfo, getaddrinfo */
#include <bits/socket.h> /* sockaddr_storage */
#include <sys/unistd.h>  /* close */
}

#include <cstring>	     /* memset */
#include <cmath>         /* log10   */
#include <cstdio>        /* sprintf, fprintf, perror */
#include <stdexcept>     /* runtime_error */

#include <Connection.h>
#include <TCPSocket.h>

class TCPClientSocket: public Connection, public TCPSocket {
public:
	TCPClientSocket(const char*, const unsigned);
	virtual ~TCPClientSocket();
};

#endif

#ifndef TCPCLIENTSOCKET_H_
#define TCPCLIENTSOCKET_H_

extern "C" {
#include <sys/socket.h>  /* connect, socket        */
#include <netdb.h>       /* addrinfo, getaddrinfo */
#include <bits/socket.h> /* sockaddr_storage */
#include <sys/unistd.h>  /* close */
#include <arpa/inet.h>   /**/
}

#include <cstring>	     /* memset */
#include <cmath>         /* log10   */
#include <cstdio>        /* sprintf, fprintf, perror */
#include <stdexcept>     /* runtime_error */
#include <string>

#include <Connection.h>
#include <TCPSocket.h>

/**
 * A TCPClientSocket establishes a connection on init
 * Afterwards it can be used like a Connection Object.
 * It directly provides send() and recv() functions
 * on init/connection error the Constructor throws a std::runtime_error
 */
class TCPClientSocket: public Connection, public TCPSocket {
public:
	/**
	 * \brief Construct a TCP connection
	 * \details Construct a TCP connection
	 *          on error throws std::runtime_error
	 */
	TCPClientSocket(const std::string, const unsigned);

	/**
	 * \brief does nothing
	 * \details does nothing
	 */
	virtual ~TCPClientSocket();
};

#endif

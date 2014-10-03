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

namespace OxSocket {

/**
 * A TCPServerSocket provides a means for TCP Clients to be Accepted
 * with the accept() methode it provides
 * if the construction failes and the Listen Port can not be accessed
 * the constructor will throw a runtime_error
 */
class TCPServerSocket: public AcceptSocket, public TCPSocket {

public:

	/**
	 * \brief  construct a listening Socket
	 * \details constructs a listening Socket
	 *          will throw runtime_error if something goes wrong
	 */
	TCPServerSocket(const unsigned);

	/**
	 * \brief  does nothing
	 * \details does nothing
	 */
	virtual ~TCPServerSocket();

	/**
	 * \brief  accept incoming tcp connections
	 * \details accept incoming tcp connections
	 */
	Connection* accept();
};
}

#endif

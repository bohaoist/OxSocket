#ifndef SERVERSOCKET_H_
#define SERVERSOCKET_H_

extern "C" {
#include <stdio.h> /*perror */
#include <sys/socket.h> /* accept , listen, setsockopt, bind */
}
#include "Connection.h"
#include "TCPSocket.h"
#include "Exception.h"

/**
 * \brief   ServerSocket for accpeting TCP Connections
 * \details ServerSocket for accpeting TCP Connections
 */
class ServerSocket: public TCPSocket {
public:

	ServerSocket(const unsigned);
	virtual ~ServerSocket();

	/**
	 * \brief   Accepts connections on the ServerSocket
	 * \details Accepts connections on the ServerSocket
	 * \return  A Pointer to a Connection Instanze to send/recv data
	 *          from the connected Client
	 */
	Connection* accept();
};

#endif

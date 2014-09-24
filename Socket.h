#ifndef SOCKET_H_
#define SOCKET_H_

#include "Connection.h"
#include "TCPSocket.h"

#include <stdexcept>

extern "C" {
#include <stdio.h>      /* perror         */
#include <netdb.h>      /* gethostbyname  */
#include <string.h>     /* memmove        */
#include <sys/socket.h> /* connect        */
}

/**
 * \brief   TCP Connect Socket
 * \details TCP Connect Socket
 * \author  Ingo Breuer (ingo.breuer@hhu.de)
 */
class Socket: public TCPSocket {
public:

	Socket(const char*, const unsigned);
	virtual ~Socket();

	/**
	 * \brief   Connect to a ServerSocket
	 * \details Connect to a ServerSocket
	 * \return  A Pointer to a Connection Instanze to send/recv data
	 *          from the connected Client
	 */
	Connection* connect();
};

#endif

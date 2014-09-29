#ifndef TCPCLIENTSOCKET_H_
#define TCPCLIENTSOCKET_H_

#include "Connection.h"
#include "TCPSocket.h"
//#include "Exception.h"

extern "C" {
#include <stdio.h>      /* perror         */
#include <netdb.h>      /* gethostbyname  */
#include <string.h>     /* memmove        */
#include <sys/socket.h> /* connect        */
}

/**
 * \brief   TCP Connect Socket
 * \details TCP Connect Socket
 * \author  Ingo Breuer (Ingo_Breuer@t-online.de)
 */
class TCPClientSocket: public TCPSocket {
public:

	TCPClientSocket(const char*, const unsigned);
	virtual ~TCPClientSocket();

	/**
	 * \brief   Connect to a ServerSocket
	 * \details Connect to a ServerSocket
	 * \return  A Pointer to a Connection Instanze to send/recv data
	 *          from the connected Client
	 */
	Connection* connect();
};

#endif

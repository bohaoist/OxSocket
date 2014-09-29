#ifndef TCPSERVERSOCKET_H_
#define TCPSERVERSOCKET_H_

extern "C" {
#include <stdio.h>      /*perror */
#include <sys/socket.h> /* accept , listen, setsockopt, bind */
}

#include <stdexcept>

#include <Connection.h>
#include <TCPSocket.h>
#include <ServerSocket.h>

class TCPServerSocket: public ServerSocket, public TCPSocket {
public:
	TCPServerSocket(const unsigned);
	virtual ~TCPServerSocket();
	Connection* accept();
};

#endif

#ifndef TCPCLIENTSOCKET_H_
#define TCPCLIENTSOCKET_H_

extern "C" {
#include <netdb.h>      /* gethostbyname  */
#include <string.h>     /* memmove        */
#include <sys/socket.h> /* connect        */
}

#include "Connection.h"
#include "TCPSocket.h"
#include <ClientSocket.h>

class TCPClientSocket: public TCPSocket, public ClientSocket {
public:
TCPClientSocket(const char*, const unsigned);
virtual ~TCPClientSocket();
Connection* connect();
};

#endif

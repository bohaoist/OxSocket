#ifndef UNIXCLIENTSOCKET_H_
#define UNIXCLIENTSOCKET_H_

extern "C" {
#include <string.h> /* perror */
#include <sys/socket.h> /* connect */
}

#include <UNIXSocket.h>
#include <Connection.h>
#include <ClientSocket.h>

class UNIXClientSocket: public UNIXSocket, public ClientSocket {
public:
	UNIXClientSocket(const char*);
	virtual ~UNIXClientSocket();
	Connection* connect();
};

#endif

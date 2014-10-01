#ifndef UNIXCLIENTSOCKET_H_
#define UNIXCLIENTSOCKET_H_

extern "C" {
#include <sys/socket.h> /* socket, connect */
#include <sys/un.h>     /* sockaddr_un */
}

#include <cstdio>      /* perror */
#include <cstring>     /* strcpy, strlen */
#include <stdexcept>   /* runtime_error */

#include <Connection.h>

class UNIXClientSocket: public Connection {
private:
	struct sockaddr_un remote;
public:
	UNIXClientSocket(const char*);
	virtual ~UNIXClientSocket();
};

#endif

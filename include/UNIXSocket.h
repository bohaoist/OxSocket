#ifndef UNIXSOCKET_H_
#define UNIXSOCKET_H_

extern "C" {
#include <sys/un.h> /* sockaddr_un */
}
#include "Connection.h"
#include "SocketFd.h"
#include "Common_tcp_udp_unix.h"

class UNIXSocket: public SocketFd, public Common_tcp_udp_unix {
protected:
	struct sockaddr_un local;
	UNIXSocket(const char*);
public:
	virtual ~UNIXSocket();
};

#endif

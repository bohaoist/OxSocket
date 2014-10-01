#ifndef UNIXSOCKET_H_
#define UNIXSOCKET_H_

extern "C" {
#include <sys/un.h> /* sockaddr_un */
#include <sys/socket.h> /* socket */
}

#include <SocketFd.h>
#include <Common_tcp_unix.h>
#include <Common_tcp_udp_unix.h>

class UNIXSocket: public SocketFd,
		public Common_tcp_unix,
		public Common_tcp_udp_unix {
protected:
	sockaddr_un sock;
	UNIXSocket(const char*);
public:
	virtual ~UNIXSocket();
};

#endif

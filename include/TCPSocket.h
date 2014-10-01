#ifndef TCPSOCKET_H_
#define TCPSOCKET_H_

extern "C" {
#include <stdio.h> /* perror */
#include <sys/socket.h> /* socket, AF_INET,  */
#include <string.h> /* memset */
#include <netinet/in.h> /* sockaddr_in, htons , INADDR_ANY*/
#include <netdb.h> /* gethostbyname */
#include <sys/unistd.h> /* socklen_t */
}

#include <stdexcept>

#include <Common_tcp_udp.h>
#include <Common_tcp_udp_unix.h>
#include <SocketFd.h>
#include <Common_tcp_unix.h>

class TCPSocket: public SocketFd,
		public Common_tcp_udp_unix,
		public Common_tcp_udp,
		public Common_tcp_unix {
protected:
	TCPSocket(const unsigned, const char* = NULL);
public:
	char *getLocalAddr();
	char *getRemotAddr();
	virtual ~TCPSocket();
};
#endif

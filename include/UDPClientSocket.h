#ifndef UDPCLIENTSOCKET_H_
#define UDPCLIENTSOCKET_H_

extern "C" {
#include <netdb.h>      /* getaddrinfo, gai_strerror, */
#include <sys/socket.h> /* socket */
}

#include <cmath>        /* log10 */
#include <cstring>      /* memset */
#include <cstdio>		/* perror, sprintf,fprintf */
#include <stdexcept>    /* runtime_error */

#include <UDPSocket.h>

class UDPClientSocket: public UDPSocket {
public:
	UDPClientSocket(const unsigned int, const char*);
	virtual ~UDPClientSocket();
};

#endif

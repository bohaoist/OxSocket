#ifndef UDPSERVERSOCKET_H_
#define UDPSERVERSOCKET_H_

extern "C" {
#include <netdb.h>      /* getaddrinfo, gai_strerror, */
#include <sys/socket.h> /* bind, socket */
}

#include <cmath>        /* log10 */
#include <cstring>      /* memset */
#include <cstdio>		/* perror, sprintf,fprintf */
#include <stdexcept>    /* runtime_error */

#include <UDPSocket.h>

class UDPServerSocket: public UDPSocket {
public:
	UDPServerSocket(const unsigned);
	virtual ~UDPServerSocket();
};

#endif

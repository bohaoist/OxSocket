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

/**
 * A UDPServerSocket is a UDP listening Socket
 * provides send() and recv() methods after construction
 * BaseClass is a Connection Object
 * throws runtime_error on construction failure
 */
class UDPServerSocket: public UDPSocket {
public:
	/**
	 * \brief  creates UDP listening Socket
	 * \details creates UDP listening Socke
	 * 			throws runtime_error on failure
	 */
	UDPServerSocket(const unsigned);

	/**
	 * \brief  does nothing
	 * \details does nothing
	 */
	virtual ~UDPServerSocket();
};

#endif

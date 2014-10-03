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
#include <string>

#include <UDPSocket.h>

/**
 * A UDPClientSocket is read to send() and recv() data after construction
 * if construction failes a runtime_error is thrown
 * BaseCöass is Connection
 */
class UDPClientSocket: public UDPSocket {
public:
	/**
	 * \brief  construct UDPClientSocket
	 * \details construct UDPClientSocket
	 * \param[in] addr The Address of the host
	 * \param[in] port The Port the host is listening on
	 */
	UDPClientSocket(const std::string addr, const unsigned port);

	/**
	 * \brief  does nothing
	 * \details does nothing
	 */
	virtual ~UDPClientSocket();
};

#endif

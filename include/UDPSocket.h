#ifndef UDPSOCKET_H_
#define UDPSOCKET_H_

extern "C" {
#include <unistd.h>      /* close */
#include <netdb.h>       /* addrinfo, freeaddrinfo */
#include <sys/socket.h>  /* sockaddr_storage, sendto, recvfrom, */
}

#include <Connection.h>

namespace OxSocket {
/**
 * virtual base for UDP Sockets
 * implements send() and recv() for Client and Server Sockets
 * and holds some structs used by both
 */
class UDPSocket: public Connection {
protected:
	int rv;
	addrinfo hints, *servinfo, *p;
	sockaddr_storage their_addr;
	UDPSocket();
public:

	/**
	 * \brief  Sends Data
	 * \details Sends Data
	 * \param[in]  buf send buffer
	 * \param[in]  size nb of bytes to send
	 * \param[in]  ???
	 */
	int send(const char* buf, const unsigned int size);

	/**
	 * \brief  Recv Data
	 * \details Recv Data
	 * \param[in]  buf recv buffer
	 * \param[in]  size nb of bytes to recv
	 * \param[in]  ???
	 */
	int recv(char* buf, const unsigned int size);

	/**
	 * \brief  frees some structs
	 * \details frees some structs
	 */
	virtual ~UDPSocket();
};
}
#endif

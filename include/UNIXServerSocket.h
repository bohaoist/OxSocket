#ifndef UNIXSERVERSOCKET_H_
#define UNIXSERVERSOCKET_H_

extern "C" {
#include <sys/unistd.h> /* unlink */
#include <errno.h> /* errno */
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
}

#include <stdexcept>     /* runtime_error */

#include <Connection.h>
#include <ServerSocket.h>

/**
 * A UNIXServerSocket provides a means for UNIX Clients to be Accepted
 * with the accept() methode it provides
 * if the construction failes and the socketfile can not be accessed
 * the constructor will throw a runtime_error
 */
class UNIXServerSocket: public AcceptSocket {
private:
	// fd of last accepted Connection
	int last_new_sock;
	/**
	 * sockfile structs
	 */
	sockaddr_un local, remote;
public:
	/**
	 * \brief construct a unix server socket
	 * \details construct a unix server socket
	 * \param[in] path Path to UNIX Socket File
	 */
	UNIXServerSocket(std::string path);
	virtual ~UNIXServerSocket();
	Connection* accept();
};

#endif
